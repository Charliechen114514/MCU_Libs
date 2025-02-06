#include "WX25Q64/wx25q64.h"
#include "WX25Q64/wx25q64_reg.h"
#include "SPI_Common/soft_spi/soft_spi.h"

static void __enable_write(WX25Q64_Handle* handle)
{
    handle->handle->op->start(handle->handle);
    handle->handle->op->sendByte(handle->handle, W25Q64_WRITE_ENABLE);
    handle->handle->op->end(handle->handle);
}

static void __disable_write(WX25Q64_Handle* handle) 
{
    handle->handle->op->start(handle->handle);
    handle->handle->op->sendByte(handle->handle, W25Q64_WRITE_DISABLE);
    handle->handle->op->end(handle->handle);
}

static void __wait_me(WX25Q64_Handle* handle)
{
	uint32_t Timeout;
	handle->handle->op->start(handle->handle);
	handle->handle->op->sendByte(handle->handle, W25Q64_READ_STATUS_REGISTER_1);
	Timeout = 100000;							//给定超时计数时间
	while ((handle->handle->op->receiveByte(handle->handle) & 0x01) == 0x01)	//循环等待忙标志位
	{
		Timeout --;								//等待时，计数值自减
		if (Timeout == 0)						//自减到0后，等待超时
		{
			break;								
		}
	}
	handle->handle->op->end(handle->handle);
}


static void __disk_erase(WX25Q64_Handle* handle, uint32_t address)
{
	__enable_write(handle);						
	const uint8_t bytes_cmd[4] = {W25Q64_SECTOR_ERASE_4KB, address >> 16, address >> 8, address};
    handle->handle->op->start(handle->handle);  
    handle->handle->op->sendBytes(handle->handle, bytes_cmd, 4);
    handle->handle->op->end(handle->handle);
	__wait_me(handle);
    __disable_write(handle);
}


static void __read_data(WX25Q64_Handle* handle, uint32_t address,uint8_t* datas, uint32_t size)
{
	handle->handle->op->start(handle->handle);
    const uint8_t bytes_cmd[4] = {W25Q64_READ_DATA, address >> 16, address >> 8, address};
    handle->handle->op->sendBytes(handle->handle, bytes_cmd, 4);
    handle->handle->op->receiveBytes(handle->handle, datas, size);
    handle->handle->op->end(handle->handle);
}

/*
    raw write, with no page controls
*/
static void __write_each_page(WX25Q64_Handle* handle, uint32_t address,uint8_t* datas, uint8_t size)
{
    if(size == 0){
        return;
    }
    __disk_erase(handle, address);
    __enable_write(handle);
    handle->handle->op->start(handle->handle);
    const uint8_t bytes_cmd[4] = {W25Q64_PAGE_PROGRAM, address >> 16, address >> 8, address};
    handle->handle->op->sendBytes(handle->handle, bytes_cmd, 4);
    handle->handle->op->sendBytes(handle->handle, datas, size);
    handle->handle->op->end(handle->handle);
    __wait_me(handle);
    __disable_write(handle);
}

static inline uint8_t req_multi_write(uint32_t address, uint32_t len)
{
    return address % WX25Q64_PAGESIZE + len > WX25Q64_PAGESIZE;
}

static void __write_data(WX25Q64_Handle* handle, uint32_t address,uint8_t* datas, uint32_t size)
{
    while(size)
    {
        uint16_t remain_size     = WX25Q64_PAGESIZE - (address % WX25Q64_PAGESIZE);
        uint16_t decide_to_write = (size > remain_size) ? remain_size: size;
        __write_each_page(handle, address, datas, decide_to_write);
        address += decide_to_write;
        datas += decide_to_write;
        size -= decide_to_write;
    }
}

static uint32_t fetch_id(WX25Q64_Handle* handle){
    handle->handle->op->start(handle->handle);
    handle->handle->op->sendByte(handle->handle, W25Q64_JEDEC_ID);
    uint32_t result = 0;
    uint8_t results[3] = {0, 0, 0};
    handle->handle->op->receiveBytes(handle->handle, results, 3);
    for(uint8_t i = 0; i < 3; i++){
        result <<= 8;
        result |= results[i];
    }
    handle->handle->op->end(handle->handle);
    return result;
}

static void __Fetch_property(WX25Q64_Handle* handle, void* data, WX25Q64_Property p)
{
    switch(p){
        case ID:{
            uint32_t _data = fetch_id(handle);
            *(uint32_t*)data = _data;  
        }break;
        default:break;
    }
}

static WX25Q64_Operation op = {
    __Fetch_property,
    __read_data,
    __write_data
};

void WX25Q64_Handle_register_spi_handle(
    WX25Q64_Handle* handle, CommonSPIHandle* protocol)
{
    handle->handle = protocol;
    handle->op = &op;
}
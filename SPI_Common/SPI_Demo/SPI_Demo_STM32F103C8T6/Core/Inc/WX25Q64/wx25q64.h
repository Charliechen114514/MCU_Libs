#ifndef WX25Q64_H
#define WX25Q64_H
#include "SPI_Common/spi_common.h"

typedef struct __WX25Q64_Handle WX25Q64_Handle;
typedef enum {
    ID
}WX25Q64_Property;

#define WX25Q64_PAGESIZE    (256)
#define GET_MID(raw_id)     (raw_id >> 16)
#define GET_DID(raw_id)     (raw_id & 0xFFFF)

typedef struct {
    void (*WX25Q64_Fetch_Property)(WX25Q64_Handle*, void*, WX25Q64_Property);
    void (*read_data)(WX25Q64_Handle* handle, uint32_t address, uint8_t*, uint32_t size);
    void (*write_data)(WX25Q64_Handle* handle, uint32_t address, uint8_t*, uint32_t size);
}WX25Q64_Operation;


typedef struct __WX25Q64_Handle
{
    WX25Q64_Operation*          op;
    CommonSPIHandle*            handle;
}WX25Q64_Handle;

void WX25Q64_Handle_register_spi_handle(WX25Q64_Handle* handle, CommonSPIHandle* protocol);

#endif
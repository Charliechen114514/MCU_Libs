#include "SPI_Common/soft_spi/soft_spi.h"
#include "SPI_Common/hard_spi/hard_spi.h"

static void __start_adapter(CommonSPIHandle *handle)
{
    switch (handle->type)
    {
    case SOFT_SPI_PROTOCOL:
        softspi_start_spi((SOFTSPI_Protocol *)(handle->handle));
        break;
    case HARD_SPI_PROTOCOL:
        hardspi_start_spi((HARDSPI_Protocol*)(handle->handle));
    }
}

static void __end_adapter(CommonSPIHandle *handle)
{
    switch (handle->type)
    {
    case SOFT_SPI_PROTOCOL:
        softspi_end_spi((SOFTSPI_Protocol *)(handle->handle));
        break;
    case HARD_SPI_PROTOCOL:
        hardspi_end_spi((HARDSPI_Protocol*)(handle->handle));
        break;
    }
}

static void __send_adapter(CommonSPIHandle *handle, const uint8_t data)
{
    switch (handle->type)
    {
    case SOFT_SPI_PROTOCOL:
        softspi_send_byte((SOFTSPI_Protocol *)(handle->handle), data);
        break;
    case HARD_SPI_PROTOCOL:
        hardspi_send_byte((HARDSPI_Protocol*)(handle->handle), data);
        break;
    }
}

static uint8_t __receive_adapter(CommonSPIHandle *handle)
{
    switch (handle->type)
    {
    case SOFT_SPI_PROTOCOL:
        return softspi_receive_byte((SOFTSPI_Protocol *)(handle->handle));
    case HARD_SPI_PROTOCOL:
        return hardspi_receive_byte(((HARDSPI_Protocol*)(handle->handle)));
    }
    return 0;
}

static uint8_t __swap_byte(CommonSPIHandle *handle, uint8_t data)
{
    switch (handle->type)
    {
    case SOFT_SPI_PROTOCOL:
        return softspi_swap_byte((SOFTSPI_Protocol *)(handle->handle), data);
        break;
    case HARD_SPI_PROTOCOL:
        return hardspi_swap_byte(((HARDSPI_Protocol*)(handle->handle)), data);
    }
    return 0;
}

static void __sendbytes(CommonSPIHandle *handle, const uint8_t *datas, uint32_t size)
{
    switch (handle->type)
    {
    case SOFT_SPI_PROTOCOL:
    {
        for (uint32_t i = 0; i < size; i++)
            softspi_send_byte((SOFTSPI_Protocol *)(handle->handle), datas[i]);
    }break;
    case HARD_SPI_PROTOCOL:
        hardspi_send_bytes(((HARDSPI_Protocol*)(handle->handle)), datas, size);
    }
}

static void __recBytes(CommonSPIHandle *handle, uint8_t *datas, uint32_t size)
{
    switch (handle->type)
    {
    case SOFT_SPI_PROTOCOL:
    {
        for (uint32_t i = 0; i < size; i++)
            datas[i] = softspi_receive_byte((SOFTSPI_Protocol *)(handle->handle));
    }
    break;
    case HARD_SPI_PROTOCOL:
    {
        hardspi_rec_bytes(((HARDSPI_Protocol*)(handle->handle)), datas, size);
    }
    }
}

static SPI_CommonOperations op = {
    __start_adapter,
    __end_adapter,
    __send_adapter,
    __receive_adapter,
    __swap_byte,
    __sendbytes,
    __recBytes};

void register_softspi_spihandle(
    CommonSPIHandle *handle,
    SOFTSPI_Protocol *protocol_internal)
{
    handle->type = SOFT_SPI_PROTOCOL;
    handle->handle = protocol_internal;
    handle->op = &op;
}

void register_hardspi_spihandle(
    CommonSPIHandle* handle,
    HARDSPI_Protocol* protocol_internal)
{
    handle->type = HARD_SPI_PROTOCOL;
    handle->handle = protocol_internal;
    handle->op = &op;
}
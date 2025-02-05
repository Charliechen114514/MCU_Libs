#ifndef MPU6050_H
#define MPU6050_H
#include "IICDriver/include/common_iic.h"
typedef struct __CommonSoftIIC CCIIC_SoftIICHandle;
typedef struct __CommonHardIIC CCIIC_HardIICHandle;

typedef enum {
    IICProtocol_SOFT_IIC,
    IICProtocol_HARD_IIC
}IICProtocol_Type;

typedef struct{
    int16_t x;
    int16_t y;
    int16_t z;
}CubeeDataType;

typedef enum{
    ID
}MPU6050_Supportive_Property;

typedef struct{
    CubeeDataType   accelerations;
    CubeeDataType   angle_fetch;
}MPU_6050DataPack;
typedef struct __MPU6050Type MPU6050Handle;
typedef uint8_t RegisterAddressType;
typedef uint8_t RegisterDataType;

typedef void(*InternelSend)(MPU6050Handle*, RegisterAddressType, RegisterDataType);
typedef RegisterDataType(*InternelReceive)(MPU6050Handle*, RegisterAddressType);
typedef void(*FetchData)(MPU6050Handle*, MPU_6050DataPack*);
typedef void(*FetchMPU6050Property)(MPU6050Handle*, uint8_t*, MPU6050_Supportive_Property);

typedef struct {
    InternelSend            register_send_function;
    InternelReceive         register_receive_function;
    FetchData               dataFetch_function;
    FetchMPU6050Property    property_fetcher;
}MPU6050_Operations;


typedef struct __MPU6050Type{
    IICCommonHandleType pvt;
    MPU6050_Operations* op;
    IICProtocol_Type    protocol_type;
    uint8_t             mpu_address;
}MPU6050Handle;

/* protocol should be inited already! */
void register_as_softiic_protocol(
    MPU6050Handle* handle, CCIIC_SoftIICHandle* soft);

void register_as_hardiic_protocol(
    MPU6050Handle* handle, CCIIC_HardIICHandle* hard);


#endif



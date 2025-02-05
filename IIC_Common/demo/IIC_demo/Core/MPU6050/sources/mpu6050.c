#include "MPU6050/include/mpu6050.h"
#include "MPU6050/include/mpu6050_register.h"
#include "IICDriver/include/hard_iic.h"
#include "IICDriver/include/soft_iic.h"


static IIC_Operations* fetch_operations(MPU6050Handle* handle)
{
    switch (handle->protocol_type)
    {
    case IICProtocol_SOFT_IIC:
    {
            CCIIC_SoftIICHandle* soft = (CCIIC_SoftIICHandle*)(handle->pvt);
            return soft->operations;
    }break;
    case IICProtocol_HARD_IIC:
    {
        CCIIC_HardIICHandle* hard = (CCIIC_HardIICHandle*)(handle->pvt);
        return hard->operations;
    }break;
    default:
        break;
    }
    // impossible to reach here :)
    return 0;
}


static void __pvt_set_register(MPU6050Handle* handle, uint8_t address, uint8_t datas)
{
    IIC_Operations* op = fetch_operations(handle);
    op->start_iic(handle->pvt);
    op->data_sender(handle->pvt, &handle->mpu_address, 1);
    op->ack_receiver(handle->pvt);
    op->data_sender(handle->pvt, &address, 1);
    op->ack_receiver(handle->pvt);
    op->data_sender(handle->pvt, &datas, 1);
    op->ack_receiver(handle->pvt);
    op->end_iic(handle->pvt);
}

static uint8_t __pvt_read_register(MPU6050Handle* handle, uint8_t address)
{
    IIC_Operations* op = fetch_operations(handle);
    op->start_iic(handle->pvt);
    op->data_sender(handle->pvt, &handle->mpu_address, 1);
    op->ack_receiver(handle->pvt);
    op->data_sender(handle->pvt, &address, 1);
    op->ack_receiver(handle->pvt);

    op->start_iic(handle->pvt);
    uint8_t written_addr = handle->mpu_address | 0x01;
    op->data_sender(handle->pvt, &written_addr, 1);
    op->ack_receiver(handle->pvt);
    uint8_t data = 0;
    op->data_receiver(handle->pvt, &data, 1);
    op->ack_sender(handle->pvt, 1);
    op->end_iic(handle->pvt);
    return data;
}

static void __property_fetcher(MPU6050Handle* handler, uint8_t* data, MPU6050_Supportive_Property p)
{
    switch(p){
        case ID:
            *data = __pvt_read_register(handler, MPU6050_WHO_AM_I);
        default:
            break;  
    }
}

#define COMPOSE_DATA(H, L) ( (H << 8) | L )

static void __data_fetcher(MPU6050Handle* handler, MPU_6050DataPack* pack)
{
    uint8_t resultL = 0;
    uint8_t resultH = 0;

    resultH = __pvt_read_register(handler,MPU6050_ACCEL_XOUT_H);		//读取加速度计X轴的高8位数据
	resultL = __pvt_read_register(handler,MPU6050_ACCEL_XOUT_L);		//读取加速度计X轴的低8位数据
	pack->accelerations.x = COMPOSE_DATA(resultH, resultL);					//数据拼接，通过输出参数返回
	
	resultH = __pvt_read_register(handler,MPU6050_ACCEL_YOUT_H);		//读取加速度计Y轴的高8位数据
	resultL = __pvt_read_register(handler,MPU6050_ACCEL_YOUT_L);		//读取加速度计Y轴的低8位数据
	pack->accelerations.y = COMPOSE_DATA(resultH, resultL);					//数据拼接，通过输出参数返回
	
	resultH = __pvt_read_register(handler,MPU6050_ACCEL_ZOUT_H);		//读取加速度计Z轴的高8位数据
	resultL = __pvt_read_register(handler,MPU6050_ACCEL_ZOUT_L);		//读取加速度计Z轴的低8位数据
	pack->accelerations.z = COMPOSE_DATA(resultH, resultL);					//数据拼接，通过输出参数返回
	
	resultH = __pvt_read_register(handler,MPU6050_GYRO_XOUT_H);		//读取陀螺仪X轴的高8位数据
	resultL = __pvt_read_register(handler,MPU6050_GYRO_XOUT_L);		//读取陀螺仪X轴的低8位数据
	pack->angle_fetch.x = COMPOSE_DATA(resultH, resultL);					//数据拼接，通过输出参数返回
	
	resultH = __pvt_read_register(handler,MPU6050_GYRO_YOUT_H);		//读取陀螺仪Y轴的高8位数据
	resultL = __pvt_read_register(handler,MPU6050_GYRO_YOUT_L);		//读取陀螺仪Y轴的低8位数据
	pack->angle_fetch.y = COMPOSE_DATA(resultH, resultL);					//数据拼接，通过输出参数返回
	
	resultH = __pvt_read_register(handler,MPU6050_GYRO_ZOUT_H);		//读取陀螺仪Z轴的高8位数据
	resultL = __pvt_read_register(handler,MPU6050_GYRO_ZOUT_L);		//读取陀螺仪Z轴的低8位数据
	pack->angle_fetch.z = COMPOSE_DATA(resultH, resultL);

}

static MPU6050_Operations g_op = {
    __pvt_set_register,
    __pvt_read_register,
    __data_fetcher,
    __property_fetcher
};

void register_as_softiic_protocol(
    MPU6050Handle* handle, CCIIC_SoftIICHandle* soft){
    handle->mpu_address = soft->configs.iic_addr;
    handle->op = &g_op;
    handle->protocol_type = IICProtocol_SOFT_IIC;
    handle->pvt = soft;
    __pvt_set_register(handle, MPU6050_PWR_MGMT_1, 0x01);
	__pvt_set_register(handle, MPU6050_PWR_MGMT_2, 0x00);		//电源管理寄存器2，保持默认值0，所有轴均不待机
	__pvt_set_register(handle, MPU6050_SMPLRT_DIV, 0x09);		//采样率分频寄存器，配置采样率
	__pvt_set_register(handle, MPU6050_CONFIG, 0x06);			//配置寄存器，配置DLPF
	__pvt_set_register(handle, MPU6050_GYRO_CONFIG, 0x18);	//陀螺仪配置寄存器，选择满量程为±2000°/s
	__pvt_set_register(handle, MPU6050_ACCEL_CONFIG, 0x18);
}

void register_as_hardiic_protocol(
    MPU6050Handle* handle, CCIIC_HardIICHandle* hard)
{
        handle->mpu_address = hard->configs.iic_addr;
    handle->op = &g_op;
    handle->protocol_type = IICProtocol_SOFT_IIC;
    handle->pvt = hard;
    __pvt_set_register(handle, MPU6050_PWR_MGMT_1, 0x01);
	__pvt_set_register(handle, MPU6050_PWR_MGMT_2, 0x00);		//电源管理寄存器2，保持默认值0，所有轴均不待机
	__pvt_set_register(handle, MPU6050_SMPLRT_DIV, 0x09);		//采样率分频寄存器，配置采样率
	__pvt_set_register(handle, MPU6050_CONFIG, 0x06);			//配置寄存器，配置DLPF
	__pvt_set_register(handle, MPU6050_GYRO_CONFIG, 0x18);	//陀螺仪配置寄存器，选择满量程为±2000°/s
	__pvt_set_register(handle, MPU6050_ACCEL_CONFIG, 0x18);
}



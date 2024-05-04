#include "stm32f1xx_hal.h"
#include "softiic.h"
#include "mpu6050.h"
#include "mpu6050_reg.h"


/**
  * ��    ����MPU6050��ʼ��
  * ��    ������
  * �� �� ֵ����
  */
void MPU6050_Init(void)
{
	MyI2C_Init();									//�ȳ�ʼ���ײ��I2C
	
	/*MPU6050�Ĵ�����ʼ������Ҫ����MPU6050�ֲ�ļĴ����������ã��˴��������˲�����Ҫ�ļĴ���*/
	MPU6050_Write(MPU6050_PWR_MGMT_1, 0x01);		//��Դ����Ĵ���1��ȡ��˯��ģʽ��ѡ��ʱ��ԴΪX��������
	MPU6050_Write(MPU6050_PWR_MGMT_2, 0x00);		//��Դ����Ĵ���2������Ĭ��ֵ0���������������
	MPU6050_Write(MPU6050_SMPLRT_DIV, 0x09);		//�����ʷ�Ƶ�Ĵ��������ò�����
	MPU6050_Write(MPU6050_CONFIG, 0x06);			//���üĴ���������DLPF
	MPU6050_Write(MPU6050_GYRO_CONFIG, 0x18);	//���������üĴ�����ѡ��������Ϊ��2000��/s
	MPU6050_Write(MPU6050_ACCEL_CONFIG, 0x18);	//���ٶȼ����üĴ�����ѡ��������Ϊ��16g
}

/**
  * ��    ����MPU6050��ȡID��
  * ��    ������
  * �� �� ֵ��MPU6050��ID��
  */
uint8_t MPU6050_GetID(void)
{
	return MPU6050_Read(MPU6050_WHO_AM_I);		//����WHO_AM_I�Ĵ�����ֵ
}

/**
  * ��    ����MPU6050��ȡ����
  * ��    ����AccX AccY AccZ ���ٶȼ�X��Y��Z������ݣ�ʹ�������������ʽ���أ���Χ��-32768~32767
  * ��    ����GyroX GyroY GyroZ ������X��Y��Z������ݣ�ʹ�������������ʽ���أ���Χ��-32768~32767
  * �� �� ֵ����
  */
void MPU6050_GetData(int16_t *AccX,  int16_t *AccY,  int16_t *AccZ, 
										 int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
	uint8_t DataH, DataL;								//�������ݸ�8λ�͵�8λ�ı���
	
	DataH = MPU6050_Read(MPU6050_ACCEL_XOUT_H);		//��ȡ���ٶȼ�X��ĸ�8λ����
	DataL = MPU6050_Read(MPU6050_ACCEL_XOUT_L);		//��ȡ���ٶȼ�X��ĵ�8λ����
	*AccX = (DataH << 8) | DataL;						//����ƴ�ӣ�ͨ�������������
	
	DataH = MPU6050_Read(MPU6050_ACCEL_YOUT_H);		//��ȡ���ٶȼ�Y��ĸ�8λ����
	DataL = MPU6050_Read(MPU6050_ACCEL_YOUT_L);		//��ȡ���ٶȼ�Y��ĵ�8λ����
	*AccY = (DataH << 8) | DataL;						//����ƴ�ӣ�ͨ�������������
	
	DataH = MPU6050_Read(MPU6050_ACCEL_ZOUT_H);		//��ȡ���ٶȼ�Z��ĸ�8λ����
	DataL = MPU6050_Read(MPU6050_ACCEL_ZOUT_L);		//��ȡ���ٶȼ�Z��ĵ�8λ����
	*AccZ = (DataH << 8) | DataL;						//����ƴ�ӣ�ͨ�������������
	
	DataH = MPU6050_Read(MPU6050_GYRO_XOUT_H);		//��ȡ������X��ĸ�8λ����
	DataL = MPU6050_Read(MPU6050_GYRO_XOUT_L);		//��ȡ������X��ĵ�8λ����
	*GyroX = (DataH << 8) | DataL;						//����ƴ�ӣ�ͨ�������������
	
	DataH = MPU6050_Read(MPU6050_GYRO_YOUT_H);		//��ȡ������Y��ĸ�8λ����
	DataL = MPU6050_Read(MPU6050_GYRO_YOUT_L);		//��ȡ������Y��ĵ�8λ����
	*GyroY = (DataH << 8) | DataL;						//����ƴ�ӣ�ͨ�������������
	
	DataH = MPU6050_Read(MPU6050_GYRO_ZOUT_H);		//��ȡ������Z��ĸ�8λ����
	DataL = MPU6050_Read(MPU6050_GYRO_ZOUT_L);		//��ȡ������Z��ĵ�8λ����
	*GyroZ = (DataH << 8) | DataL;						//����ƴ�ӣ�ͨ�������������
}


/*
	����1��Ҫд��ļĴ���
	����2��Ҫд�������
*/
void MPU6050_Write(uint8_t Regaddr, uint8_t data)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDR);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Regaddr);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(data);
	MyI2C_ReceiveAck();
	MyI2C_Stop();
}


/*
	����1��Ҫ��ȡ�ļĴ���
*/
uint8_t MPU6050_Read(uint8_t Regaddr)
{
	uint8_t data;
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDR);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Regaddr);
	MyI2C_ReceiveAck();
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDR | 0x01);
	MyI2C_ReceiveAck();
	data = MyI2C_ReceiveByte();
	MyI2C_SendAck(1);
	MyI2C_Stop();
	return data;
}

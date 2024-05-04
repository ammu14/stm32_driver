#ifndef __MPU6050_H
#define __MPU6050_H

void MPU6050_Write(uint8_t Regaddr, uint8_t data);
uint8_t MPU6050_Read(uint8_t Regaddr);
void MPU6050_Init(void);
void MPU6050_GetData(int16_t *AccX,  int16_t *AccY,  int16_t *AccZ, 
										 int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);
uint8_t MPU6050_GetID(void);
#endif

#ifndef __SOFTIIC_H
#define __SOFTIIC_H

#define SDA_port GPIOB
#define SCL_port GPIOB

#define SDA_data GPIO_PIN_11
#define SCL_data GPIO_PIN_10

void MyI2C_Init(void);
void MyI2C_Start(void);
void MyI2C_Stop(void);
void MyI2C_SendByte(uint8_t Byte);
uint8_t MyI2C_ReceiveByte(void);
void MyI2C_SendAck(uint8_t AckBit);
uint8_t MyI2C_ReceiveAck(void);

#endif

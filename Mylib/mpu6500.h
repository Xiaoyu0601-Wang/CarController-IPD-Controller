/* #include "mpu6500.h" */

#ifndef __MPU6500_H
#define __MPU6500_H

#include "main.h"

extern volatile unsigned short int MPU_FLAG;

extern float angletst;//csn output angle value
extern float angleRaw;
extern short int X_tst;
extern float angle2;
extern short int AccData[3];
extern short int AccRawData[3];//
extern short int GyroData[3];
extern short int GyroRawData[3];
extern short int TemRawData;//
extern float AngularV[3];
extern float Angle[3];
extern float RawAngle;
//extern float   acc_data_x, acc_data_y, acc_data_z; 
//extern float   gyro_data_x,gyro_data_y,gyro_data_z;

void SPI_Config( void );
void SPI_WriteByte( SPI_TypeDef* SPIx, u8 WriteByte );
u8 SPI_ReadByte( SPI_TypeDef* SPIx );
void MPU_WriteReg( u8 WriteAddr, u8 WriteData );
u8 MPU_ReadReg( u8 ReadAddr );
void MPU_WriteBuf( u8 WriteAddr, u8 *WriteBuf, u8 Bytes );
void MPU_ReadBuf( u8 ReadAddr, u8 *ReadBuf, u8 Bytes );
void MPU_Init( void );
void MPU_ReadData(short int *accData, short int *gyroData);
void MPU6500_init(void);
void Zero_Offset_Config(void);
void Zero_Offset_Cal(void);
float no_motion(float GYRO,float angle);
float no_rotation(float GYRO);
void get_Angle(void);
void IMU_Cal(void);
#endif

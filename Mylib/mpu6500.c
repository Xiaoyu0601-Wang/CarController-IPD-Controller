#include "main.h"

#define MPU_SPI  SPI1      //使用SPI1
#define MPU_CS   PAO(4)   //PA4

#define GyroZRatio 0.00003814697265625f
#define GyroZPosFix 1.0087250395213f
#define GyroZNegFix 1.0087250395213f//1.0135135135f

//#define AccXRatio 0.00003814697265625f
//#define AccXPosFix 1.0135135135f
//#define AccXNegFix 1.0135135135f

//#define AccYRatio 0.00003814697265625f
//#define AccYPosFix 1.0135135135f
//#define AccYNegFix 1.0135135135f

volatile unsigned short int MPU_FLAG = 0;
volatile unsigned short int OffSet_FLAG = 0;
short int AccData[3];//
short int AccRawData[3];//
short int GyroData[3];//
short int GyroRawData[3];//
short int GyroLastRawData[3];

float Temperature;
short int TemRawData;//
short int RoomTempOffset = 816;

short int	AccZero_Offset[3] = {0};
short int	GyroZero_Offset[3] = {0};

float AngularV[3] = {0};
float Angle[3] = {0};
float RawAngle = 0;
//float Acceleration[3] = {0};
unsigned char AccXY_Buffer[4];
unsigned char GyroZ_Buffer[2];


//float   acc_data_x, acc_data_y, acc_data_z; //
//float   gyro_data_x,gyro_data_y,gyro_data_z;//
//float RLine;
/*用来做物体旋转判断*/
char no_mtn=0;
char frstIn=1;
float bs=0;
float AngleLck;
/*用来做物体旋转判断*/

void SPI_Config()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    SPI_InitTypeDef SPI_InitStruct;
/***修改点***/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
/***修改点***/
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
/***修改点***/
    /* CS PA4 */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
/***修改点***/
    /* SCK PA5 */	/* MISO PA6 */	/* MOSI PA7 */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    MPU_CS = 1;

    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;   // 双线全双工
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;                        // 主模式
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;                    // 数据大小8位
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;                           // 时钟极性
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;                         // 第1个边沿有效，上升沿为采样时刻
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;                            // NSS信号由软件产生
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;   // 8分频，9MHz
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;                   // 高位在前
    SPI_InitStruct.SPI_CRCPolynomial = 7;
/***修改点***/    
    SPI_Init(SPI1, &SPI_InitStruct);
/***修改点***/
    SPI_Cmd(SPI1, ENABLE);
}


/**********************************************************************
**函數 : SPI_WriteByte
**功能 : Transmit 1Byte Data
**輸入 : SPIx, WriteByte
**輸出 : None
**使用 : SPI_WriteByte(SPI1, 0xFF);
**********************************************************************/





void SPI_WriteByte( SPI_TypeDef* SPIx, u8 WriteByte )
{
    while((SPIx->SR & SPI_I2S_FLAG_TXE) == (u16)RESET);
    SPIx->DR = WriteByte;
    while((SPIx->SR & SPI_I2S_FLAG_RXNE) == (u16)RESET);
    SPIx->DR;
}

/**********************************************************************
**函數 : SPI_ReadByte
**功能 : Receive 1Byte Data
**輸入 : SPIx
**輸出 : None
**使用 : Read = SPI_ReadByte(SPI1);
**********************************************************************/
u8 SPI_ReadByte( SPI_TypeDef* SPIx )
{
    while((SPIx->SR & SPI_I2S_FLAG_TXE) == (u16)RESET);
    SPIx->DR = 0xFF;
    while((SPIx->SR & SPI_I2S_FLAG_RXNE) == (u16)RESET);

    return SPIx->DR;
}


void MPU_WriteReg( u8 WriteAddr, u8 WriteData )
{
    MPU_CS = 0;
    SPI_WriteByte(MPU_SPI, WriteAddr);
    SPI_WriteByte(MPU_SPI, WriteData);
    MPU_CS = 1;
}

u8 MPU_ReadReg( u8 ReadAddr )
{
    u8 ReadData;
    
    MPU_CS = 0;
    //The first bit of the first byte:Read(1) Write(0)
    ReadAddr|=0x80;
    SPI_WriteByte(MPU_SPI, ReadAddr);
    ReadData = SPI_ReadByte(MPU_SPI);
    MPU_CS = 1;

    return ReadData;
}

void MPU_WriteBuf( u8 WriteAddr, u8 *WriteBuf, u8 Bytes )
{
    u8 i;

    MPU_CS = 0;

    SPI_WriteByte(MPU_SPI, WriteAddr);

    for(i=0; i<Bytes; i++)
        SPI_WriteByte(MPU_SPI, WriteBuf[i]);

    MPU_CS = 1;
}

void MPU_ReadBuf( u8 ReadAddr, u8 *ReadBuf, u8 Bytes )
{
    u8 i = 0;

    MPU_CS = 0;
    //The first bit of the first byte:Read(1) Write(0)
    ReadAddr|=0x80;
    SPI_WriteByte(MPU_SPI, ReadAddr);

    for(i=0; i<Bytes; i++)
        ReadBuf[i] = SPI_ReadByte(MPU_SPI);

    MPU_CS = 1;
}

void MPU_Init()
{
    u8 Reg_Addr[8]={0x19, //SMPLRT_DIV
                    0x1A, //CONFIG 
                    0x1B, //GYRO_CONFIG
                    0x1C, //ACCEL_CONFIG
                    0x1D, //ACCEL_CONFIG 2
                    0x6A, //USER_CTRL
                    0x6B, //PWR_MGMT_1
                    0x6C};//PWR_MGMT_2
                    
    u8  Reg_Val[8]={0x00, //SAMPLE_RATE
                    0x00, //Gyro Fs = 32KHz
			              0x00,//csn change ;Gyro Full Scale = +-250dps// 0x1B, //Gyro Full Scale = +-2000dps
                    0x00, //Acc Full Scale = +-2G
                    0x00, //Acc Rate = 4KHz
                    0x10, //SPI mode only
                    0x01, //PLL if ready, else use the Internal oscillator
                    0x00};//All sensors on
    u8 i=0;
    for(i=0;i<8;i++)
    {
        MPU_WriteReg(Reg_Addr[i],Reg_Val[i]); 
        Delay_ms(10);
    }
}

void MPU_ReadData(short int *accData, short int *gyroData)
{
	u8 bufAR[14];
	MPU_ReadBuf( 0x3B , bufAR , 14 );
	accData[0] = (bufAR[0] << 8) | bufAR[1];
	accData[1] = (bufAR[2] << 8) | bufAR[3];
	accData[2] = (bufAR[4] << 8) | bufAR[5];
	TemRawData = ((bufAR[6] << 8) | bufAR[7]);
	gyroData[0] = (bufAR[8] << 8) | bufAR[9];
	gyroData[1] = (bufAR[10] << 8) | bufAR[11];
	gyroData[2] = (bufAR[12] << 8) | bufAR[13];
}
/******************************************************/
void Zero_Offset_Config(void){
	short int Count;
	int sum[3];
	for(Count=0;Count<700;Count++)
	{
		MPU_ReadData(AccRawData, GyroRawData);
		sum[0] += AccRawData[0];
		sum[1] += AccRawData[1];
		sum[2] += GyroRawData[2];
		Delay_ms(5);
	}
	AccZero_Offset[0] = (short int)(sum[0]/Count);
	AccZero_Offset[1] = (short int)(sum[1]/Count);
	GyroZero_Offset[2] = (short int)(sum[2]/Count);	
	OffSet_FLAG = 1;
}
void Zero_Offset_Cal(void)
{
	Temperature = (TemRawData - RoomTempOffset)/333.87f;// + 21; 

	AccRawData[0] -= AccZero_Offset[0];
	AccRawData[1] -= AccZero_Offset[1];
	GyroRawData[2] -= GyroZero_Offset[2];
}
/*******************************************************/
void MPU6500_init()
{
	SPI_Config();
	MPU_Init();
	Delay_ms(1500);
	Zero_Offset_Config();
	LPF_Initial();
}


float no_motion(float GYRO,float angle){
	  /*judging motion*/
	if((GYRO<0.5f)&&(GYRO>-0.5f)){ //no motion
		no_mtn++;
		if(no_mtn>=5){   //if continue yes,we can judge no motion.
			 if(frstIn==1){
				 frstIn=0;
				 AngleLck=angle-bs;
			 }
			 no_mtn=0;
			 bs=angle-AngleLck;
		}
	}
	else {          //motion
		AngleLck=angle-bs;  //update Yawlck;
		no_mtn=0;
		frstIn=1;
	}
	return AngleLck;
}

char no_rttn=0;//无转动计数
char AFrstIn=1;//第一次进入锁定模式
float VlctyA=0;//角速度漂移处理
float no_rotation(float GYRO){
	  /*judging motion*/
	if((GYRO<0.5f)&&(GYRO>-0.5f)){ //no motion
		no_rttn++;
		if(no_rttn>=5){   //if continue yes,we can judge no rotation.
			 if(AFrstIn==1){
				 AFrstIn=0;
				 VlctyA=0;
			 }
			 no_rttn=0;	
		}
	}
	else {          //rotation
		VlctyA=GYRO;
		no_rttn=0;
		AFrstIn=1;
	}
	return VlctyA;
} 
 

void Angle_Cal(void)
{
	if (Speed.angle != 0)
	{
//		if((GyroRawData[2]-GyroLastRawData[2])>0)
		{
			AngularV[2] = ((float)GyroData[2]*GyroZRatio)*GyroZPosFix;// - Temperature*0.000784f*0.005f//0.000784f
			Angle[2] += AngularV[2];
		}
	}
}
 
void IMU_Cal(void)
{
	MPU_ReadData(AccRawData, GyroRawData);
	Zero_Offset_Cal();
	GyroZLPF.Input = -GyroRawData[2];//Reverse the Rotation Direction
	GyroData[2] = LPF_Calculation(&GyroZLPF);//(short int)KalmanFilter(GyroRawData[2]);
//	RawAngle += ((float)GyroRawData[2]*GyroZRatio + Temperature*0.000784f*0.005f)*GyroZPosFix; 
	Angle_Cal();
}
 

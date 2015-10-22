#include "main.h"
/*******************************************************************************
                          ELMO通信相关变量
*******************************************************************************/
Elmo      elmo[ELMO_NUM];                                  // 定义Elmo结构体数组,与elmo个数对应
/*******************************************************************************/
void Elmo_Write(Elmo* elmo, unsigned char Index, unsigned char SubIndex, int Param)
{
  elmo->elmoCAN.IDE = CAN_ID_STD;                    //  发送标准帧
  elmo->elmoCAN.StdId  = elmo->ulNodeID;         //  CAN报文IDelmo->ulNodeID
  elmo->elmoCAN.RTR=CAN_RTR_DATA;					   //数据帧
  elmo->elmoCAN.DLC = 6;                            //  CAN报文数据长度
  elmo->elmoCAN.Data[0]= Index;                    //  写数据
  elmo->elmoCAN.Data[1]= SubIndex;              //0x01写数据
  elmo->elmoCAN.Data[2]= Param&0xFF;       //0x01电机开启，0x02电机释放
  elmo->elmoCAN.Data[3]= (Param&0xFF00)>>8;                //  发送SubIndex
  elmo->elmoCAN.Data[4]= (Param&0xFF0000)>>16;
  elmo->elmoCAN.Data[5]= (Param&0xFF000000)>>24;//  依次发送对象内容
  MailBox = CAN_Transmit(CAN, &(elmo->elmoCAN));     //  调用发送报文函数
	while (MailBox == 4)
	{
		MailBox = CAN_Transmit(CAN, &(elmo->elmoCAN)); //  调用发送报文函数
	}
}
/*******************************************************************************
入口参数:                                                  
          elmo          指向elmo结构体的指针
          Index         对象字典索引
          SubIndex      对象字典子索引
*******************************************************************************/
void Elmo_Read(Elmo* elmo, unsigned char Index, unsigned char SubIndex)
{
  g_Index = Index;
  g_SubIndex = SubIndex;
  g_ReadNodeID = elmo->ulNodeID;            //  修改全局变量,供中断使用
  elmo->elmoCAN.IDE = CAN_ID_STD;           //  发送标准帧
  elmo->elmoCAN.RTR=CAN_RTR_DATA;					  //  数据帧
  elmo->elmoCAN.StdId  = elmo->ulNodeID;    //  CAN报文ID
  elmo->elmoCAN.DLC = 6;                    //  读数据
  elmo->elmoCAN.Data[0]= Index;             //  CAN报文前缀,根据资料得到
  elmo->elmoCAN.Data[1]= SubIndex;          //  0x02读码盘，10ms码盘计数
  elmo->elmoCAN.Data[2]= 0;       		      //  发送Index高字节
  elmo->elmoCAN.Data[3]= 0;                	//  发送SubIndex
  elmo->elmoCAN.Data[4]= 0;
  elmo->elmoCAN.Data[5]= 0;                 //  
	MailBox = CAN_Transmit(CAN, &(elmo->elmoCAN));	
	while (MailBox == 4)
	{
		MailBox = CAN_Transmit(CAN, &(elmo->elmoCAN)); //  调用发送报文函数
	}
}
/*******************************************************************************
  函数描述：
             初始化后，ELMO已经处于使能状态，目的是方便各个模式之间的切
             换因为ELMO支持使能状态下的切换
  入口参数:
            elmo          指向elmo结构体的指针
            elmoNum       要初始化的ELMO个数
*******************************************************************************/
void Elmo_Init(Elmo* elmo, unsigned long elmoNum)
{
    unsigned int i;
    tMode tModeInit={0,0,0,0,0,0,0,0,0,0,(void*)0};  //  初始化各种模式的参数
    for (i=1; i<=ELMO_NUM; i++)
    {
	     elmo[ i - 1].ulNodeID = i;							//结点号
       elmo[ i - 1].Mode = tModeInit;
       //Elmo_ParamInit(&elmo[i]);
    }
    Delay_ms(5);                            		//  初始化之后等待一段时间
}


/*******************************************************************************
入口参数：
          speed              目标速度，单位是：counts/sec   
          acc                加速度
          dec                减速度
          QSDec              急停减速度
使用示例：Elmo_RunPVM(&elmo[0],-100000,300000,300000, 40000);        
*******************************************************************************/
/*
void Elmo_RunPVM(Elmo* elmo,  long speed, long acc, long dec, long QSDec)
{  
  if (elmo->Mode.CurMode != &elmo->Mode.PVMode)
  {
    elmo->Mode.CurMode =& elmo->Mode.PVMode; 
    elmo->Mode.PVMode.Speed=0;
    Elmo_Write(elmo, 0x6040, 0x00, 0x06);        //  Shutdown
    delay_us(500);
    Elmo_Write(elmo, 0x6060, 0x00, 0x03);        //  Enter PVMode
    delay_us(500);
    Elmo_Write(elmo, 0x6040, 0x00, 0x07);        //  SwitchOn
    delay_us(500); 
    Elmo_Write(elmo, 0x6040, 0x00, 0x0f);        //  Enable  Operation
    delay_us(500);
  }
  if (elmo->Mode.PVMode.Acc != acc)              // 设置加速度
  {
    elmo->Mode.PVMode.Acc = acc;
    Elmo_Write(elmo, 0x6083, 0x00, acc);
    delay_us(500);
  }
  if (elmo->Mode.PVMode.Dec != dec)              // 设置减速度
  {
    elmo->Mode.PVMode.Dec = dec;
    Elmo_Write(elmo, 0x6084, 0x00, dec);
    delay_us(500);
  }
  if (elmo->Mode.PVMode.QSDec != QSDec)          //  设置急停减速度
  {
    elmo->Mode.PVMode.QSDec = QSDec;
    Elmo_Write(elmo, 0x6085, 0x00, QSDec);
    delay_us(500);  
  }  
  if (elmo->Mode.PVMode.Speed != speed)          //  设置目标速度，同时启动PVM
  {
    elmo->Mode.PVMode.Speed = speed;
    Elmo_Write(elmo, 0x60FF, 0x00, speed);
    delay_us(500);
  }

}
*/
/*******************************************************************************
 入口参数：
           speed        最大速度（必须大于0）
           position     目标位置，单位：counts  
           acc          加速度 
           dec          减速度 
           runMode      P平滑运动模式的运行模式，详细如下：
                           ABS_POS       绝对位置
                           ABS_POS_IMM   绝对位置,立即运行
                           REL_POS_IMM   相对位置,立即运行
                           REL_POS       相对位置
使用示例：Elmo_RunPPM(&elmo[0],100000,1000000,300000,300000,REL_POS_IMM);
*******************************************************************************/
/*
void Elmo_RunPPM(Elmo* elmo, long speed, long position, long acc, long dec, long runMode)
{  
  if (elmo->Mode.CurMode != &elmo->Mode.PPMode)
  {
    elmo->Mode.CurMode = &elmo->Mode.PPMode;  
    Elmo_Write(elmo, 0x6060, 0x00, 0x01);         //  Enter PPMode
    delay_us(500); 
    Elmo_Write(elmo, 0x6040, 0x00, 0x06);         //  Shutdown
    delay_us(500);
    Elmo_Write(elmo, 0x6040, 0x00, 0x07);         //  SwitchOn
    delay_us(500);
    Elmo_Write(elmo, 0x6040, 0x00, 0x0f);         //  Enable  Operation 多啦了这个 可以用的  必定有其特殊用处
    delay_us(500);
  }
  if (elmo->Mode.PPMode.Speed != speed)           //  设置最大速度
  {
    elmo->Mode.PPMode.Speed = speed;
    Elmo_Write(elmo, 0x6081, 0x00, speed);
    delay_us(500);
  }

  if(elmo->Mode.PPMode.Acc != acc)                //  设置加速度
  {
    elmo->Mode.PPMode.Acc = acc;
    Elmo_Write(elmo, 0x6083, 0x00, acc);
    delay_us(500);;
  }
  if(elmo->Mode.PPMode.Dec != dec)                //  设置减速度
  { 
    elmo->Mode.PPMode.Dec = dec;
    Elmo_Write(elmo, 0x6084, 0x00, dec);
    delay_us(500);
  }
    if(elmo->Mode.PPMode.Position != position)      //  设置目标位置
  {
    elmo->Mode.PPMode.Position = position;
    Elmo_Write(elmo, 0x607A, 0x00, position);
    delay_us(500);
  }
  delay_us(500);
  Elmo_Write(elmo, 0x6040, 0x00, runMode);        //  选择运行模式，同时启动PPM
  delay_us(500);
  Elmo_Write(elmo, 0x6040, 0x00, 0x0f);           //  Enable  Operation
  delay_us(500);
  Elmo_Write(elmo, 0x6040, 0x00, 0x0f);           //  Enable  Operation
  delay_us(500);;
}
*/
/*******************************************************************************
入口参数: elmo          指向elmo结构体的指针
*******************************************************************************/
/*
void Elmo_QuickStop(Elmo* elmo)
{
  tMode tModeInit={0,0,0,0,0,0,0,0,0,0,(void*)0};
  
  delay_us(500);     
  Elmo_Write(elmo, 0x6040, 0x00, 0x06);     //  quickstop
  delay_us(500);
  Elmo_Write(elmo, 0x6040, 0x00, 0x07);     //  switch on
  delay_us(500);
  Elmo_Write(elmo, 0x6040, 0x00, 0x0f);     //  Enable Operation
  delay_us(500);
  
  elmo->Mode = tModeInit;                   //  复位参数
}
*/

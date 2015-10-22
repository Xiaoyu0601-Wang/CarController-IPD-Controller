#include "main.h"
/*******************************************************************************
                          ELMOͨ����ر���
*******************************************************************************/
Elmo      elmo[ELMO_NUM];                                  // ����Elmo�ṹ������,��elmo������Ӧ
/*******************************************************************************/
void Elmo_Write(Elmo* elmo, unsigned char Index, unsigned char SubIndex, int Param)
{
  elmo->elmoCAN.IDE = CAN_ID_STD;                    //  ���ͱ�׼֡
  elmo->elmoCAN.StdId  = elmo->ulNodeID;         //  CAN����IDelmo->ulNodeID
  elmo->elmoCAN.RTR=CAN_RTR_DATA;					   //����֡
  elmo->elmoCAN.DLC = 6;                            //  CAN�������ݳ���
  elmo->elmoCAN.Data[0]= Index;                    //  д����
  elmo->elmoCAN.Data[1]= SubIndex;              //0x01д����
  elmo->elmoCAN.Data[2]= Param&0xFF;       //0x01���������0x02����ͷ�
  elmo->elmoCAN.Data[3]= (Param&0xFF00)>>8;                //  ����SubIndex
  elmo->elmoCAN.Data[4]= (Param&0xFF0000)>>16;
  elmo->elmoCAN.Data[5]= (Param&0xFF000000)>>24;//  ���η��Ͷ�������
  MailBox = CAN_Transmit(CAN, &(elmo->elmoCAN));     //  ���÷��ͱ��ĺ���
	while (MailBox == 4)
	{
		MailBox = CAN_Transmit(CAN, &(elmo->elmoCAN)); //  ���÷��ͱ��ĺ���
	}
}
/*******************************************************************************
��ڲ���:                                                  
          elmo          ָ��elmo�ṹ���ָ��
          Index         �����ֵ�����
          SubIndex      �����ֵ�������
*******************************************************************************/
void Elmo_Read(Elmo* elmo, unsigned char Index, unsigned char SubIndex)
{
  g_Index = Index;
  g_SubIndex = SubIndex;
  g_ReadNodeID = elmo->ulNodeID;            //  �޸�ȫ�ֱ���,���ж�ʹ��
  elmo->elmoCAN.IDE = CAN_ID_STD;           //  ���ͱ�׼֡
  elmo->elmoCAN.RTR=CAN_RTR_DATA;					  //  ����֡
  elmo->elmoCAN.StdId  = elmo->ulNodeID;    //  CAN����ID
  elmo->elmoCAN.DLC = 6;                    //  ������
  elmo->elmoCAN.Data[0]= Index;             //  CAN����ǰ׺,�������ϵõ�
  elmo->elmoCAN.Data[1]= SubIndex;          //  0x02�����̣�10ms���̼���
  elmo->elmoCAN.Data[2]= 0;       		      //  ����Index���ֽ�
  elmo->elmoCAN.Data[3]= 0;                	//  ����SubIndex
  elmo->elmoCAN.Data[4]= 0;
  elmo->elmoCAN.Data[5]= 0;                 //  
	MailBox = CAN_Transmit(CAN, &(elmo->elmoCAN));	
	while (MailBox == 4)
	{
		MailBox = CAN_Transmit(CAN, &(elmo->elmoCAN)); //  ���÷��ͱ��ĺ���
	}
}
/*******************************************************************************
  ����������
             ��ʼ����ELMO�Ѿ�����ʹ��״̬��Ŀ���Ƿ������ģʽ֮�����
             ����ΪELMO֧��ʹ��״̬�µ��л�
  ��ڲ���:
            elmo          ָ��elmo�ṹ���ָ��
            elmoNum       Ҫ��ʼ����ELMO����
*******************************************************************************/
void Elmo_Init(Elmo* elmo, unsigned long elmoNum)
{
    unsigned int i;
    tMode tModeInit={0,0,0,0,0,0,0,0,0,0,(void*)0};  //  ��ʼ������ģʽ�Ĳ���
    for (i=1; i<=ELMO_NUM; i++)
    {
	     elmo[ i - 1].ulNodeID = i;							//����
       elmo[ i - 1].Mode = tModeInit;
       //Elmo_ParamInit(&elmo[i]);
    }
    Delay_ms(5);                            		//  ��ʼ��֮��ȴ�һ��ʱ��
}


/*******************************************************************************
��ڲ�����
          speed              Ŀ���ٶȣ���λ�ǣ�counts/sec   
          acc                ���ٶ�
          dec                ���ٶ�
          QSDec              ��ͣ���ٶ�
ʹ��ʾ����Elmo_RunPVM(&elmo[0],-100000,300000,300000, 40000);        
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
  if (elmo->Mode.PVMode.Acc != acc)              // ���ü��ٶ�
  {
    elmo->Mode.PVMode.Acc = acc;
    Elmo_Write(elmo, 0x6083, 0x00, acc);
    delay_us(500);
  }
  if (elmo->Mode.PVMode.Dec != dec)              // ���ü��ٶ�
  {
    elmo->Mode.PVMode.Dec = dec;
    Elmo_Write(elmo, 0x6084, 0x00, dec);
    delay_us(500);
  }
  if (elmo->Mode.PVMode.QSDec != QSDec)          //  ���ü�ͣ���ٶ�
  {
    elmo->Mode.PVMode.QSDec = QSDec;
    Elmo_Write(elmo, 0x6085, 0x00, QSDec);
    delay_us(500);  
  }  
  if (elmo->Mode.PVMode.Speed != speed)          //  ����Ŀ���ٶȣ�ͬʱ����PVM
  {
    elmo->Mode.PVMode.Speed = speed;
    Elmo_Write(elmo, 0x60FF, 0x00, speed);
    delay_us(500);
  }

}
*/
/*******************************************************************************
 ��ڲ�����
           speed        ����ٶȣ��������0��
           position     Ŀ��λ�ã���λ��counts  
           acc          ���ٶ� 
           dec          ���ٶ� 
           runMode      Pƽ���˶�ģʽ������ģʽ����ϸ���£�
                           ABS_POS       ����λ��
                           ABS_POS_IMM   ����λ��,��������
                           REL_POS_IMM   ���λ��,��������
                           REL_POS       ���λ��
ʹ��ʾ����Elmo_RunPPM(&elmo[0],100000,1000000,300000,300000,REL_POS_IMM);
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
    Elmo_Write(elmo, 0x6040, 0x00, 0x0f);         //  Enable  Operation ��������� �����õ�  �ض����������ô�
    delay_us(500);
  }
  if (elmo->Mode.PPMode.Speed != speed)           //  ��������ٶ�
  {
    elmo->Mode.PPMode.Speed = speed;
    Elmo_Write(elmo, 0x6081, 0x00, speed);
    delay_us(500);
  }

  if(elmo->Mode.PPMode.Acc != acc)                //  ���ü��ٶ�
  {
    elmo->Mode.PPMode.Acc = acc;
    Elmo_Write(elmo, 0x6083, 0x00, acc);
    delay_us(500);;
  }
  if(elmo->Mode.PPMode.Dec != dec)                //  ���ü��ٶ�
  { 
    elmo->Mode.PPMode.Dec = dec;
    Elmo_Write(elmo, 0x6084, 0x00, dec);
    delay_us(500);
  }
    if(elmo->Mode.PPMode.Position != position)      //  ����Ŀ��λ��
  {
    elmo->Mode.PPMode.Position = position;
    Elmo_Write(elmo, 0x607A, 0x00, position);
    delay_us(500);
  }
  delay_us(500);
  Elmo_Write(elmo, 0x6040, 0x00, runMode);        //  ѡ������ģʽ��ͬʱ����PPM
  delay_us(500);
  Elmo_Write(elmo, 0x6040, 0x00, 0x0f);           //  Enable  Operation
  delay_us(500);
  Elmo_Write(elmo, 0x6040, 0x00, 0x0f);           //  Enable  Operation
  delay_us(500);;
}
*/
/*******************************************************************************
��ڲ���: elmo          ָ��elmo�ṹ���ָ��
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
  
  elmo->Mode = tModeInit;                   //  ��λ����
}
*/

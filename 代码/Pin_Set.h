//Pin_Set.h

#ifndef  _Pin_Set_h
#define _Pin_Set_h


//引脚设定
//****************************************
//MP3模块
//2收RX,3发TX
byte SS_RX_Pin = 10;
byte SS_TX_Pin = 11;
//********************
//加速度传感器
//20 (SDA) 和21 (SCL)
//SDA;
//SCL;
//8 9:int0 int1
byte Int0_Pin = 8, Int1_Pin = 9;
//********************
//心率传感器
byte Heart_Pin = A0;
//****************************************


#endif //_Pin_Set_h

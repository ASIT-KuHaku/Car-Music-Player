/*
 Name:		MP3_ON_Car.ino
 Created:	2019/3/10 20:28:04
 Author:	2540784213@qq.com
*/


//更新日志
/*
	0312 1800 重构基本结构
	0312 2221 完成测心率程序
	0313 1949 完成初版
*/


//包含类
//****************************************
#include "Pin_Set.h"
#include "Other_Function.h"
//****************************************


//变量区
//****************************************
byte Now_Emotion = 0;
byte Histo_Emotion = 0;
//
int delay_t = 50;
//****************************************


//对象区
//****************************************
SoftwareSerial MP3_TF_16P(SS_RX_Pin, SS_TX_Pin);
Pulse_Sensor Pulse_Sensor_0(0, delay_t);
//****************************************


//配置函数
void setup() {
	//串口初始化
	Serial.begin(115200);
	//加速度传感器初始化
	ADXL_Init(ADXAddress);
	//播放器供电控制
	pinMode(12, 1);
	digitalWrite(12, 1);
	delay(500);
	//软串口启动
	MP3_TF_16P.begin(9600);
	//音乐播放模块初始化
	mp3_set_serial(MP3_TF_16P);
	//设置音量
	delay(10); mp3_set_volume(30);
}
//循环函数
void loop() {
	//循环采集数据
	Pulse_Sensor_0.Read_Analog();
	delay(delay_t); Cal_Speed();
	Serial.println(Pulse_Sensor_0.Get_Pulse());
	//判断是否进入高速，否则停止播放并return
	if (Get_Running_Conditioon() == false) { mp3_stop(); return; }
	//进入高速，采集心情
	Histo_Emotion = Now_Emotion;
	Now_Emotion = Get_Emotion(Pulse_Sensor_0);
	//判断心情变化，不变的化delay(100),然后return
	if (Histo_Emotion == Now_Emotion) { delay(100); return; }
	//心情变化，播放相应音乐
	switch (Now_Emotion)
	{
	case Happy:
		Mp3_Play(1);
	case Excited:
		Mp3_Play(2);
	case Sad:
		Mp3_Play(3);
	case Nervous:
		Mp3_Play(3);
	case Normal:
		mp3_random_play();
	default:
		break;
	}
	//
}




void t0() {
	Mp3_Play(0);
	delay(5000);
	Mp3_Play(1);
	delay(5000);
	Mp3_Play(2);
	delay(5000);
	return;
}
void t1() {
	while (Serial.available() == 0);
	byte byte_ = Serial.read();
	switch (byte_)
	{
	case 0:
		Mp3_Play(0);
		break;
	case 1:
		Mp3_Play(1);
		break;
	case 2:
		Mp3_Play(2);
		break;
	case 3:
		Mp3_Play(3);
		break;
	default:
		break;
	}
	Serial.println(byte_);
}

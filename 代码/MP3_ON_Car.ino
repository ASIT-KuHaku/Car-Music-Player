/*
 Name:		MP3_ON_Car.ino
 Created:	2019/3/10 20:28:04
 Author:	2540784213@qq.com
*/


//������־
/*
	0312 1800 �ع������ṹ
	0312 2221 ��ɲ����ʳ���
	0313 1949 ��ɳ���
*/


//������
//****************************************
#include "Pin_Set.h"
#include "Other_Function.h"
//****************************************


//������
//****************************************
byte Now_Emotion = 0;
byte Histo_Emotion = 0;
//
int delay_t = 50;
//****************************************


//������
//****************************************
SoftwareSerial MP3_TF_16P(SS_RX_Pin, SS_TX_Pin);
Pulse_Sensor Pulse_Sensor_0(0, delay_t);
//****************************************


//���ú���
void setup() {
	//���ڳ�ʼ��
	Serial.begin(115200);
	//���ٶȴ�������ʼ��
	ADXL_Init(ADXAddress);
	//�������������
	pinMode(12, 1);
	digitalWrite(12, 1);
	delay(500);
	//��������
	MP3_TF_16P.begin(9600);
	//���ֲ���ģ���ʼ��
	mp3_set_serial(MP3_TF_16P);
	//��������
	delay(10); mp3_set_volume(30);
}
//ѭ������
void loop() {
	//ѭ���ɼ�����
	Pulse_Sensor_0.Read_Analog();
	delay(delay_t); Cal_Speed();
	Serial.println(Pulse_Sensor_0.Get_Pulse());
	//�ж��Ƿ������٣�����ֹͣ���Ų�return
	if (Get_Running_Conditioon() == false) { mp3_stop(); return; }
	//������٣��ɼ�����
	Histo_Emotion = Now_Emotion;
	Now_Emotion = Get_Emotion(Pulse_Sensor_0);
	//�ж�����仯������Ļ�delay(100),Ȼ��return
	if (Histo_Emotion == Now_Emotion) { delay(100); return; }
	//����仯��������Ӧ����
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

#pragma once
#pragma once
#include<stdio.h>
#include<easyx.h>
#include<graphics.h>
#include<windows.h>
#pragma comment(lib,"winmm.lib")
//#define WIDTH 846
//#define HIGHT 585
//#define SCREEN_WIDTH 960
//#define SCREEN_HIGH 720
//#define GARDEN_WIDTH 1680
//#define GARDEN_HIGH 720
#define WIDTH 1000
#define HIGHT 1000
#define GARDEN_WIDTH 900
#define GARDEN_HIGH 600

int a = 0; int b = 0; int c = 0;//a=music1 b=music2 c=music3�ж�Ϊ�Ǹ�����
int j = 2;//��ʼ����ʼʱ������ͼƬ
int volume3 = 200;//��ʼ������С
void initdeat();//��ʼ��
void volume1();//����+
void volume2();//����-


void music1();//��Ч1
void music2();//��Ч2
void music3();//��Ч3


void initdeat()
{
	IMAGE yl[7];
	char name[64];
	for (int i = 1; i <= 6; i++)
	{
		sprintf_s(name, sizeof(name), "ly/yl%d.png", i);
		loadimage(&yl[i], name);
	}
	IMAGE img;
	IMAGE zt;
	IMAGE ks2, ks1, jx1, jx2, fh1, fh2;
	loadimage(&img, "res/bg.png");//�����壬���㸴�Ƴ�ʼ��
	loadimage(&zt, "res/zt.png");
	loadimage(&ks1, "res/ks1.png");
	loadimage(&ks2, "res/ks2.png");
	loadimage(&jx1, "res/jx1.png");
	loadimage(&jx2, "res/js2.png");
	loadimage(&fh1, "res/fh1.png");
	loadimage(&fh2, "res/fh2.png");
	initgraph(GARDEN_WIDTH, GARDEN_HIGH);
	putimage(200, 0, &img, SRCPAINT);


}
void volume1()
{
	
	if (j > 0 && j <= 6)//�ж��������Ƿ�Խ�磬�Ǿ�����ͣ��
	{

		IMAGE yl[10];
		char name[64];
		sprintf_s(name, sizeof(name), "yl/yl%d.png", j);//ƴ��
		loadimage(&yl[j], name);
		putimage(551+100-20+30,160+100-40, &yl[j]);
	}
	else if (j < 0)
	{
		IMAGE yl1;
		loadimage(&yl1, "yl/yl1.png");
		putimage(551+100-20+30, 160+60,  &yl1);
		j = 0;
	}
	else if (j >= 6)
	{
		IMAGE yl6;
		loadimage(&yl6, "yl/yl6.png");
		putimage(551+100-20+30, 160+60, &yl6);
		j = 6;
	}
	char cmd1[100] = { 0 };//����
	char cmd2[100] = { 0 };
	char cmd3[100] = { 0 };
	int	volume2 = volume3 + 200;//�ı�����
	volume3 = volume2;//��ȫ�ָı�����
	sprintf_s(cmd1, "setaudio  ./ppp.mp3 volume to %d", volume3);//ʵ�������ı�
	sprintf_s(cmd2, "setaudio  ./hhh.mp3 volume to %d", volume3);
	sprintf_s(cmd3, "setaudio  ./ggg.mp3 volume to %d", volume3);
	static MCIERROR ret;
	
	if (a > 0)//�ж����Ǹ�����
	{
		ret = mciSendString(cmd1, 0, NULL, 0);

	}
	if (b > 0)
	{
		ret = mciSendString(cmd2, 0, NULL, 0);
	}
	if (c > 0)
	{
		ret = mciSendString(cmd3, 0, NULL, 0);
	}j++;
}
void volume2()//������ʱһ��
{
	//j--;

	if (j > 0 && j <= 6)
	{

		IMAGE yl[10];
		char name[64];
		sprintf_s(name, sizeof(name), "yl/yl%d.png", j);
		loadimage(&yl[j], name);
		putimage(551+100-20+30, 160+60, &yl[j]);
	}
	else if (j < 0)
	{
		IMAGE yl1;
		loadimage(&yl1, "yl/yl1.png");
		putimage(551+100-20 + 30, 160+60, &yl1);
		j = 0;
	}
	else if (j >= 6)
	{
		IMAGE yl6;
		loadimage(&yl6, "yl/yl6.png");
		putimage(551+100-20 + 30, 160+60, &yl6);
		j = 6;
	}
	char cmd1[100] = { 0 };
	char cmd2[100] = { 0 };
	char cmd3[100] = { 0 };
	int	volume2 = volume3 - 400;
	volume3 = volume2;
	sprintf_s(cmd1, "setaudio  ./ppp.mp3 volume to %d", volume3);
	sprintf_s(cmd2, "setaudio  ./hhh.mp3 volume to %d", volume3);
	sprintf_s(cmd3, "setaudio  ./ggg.mp3 volume to %d", volume3);
	static MCIERROR ret;
	if (a > 0)
	{
		ret = mciSendString(cmd1, 0, NULL, 0);

	}
	if (b > 0)
	{
		ret = mciSendString(cmd2, 0, NULL, 0);
	}
	if (c > 0)
	{
		ret = mciSendString(cmd3, 0, NULL, 0);
	}j--;

}
void music1()
{
	a = 1; b = 0; c = 0;//����aΪmusic1
	char cmd1[100] = { 0 };
	mciSendString("stop  ./hhh.mp3", 0, 0, 0);//ͣ��muaic2,3
	mciSendString("stop  ./ggg.mp3", 0, 0, 0);
	mciSendString("open  ./ppp.mp3", 0, 0, 0);
	mciSendString("play  ./ppp.mp3  repeat ", 0, 0, 0);
	MCIERROR ret1 = mciSendString("setaudio ./ppp.mp3 volume to 100", NULL, 0, NULL);//ƴ��
	sprintf_s(cmd1, "setaudio  ./ppp.mp3 volume to %d", volume3);//�ı�ɹ�
	ret1 = mciSendString("cmd1", 0, NULL, 0);//����
}
void music2()
{
	a = 0; b = 1; c = 0;//����bΪmusi2
	char cmd2[100] = { 0 };
	mciSendString("stop ./ppp.mp3", 0, 0, 0);//ͣ��muaic1,3
	mciSendString("stop ./ggg.mp3", 0, 0, 0);
	mciSendString("open  ./hhh.mp3 ", 0, 0, 0);
	mciSendString("play  ./hhh.mp3 repeat", 0, 0, 0);
	MCIERROR ret1 = mciSendString("setaudio ./hhh.mp3 volume to 100 ", NULL, 0, NULL);//ƴ��
	sprintf_s(cmd2, "setaudio  ./hhh.mp3 volume to %d", volume3);//�ı�ɹ�
	ret1 = mciSendString(cmd2, 0, NULL, 0);//����
}
void music3()
{
	a = 0; b = 0; c = 1; //����cΪmusi3
	char cmd3[100] = { 0 };
	mciSendString("stop ./hhh.mp3", 0, 0, 0);//ͣ��muaic1,2
	mciSendString("stop ./ppp.mp3", 0, 0, 0);
	mciSendString("open  ./ggg.mp3 ", 0, 0, 0);
	mciSendString("play  ./ggg.mp3 repeat", 0, 0, 0);
	MCIERROR ret1 = mciSendString("setaudio ./ggg.mp3 volume to 100", NULL, 0, NULL);//ƴ��
	sprintf_s(cmd3, "setaudio  ./ggg.mp3 volume to %d", volume3);//�ı�ɹ�
	ret1 = mciSendString(cmd3, 0, NULL, 0);//����
}





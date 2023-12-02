#include<stdio.h>
#include<easyx.h>
#include<windows.h>
#include "tools.h"
#pragma comment(lib,"winmm.lib")
#include<graphics.h>
#define WIDTH 900
#define HIGHT 600
//�������ṹ���Լ������
//�Ľ�ʬ�ľ���
struct STC//С�Ƴ��ṹ��
{
	int x, y;
	int x1, y1;
	int x2, y2;
	int x3, y3; int x4, y4;
	
	int speed;
};
struct STC stc;
struct ZM//��ʬ�ṹ��
{
	int x, y;
	int speed;
	int frameindex;
	bool used;
	bool dead;
	int blood;
};
struct ZM zm1[1];

int main()
{
	char name[64];

	IMAGE bg;//����
	IMAGE tc;//�Ƴ�
	IMAGE zmt;//��ʬ
	IMAGE zmdead[22];//����ͼ
	initgraph(WIDTH, HIGHT);
	loadimage(&bg, "res/bg.jpg");//��ʼ��ͼƬ
	loadimage(&tc, "res/xtc.png");//�����Ƴ�ͼƬ
	loadimage(&zmt, "res/zm/13.png");//���ؽ�ʬͼƬ
	IMAGE tc1; IMAGE tc2;//�Ƴ�ͼƬ
	IMAGE tc3; IMAGE tc4;
	loadimage(&tc1, "res/xtc.png"); loadimage(&tc3, "res/xtc.png");//���ض�ӦС��
	loadimage(&tc2, "res/xtc.png"); loadimage(&tc4, "res/xtc.png");
	memset(zm1, 0, sizeof(zm1));
	for (int i = 1; i <= 20; i++)//ѭ����ʬ����ͼ
	{//δʵ�ֶ���
		sprintf_s(name, sizeof(name), "res/zm_dead/%d.png", i);
		loadimage(&zmdead[i], name);
	}
	zm1[0].x = 200; zm1[0].y = 400;//��ʬλ��
	stc.x = 200; stc.y = 500;//С��1
	stc.x1 = 200; stc.y1 =405;//С�Ƴ�2����
	stc.x2 = 200; stc.y2 = 310;//С��3
	stc.x3 = 200; stc.y3 = 205;//С��4
	stc.x4 = 200; stc.y4 = 110;//С��5
	zm1[0].used = true;//���彩ʬʹ��״̬
	zm1[0].dead == true;//��ʬ����״̬
	BeginBatchDraw();//˫����
	while (1)
	{

		putimage(0, 0, &bg);
		putimagePNG(stc.x, stc.y, &tc);//��ӡͼƬ
		putimagePNG(stc.x1, stc.y1, &tc1);	putimagePNG(stc.x2, stc.y2, &tc2);
		putimagePNG(stc.x3, stc.y3, &tc); putimagePNG(stc.x4, stc.y4, &tc);
		if (zm1[0].x < 210)//�ж��Ƿ񵽴�С�Ƴ�λ��
		{
			if (zm1[0].y >= 400)//��ʬ�ж�����һ��
			{
				stc.x = stc.x + 1;
			}
			if (zm1[0].y <400&&zm1[0].y>305)//��ʬ�ж�����һ��
			{
				stc.x1 = stc.x1 + 1;
			}
			if (zm1[0].y <305 && zm1[0].y > 210)//��ʬ�ж�����һ��
			{
				stc.x2 = stc.x2 + 1;
			}
			if (zm1[0].y < 210&& zm1[0].y > 115)//��ʬ�ж�����һ��
			{
				stc.x3 = stc.x3 + 1;
			}
			if (zm1[0].y < 115)
			{//�ж�����һ��
				stc.x4 = stc.x4 + 1;
			}
		}
		if (zm1[0].used == true)//�жϽ�ʬ�Ƿ�����
		{
			putimagePNG(zm1[0].x, zm1[0].y, &zmt);
		}
		if (zm1[0].x <= stc.x && stc.x <= 800&& zm1[0].y >= 400)
		{//�ж������в����������Ƴ�ǰ��
			zm1[0].used = false;
			putimagePNG(zm1[0].x, zm1[0].y, &zmdead[1]);
		}
		if (zm1[0].x <= stc.x1 && stc.x1 <= 800&&zm1[0].y < 400 && zm1[0].y>305)
		{//�ж������в����������Ƴ�ǰ��
			zm1[0].used = false;
			putimagePNG(zm1[0].x, zm1[0].y, &zmdead[1]);

		}
		if (zm1[0].x <= stc.x2 && stc.x2 <= 800&& zm1[0].y < 305 && zm1[0].y > 210)
		{//�ж������в����������Ƴ�ǰ��
			zm1[0].used = false;
			putimagePNG(zm1[0].x, zm1[0].y, &zmdead[1]);
	}
		if (zm1[0].x <= stc.x3 && stc.x3 <= 800&& zm1[0].y < 210 && zm1[0].y > 115)
		{//�ж������в����������Ƴ�ǰ��
			zm1[0].used = false;
			putimagePNG(zm1[0].x, zm1[0].y, &zmdead[1]);
	}
		if (zm1[0].x <= stc.x4 && stc.x4 <= 800&& zm1[0].y < 115)
		{//�ж������в����������Ƴ�ǰ��
			zm1[0].used = false;
			putimagePNG(zm1[0].x, zm1[0].y, &zmdead[1]);
		}

		FlushBatchDraw();
	}

	EndBatchDraw();
	system("pause");
	return 0;
}
#include<stdio.h>
#include<easyx.h>
#include<windows.h>
#include "tools.h"
#pragma comment(lib,"winmm.lib")
#include<graphics.h>
#define WIDTH 900
#define HIGHT 600
//这两个结构体自己定义的
//改僵尸的就行
struct STC//小推车结构体
{
	int x, y;
	int x1, y1;
	int x2, y2;
	int x3, y3; int x4, y4;
	
	int speed;
};
struct STC stc;
struct ZM//僵尸结构体
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

	IMAGE bg;//背景
	IMAGE tc;//推车
	IMAGE zmt;//僵尸
	IMAGE zmdead[22];//死亡图
	initgraph(WIDTH, HIGHT);
	loadimage(&bg, "res/bg.jpg");//初始化图片
	loadimage(&tc, "res/xtc.png");//加载推车图片
	loadimage(&zmt, "res/zm/13.png");//加载僵尸图片
	IMAGE tc1; IMAGE tc2;//推车图片
	IMAGE tc3; IMAGE tc4;
	loadimage(&tc1, "res/xtc.png"); loadimage(&tc3, "res/xtc.png");//加载对应小车
	loadimage(&tc2, "res/xtc.png"); loadimage(&tc4, "res/xtc.png");
	memset(zm1, 0, sizeof(zm1));
	for (int i = 1; i <= 20; i++)//循环僵尸死亡图
	{//未实现动画
		sprintf_s(name, sizeof(name), "res/zm_dead/%d.png", i);
		loadimage(&zmdead[i], name);
	}
	zm1[0].x = 200; zm1[0].y = 400;//僵尸位置
	stc.x = 200; stc.y = 500;//小车1
	stc.x1 = 200; stc.y1 =405;//小推车2坐标
	stc.x2 = 200; stc.y2 = 310;//小车3
	stc.x3 = 200; stc.y3 = 205;//小车4
	stc.x4 = 200; stc.y4 = 110;//小车5
	zm1[0].used = true;//定义僵尸使用状态
	zm1[0].dead == true;//僵尸死亡状态
	BeginBatchDraw();//双缓冲
	while (1)
	{

		putimage(0, 0, &bg);
		putimagePNG(stc.x, stc.y, &tc);//打印图片
		putimagePNG(stc.x1, stc.y1, &tc1);	putimagePNG(stc.x2, stc.y2, &tc2);
		putimagePNG(stc.x3, stc.y3, &tc); putimagePNG(stc.x4, stc.y4, &tc);
		if (zm1[0].x < 210)//判断是否到达小推车位置
		{
			if (zm1[0].y >= 400)//僵尸判断在哪一行
			{
				stc.x = stc.x + 1;
			}
			if (zm1[0].y <400&&zm1[0].y>305)//僵尸判断在哪一行
			{
				stc.x1 = stc.x1 + 1;
			}
			if (zm1[0].y <305 && zm1[0].y > 210)//僵尸判断在哪一行
			{
				stc.x2 = stc.x2 + 1;
			}
			if (zm1[0].y < 210&& zm1[0].y > 115)//僵尸判断在哪一行
			{
				stc.x3 = stc.x3 + 1;
			}
			if (zm1[0].y < 115)
			{//判断在哪一行
				stc.x4 = stc.x4 + 1;
			}
		}
		if (zm1[0].used == true)//判断僵尸是否死亡
		{
			putimagePNG(zm1[0].x, zm1[0].y, &zmt);
		}
		if (zm1[0].x <= stc.x && stc.x <= 800&& zm1[0].y >= 400)
		{//判断在那行并且让这行推车前进
			zm1[0].used = false;
			putimagePNG(zm1[0].x, zm1[0].y, &zmdead[1]);
		}
		if (zm1[0].x <= stc.x1 && stc.x1 <= 800&&zm1[0].y < 400 && zm1[0].y>305)
		{//判断在那行并且让这行推车前进
			zm1[0].used = false;
			putimagePNG(zm1[0].x, zm1[0].y, &zmdead[1]);

		}
		if (zm1[0].x <= stc.x2 && stc.x2 <= 800&& zm1[0].y < 305 && zm1[0].y > 210)
		{//判断在那行并且让这行推车前进
			zm1[0].used = false;
			putimagePNG(zm1[0].x, zm1[0].y, &zmdead[1]);
	}
		if (zm1[0].x <= stc.x3 && stc.x3 <= 800&& zm1[0].y < 210 && zm1[0].y > 115)
		{//判断在那行并且让这行推车前进
			zm1[0].used = false;
			putimagePNG(zm1[0].x, zm1[0].y, &zmdead[1]);
	}
		if (zm1[0].x <= stc.x4 && stc.x4 <= 800&& zm1[0].y < 115)
		{//判断在那行并且让这行推车前进
			zm1[0].used = false;
			putimagePNG(zm1[0].x, zm1[0].y, &zmdead[1]);
		}

		FlushBatchDraw();
	}

	EndBatchDraw();
	system("pause");
	return 0;
}
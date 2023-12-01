#include<stdio.h>
#include<easyx.h>
#include<graphics.h>
#include<windows.h>
#include"tools.h"
#include"yin2.h"
#pragma comment(lib,"winmm.lib")
void initdelt()
{
	IMAGE img;
	IMAGE zt;
	IMAGE ks2, ks1, jx1, jx2, fh1, fh2;//图片变量
	IMAGE yl[7];
	char name[64];
	for (int i = 1; i <= 6; i++)
	{
		sprintf_s(name, sizeof(name), "yl/yl%d.png", i);
		loadimage(&yl[i], name);
	}//初始化音亮条
	loadimage(&zt, "res/bt.png");//初始化图片
	loadimage(&ks1, "res/ks1.png");
	loadimage(&ks2, "res/ks2.png");
	loadimage(&jx1, "res/jx1.png");
	loadimage(&jx2, "res/jx2.png");
	loadimage(&fh1, "res/fh1.png");
	loadimage(&fh2, "res/fh2.png");
	initgraph(GARDEN_WIDTH, GARDEN_HIGH);
	
	int flag1 = 0;//设置变量判断跳转
	int flag2 = 0;
	int flag3 = 0;
	while (1)
	{
		ExMessage  msg;
		BeginBatchDraw();//设置缓冲
		putimage(30, 0, &zt, SRCPAINT);
		putimagePNG(41+30, 437, flag1 ? &fh2 : &fh1);//如果为真则变白并实现跳转
		putimagePNG(626+30, 431, flag2 ? &ks2 : &ks1);
		putimagePNG(340+30, 528, flag3 ? &jx2 : &jx1);
		putimage(551+100-20+30, 160+60, &yl[j]);
		if (peekmessage(&msg))//判断是否按下,按下为选择，松开为跳转
		{

			if (msg.message == WM_LBUTTONDOWN && msg.x > 411+100+30 && msg.x < 465+100+30 && msg.y > 250&& msg.y < 293)
			{
				//音量加

				volume1();
			}

			if (msg.message == WM_LBUTTONDOWN && msg.x > 474+100+20 + 30 && msg.x < 536 +100+20 + 30 && msg.y > 241+20 && msg.y < 288+20)
			{
				//音量减
				volume2();

			}
			if (msg.message == WM_LBUTTONDOWN && msg.x > 171 + 30 && msg.x < 245 + 30 && msg.y > 108 && msg.y < 150)
			{
				//选择1
				music1();
			}
			if (msg.message == WM_LBUTTONDOWN && msg.x > 168 + 30 && msg.x < 238 + 30 && msg.y > 197 && msg.y <235)
			{
				//选择2
				music2();
			}
			if (msg.message == WM_LBUTTONDOWN && msg.x > 172 + 30 && msg.x < 238 + 30 && msg.y > 279&& msg.y < 333)
			{
				//选择3
				music3();
			}
			if (msg.message == WM_LBUTTONDOWN && msg.x > 41 + 30 && msg.x < 259 + 30 && msg.y >432 && msg.x < 473)
			{
				flag1 = 1;

			}
			else if (msg.message == WM_LBUTTONUP && flag1 == 1)
			{

				//return ;
				//返回游戏
			}
			if (msg.message == WM_LBUTTONDOWN && msg.x > 526 + 100 + 30 && msg.x < 716 + 30 && msg.y >431 && msg.y < 476)
			{
				flag2 = 1;

			}
			else if (msg.message == WM_LBUTTONUP && flag2 == 1)
			{

				//return ;
				//重新开始
			}
			if (msg.message == WM_LBUTTONDOWN && msg.x > 340 + 30 && msg.x < 474 + 30 && msg.y >530 && msg.x < 586)
			{
				flag3 = 1;

			}
			else if (msg.message == WM_LBUTTONUP && flag3 == 1)
			{

				//return ;
				//继续游戏

			}
			EndBatchDraw();//结束缓冲

		}
	}
}

int main()
{
	music1();//播放初始音乐
	initdelt();
	system("pause");
	return 0;
}
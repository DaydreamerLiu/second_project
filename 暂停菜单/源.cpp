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
	IMAGE ks2, ks1, jx1, jx2, fh1, fh2;//ͼƬ����
	IMAGE yl[7];
	char name[64];
	for (int i = 1; i <= 6; i++)
	{
		sprintf_s(name, sizeof(name), "yl/yl%d.png", i);
		loadimage(&yl[i], name);
	}//��ʼ��������
	loadimage(&zt, "res/bt.png");//��ʼ��ͼƬ
	loadimage(&ks1, "res/ks1.png");
	loadimage(&ks2, "res/ks2.png");
	loadimage(&jx1, "res/jx1.png");
	loadimage(&jx2, "res/jx2.png");
	loadimage(&fh1, "res/fh1.png");
	loadimage(&fh2, "res/fh2.png");
	initgraph(GARDEN_WIDTH, GARDEN_HIGH);
	
	int flag1 = 0;//���ñ����ж���ת
	int flag2 = 0;
	int flag3 = 0;
	while (1)
	{
		ExMessage  msg;
		BeginBatchDraw();//���û���
		putimage(30, 0, &zt, SRCPAINT);
		putimagePNG(41+30, 437, flag1 ? &fh2 : &fh1);//���Ϊ�����ײ�ʵ����ת
		putimagePNG(626+30, 431, flag2 ? &ks2 : &ks1);
		putimagePNG(340+30, 528, flag3 ? &jx2 : &jx1);
		putimage(551+100-20+30, 160+60, &yl[j]);
		if (peekmessage(&msg))//�ж��Ƿ���,����Ϊѡ���ɿ�Ϊ��ת
		{

			if (msg.message == WM_LBUTTONDOWN && msg.x > 411+100+30 && msg.x < 465+100+30 && msg.y > 250&& msg.y < 293)
			{
				//������

				volume1();
			}

			if (msg.message == WM_LBUTTONDOWN && msg.x > 474+100+20 + 30 && msg.x < 536 +100+20 + 30 && msg.y > 241+20 && msg.y < 288+20)
			{
				//������
				volume2();

			}
			if (msg.message == WM_LBUTTONDOWN && msg.x > 171 + 30 && msg.x < 245 + 30 && msg.y > 108 && msg.y < 150)
			{
				//ѡ��1
				music1();
			}
			if (msg.message == WM_LBUTTONDOWN && msg.x > 168 + 30 && msg.x < 238 + 30 && msg.y > 197 && msg.y <235)
			{
				//ѡ��2
				music2();
			}
			if (msg.message == WM_LBUTTONDOWN && msg.x > 172 + 30 && msg.x < 238 + 30 && msg.y > 279&& msg.y < 333)
			{
				//ѡ��3
				music3();
			}
			if (msg.message == WM_LBUTTONDOWN && msg.x > 41 + 30 && msg.x < 259 + 30 && msg.y >432 && msg.x < 473)
			{
				flag1 = 1;

			}
			else if (msg.message == WM_LBUTTONUP && flag1 == 1)
			{

				//return ;
				//������Ϸ
			}
			if (msg.message == WM_LBUTTONDOWN && msg.x > 526 + 100 + 30 && msg.x < 716 + 30 && msg.y >431 && msg.y < 476)
			{
				flag2 = 1;

			}
			else if (msg.message == WM_LBUTTONUP && flag2 == 1)
			{

				//return ;
				//���¿�ʼ
			}
			if (msg.message == WM_LBUTTONDOWN && msg.x > 340 + 30 && msg.x < 474 + 30 && msg.y >530 && msg.x < 586)
			{
				flag3 = 1;

			}
			else if (msg.message == WM_LBUTTONUP && flag3 == 1)
			{

				//return ;
				//������Ϸ

			}
			EndBatchDraw();//��������

		}
	}
}

int main()
{
	music1();//���ų�ʼ����
	initdelt();
	system("pause");
	return 0;
}
#include<stdio.h>
#include<easyx.h>
#include<graphics.h>
#include<windows.h>
#include"yin.h"
#pragma comment(lib,"winmm.lib")
void sign_up_view()
{

}
int sign_up_judgment()
{
	return 0;
}
int main()
{
	music1();//���ų�ʼ����
	MOUSEMSG m;
	IMAGE img;
	loadimage(&img, "res/bg.png");
	initgraph(GARDEN_WIDTH, GARDEN_HIGH);//��ͼ
	putimage(50, 0, &img, SRCPAINT);//��ͼ
	IMAGE yl[10];
	char name[64];
	sprintf_s(name, sizeof(name), "ylt/yl%d.png", j);//��ʼ��������
	loadimage(&yl[j], name);
	putimagePNG(323+50, 175, &yl[j]);

	while(1)
	{
		if (MouseHit())//�ж��Ƿ��е��
		{
			m = GetMouseMsg();
			switch (m.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (m.x > 114 +50&& m.x < 308+50 && m.y > 66 && m.y < 158)
				{
					//������
					
					volume1();
				}
					
				if (m.x > 508+50 && m.x < 733+50 && m.y > 97 && m.y < 155)
				{
					//������
					volume2();
				}
				if (m.x > 398+50&& m.x < 487+50 && m.y > 209 && m.y < 263)
				{
					//ѡ��1
					music1();
				}
				if (m.x > 397+50 && m.x < 493+50 && m.y < 352 && m.y >321)
				{
					//ѡ��2
					music2();
				}
				if (m.x > 384+50 && m.x < 499+50 && m.y > 400 && m.y < 447)
				{
					//ѡ��3
					music3();
				}
				if (m.x > 398+50 && m.x < 487+50 && m.y > 209 && m.y < 263)
				{
					//�������˵�
					sign_up_view();
				}
				
					
				break;
				
			}
		}
		
	}
	system("pause");

	return 0;
}
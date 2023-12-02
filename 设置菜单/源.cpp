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
	music1();//播放初始音乐
	MOUSEMSG m;
	IMAGE img;
	loadimage(&img, "res/bg.png");
	initgraph(GARDEN_WIDTH, GARDEN_HIGH);//开图
	putimage(50, 0, &img, SRCPAINT);//放图
	IMAGE yl[10];
	char name[64];
	sprintf_s(name, sizeof(name), "ylt/yl%d.png", j);//初始化音亮条
	loadimage(&yl[j], name);
	putimagePNG(323+50, 175, &yl[j]);

	while(1)
	{
		if (MouseHit())//判断是否有点击
		{
			m = GetMouseMsg();
			switch (m.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (m.x > 114 +50&& m.x < 308+50 && m.y > 66 && m.y < 158)
				{
					//音量加
					
					volume1();
				}
					
				if (m.x > 508+50 && m.x < 733+50 && m.y > 97 && m.y < 155)
				{
					//音量减
					volume2();
				}
				if (m.x > 398+50&& m.x < 487+50 && m.y > 209 && m.y < 263)
				{
					//选择1
					music1();
				}
				if (m.x > 397+50 && m.x < 493+50 && m.y < 352 && m.y >321)
				{
					//选择2
					music2();
				}
				if (m.x > 384+50 && m.x < 499+50 && m.y > 400 && m.y < 447)
				{
					//选择3
					music3();
				}
				if (m.x > 398+50 && m.x < 487+50 && m.y > 209 && m.y < 263)
				{
					//返回主菜单
					sign_up_view();
				}
				
					
				break;
				
			}
		}
		
	}
	system("pause");

	return 0;
}
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include"tools.h"
#define SCREEN_WIDTH 900
#define SCREEN_HIGH 600
void Levle_choose_view()
{
	IMAGE mag1;//选关界面
	IMAGE ima1,ima2,ima3,ima4;//按钮图片
	loadimage(&mag1, "图片/选关界面.jpg", SCREEN_WIDTH, SCREEN_HIGH);
	loadimage(&ima1, "图片/按钮1.png", 90, 30);
	loadimage(&ima2, "图片/按钮2.png", 90, 30);
	loadimage(&ima3, "图片/按钮1.png", 200, 40);
	loadimage(&ima4, "图片/按钮1.png", 200, 40);
	int flag = 1;
	while (1)
	{
		BeginBatchDraw();
		putimage( 0, 0, &mag1);
		putimagePNG(100, 300, flag ? &ima1 : &ima2 );
		putimagePNG(250, 300, flag ? &ima1 : &ima2 );
		putimagePNG(400, 300, flag ? &ima1 : &ima2 );
		putimagePNG(550, 300, flag ? &ima1 : &ima2 );
		putimagePNG(700, 300, flag ? &ima1 : &ima2 );
		putimagePNG(350, 515, flag ? &ima3 : &ima4 );
		ExMessage m;
		if (peekmessage(&m, EX_MOUSE))
		{
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 100 && m.y >= 300 && m.x <= 100 + 90 && m.y <= 300 + 30)
				{
					//调用关卡1
					break;
				}
				
			}
		
		}
		if (peekmessage(&m, EX_MOUSE))
		{
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 250 && m.y >= 300 && m.x <= 250 + 90 && m.y <= 300 + 30)
				{
					//调用关卡2
					break;
				}

			}

		}
		if (peekmessage(&m, EX_MOUSE))
		{
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 400 && m.y >= 300 && m.x <= 400 + 90 && m.y <= 300 + 30)
				{
					//调用关卡3
					break;
				}

			}

		}
		if (peekmessage(&m, EX_MOUSE))
		{
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 550 && m.y >= 300 && m.x <= 550 + 90 && m.y <= 300 + 30)
				{
					//调用关卡4
					break;
				}

			}

		}
		if (peekmessage(&m, EX_MOUSE))
		{
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 700 && m.y >= 300 && m.x <= 700 + 90 && m.y <= 300 + 30)
				{
					//调用关卡5
					break;
				}

			}

		}
		if (peekmessage(&m, EX_MOUSE))
		{
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 350 && m.y >= 515 && m.x <= 350 + 200 && m.y <= 515 + 40)
				{
					//返回主菜单
					break;
				}

			}

		}

	}
}
int main()
{
	initgraph(SCREEN_WIDTH, SCREEN_HIGH);
	Levle_choose_view();
	getchar();
	closegraph();
	return 0;
}
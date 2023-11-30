#include"state.h"

void InitImages() {
	//地图
	loadimage(&g[0], _T("./imgs/map/garden.jpg"), GARDEN_WIDTH, GARDEN_HIGH);
	loadimage(&g[1], _T("./imgs/map/garden2.jpg"), GARDEN_WIDTH, GARDEN_HIGH);
	//组件
	loadimage(&s[0], _T("./imgs/screen/PanelBackground.png"));
	loadimage(&s[1], _T("./imgs/screen/ChooserBackground.png"));
	loadimage(&s[2], _T("./imgs/screen/StartButton.png"));
	//卡片文件
	loadimage(&c[0], _T("./imgs/cards/card_1.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[1], _T("./imgs/cards/card_2.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[2], _T("./imgs/cards/card_3.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[3], _T("./imgs/cards/card_4.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[4], _T("./imgs/cards/card_hypnoshroom.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[5], _T("./imgs/cards/card_iceshroom.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[6], _T("./imgs/cards/card_jalapeno.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[7], _T("./imgs/cards/card_potatomine.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[8], _T("./imgs/cards/card_puffshroom.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[9], _T("./imgs/cards/card_repeaterpea.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[10], _T("./imgs/cards/card_scaredyshroom.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[11], _T("./imgs/cards/card_snowpea.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[12], _T("./imgs/cards/card_spikeweed.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[13], _T("./imgs/cards/card_squash.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[14], _T("./imgs/cards/card_sunshroom.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[15], _T("./imgs/cards/card_threepeashooter.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[16], _T("./imgs/cards/card_wallnut.png"), CARDS_WIDTH, CARDS_HIGH);
	//加载植物
	memset(p, 0, sizeof(p));
	for (int i = 0; i < 13; i++)
	{
		char name[60];
		sprintf_s(name, sizeof(name),"res/zhiwu/0/%d.png", i+1);
		p[0][i] = (IMAGE*)malloc(sizeof(IMAGE));
		loadimage(p[1][i], name);
	}
	for (int i = 0; i < 18; i++)
	{
		sprintf_s(name, sizeof(name), "res/zhiwu/1/%d.png", i+1);
		p[1][i] = (IMAGE*)malloc(sizeof(IMAGE));
		loadimage(p[1][i], name);
	}
	for (int i = 0; i < 13; i++)
	{
		sprintf_s(name, sizeof(name), "res/zhiwu/2/%d.png", i+1);
		p[2][i] = (IMAGE*)malloc(sizeof(IMAGE));
		loadimage(p[2][i], name);
	}
	for (int i = 0; i < 8; i++)
	{
		sprintf_s(name, sizeof(name), "res/zhiwu/qqq%d.png", i + 1);
		p[3][i] = (IMAGE*)malloc(sizeof(IMAGE));
		loadimage(p[3][i], name);
	}
	for (int i = 0; i < 8; i++)
	{
		sprintf_s(name, sizeof(name), "res/zhiwu/HypnoShroom%d.png", i + 1);
		p[4][i] = (IMAGE*)malloc(sizeof(IMAGE));
		loadimage(p[4][i], name);
	}
	for (int i = 0; i < 8; i++)
	{
		sprintf_s(name, sizeof(name), "res/zhiwu/SnowPea%d.png", i + 1);
		p[11][i] = (IMAGE*)malloc(sizeof(IMAGE));
		loadimage(p[11][i], name);
	}
	for (int i = 0; i < 8; i++)
	{
		sprintf_s(name, sizeof(name), "res/zhiwu/Repeater%d.png", i + 1);
		p[9][i] = (IMAGE*)malloc(sizeof(IMAGE));
		loadimage(p[9][i], name);
	
	}
	for (int i = 0; i < 8; i++)
	{
		sprintf_s(name, sizeof(name), "res/zhiwu/zz%d.png", i + 1);
		p[16][i] = (IMAGE*)malloc(sizeof(IMAGE));
		loadimage(p[16][i], name);

	}
	//加载阳光
	for (int i = 0; i < 29; i++)
	{
		sprintf_s(name, sizeof(name), "res/sunshine/%d.png", i + 1);
		loadimage(&shine[i], name);
	}
	//加载植物栏
	loadimage(&plantlist, "res/bar4.png");
	//加载僵尸
	for (int i = 0; i < 20; i++)
	{
		sprintf_s(name, sizeof(name), "res/zm/%d.png", i + 1);
		loadimage(z[0][i], name);  //走
	}
	for (int i = 0; i < 20; i++)
	{
		sprintf_s(name, sizeof(name), "res/zm_eat/%d.png", i + 1);
		loadimage(z[1][i], name);     //吃
	}
	for (int i = 0; i < 20; i++)
	{
		sprintf_s(name, sizeof(name), "res/zm_dead/%d.png", i + 1);
		loadimage(z[2][i], name);     //死
	}
}

//开始前的动画和携带的植物的选择
void Star_game_view() {
	BeginBatchDraw();
	putimage(garden.x, garden.y, &g[0]);
	FlushBatchDraw();
	Sleep(3000);//按照原版游戏等待几秒
	while (garden.x > -(GARDEN_WIDTH - SCREEN_WIDTH))//在视角移动到最右边前保持移动
	{
		if (Timer(20, 0))
		{
			cleardevice();
			garden.speed = 10 - pow(garden.x + (GARDEN_WIDTH - SCREEN_WIDTH) / 2, 2) / (pow((GARDEN_WIDTH - SCREEN_WIDTH) / 2, 2) / 9);//通过这个运算实现从慢到快再到慢的平滑的地图移动
			garden.x -= garden.speed;
			putimage(garden.x, garden.y, &g[0]);
			FlushBatchDraw();
			/*printf("%d %d\n", garden.speed, garden.x);*///检查器
		}
	}
	plants_choose_view();
	while (garden.x < -125)
	{
		if (Timer(20, 0))
		{
			cleardevice();
			garden.speed = 7 - pow(garden.x + (GARDEN_WIDTH - SCREEN_WIDTH + 125) / 2, 2) / (pow((GARDEN_WIDTH - SCREEN_WIDTH) / 2, 2) / 9);//同上 为了实现变速运动
			garden.x += garden.speed;
			/*printf("%d", garden.speed);*///速度检查器
			putimage(garden.x, garden.y, &g[0]);
			printf("%d %d", garden.speed, garden.x);
			FlushBatchDraw();
		}
	}
	printf("\n");
	EndBatchDraw();
}
void plants_choose_view() {

	Lb = initAarry(8);//初始化背包植物的线性表
	while (1)
	{
		ExMessage m = getmessage(EX_MOUSE);
		//底层图片的打印
		putimage(garden.x, garden.y, &g[0]);//地图
		putimage(0, 87, &s[0]);
		putimage(0, 0, &s[1]);
		if (m.x > 150 && m.x < 304 && m.y>548 && m.y < 585)
		{
			putimage(155, 548, &s[2]);//开始游戏按钮的动效（当鼠标移动到按钮位置时候按钮发光）
		}
		//仓库卡片的打印
		int num = 0;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				putimage(20 + CARDS_WIDTH * j, 122 + CARDS_HIGH * i, &c[num]);
				if (!find(&Lb, num))
				{
					setbkmode(TRANSPARENT);
					settextcolor(RED);
					settextstyle(16, 0, _T("Consolas"));
					outtextxy(20 + CARDS_WIDTH * j, 122 + CARDS_HIGH * (i + 0.4), "Selected");
				}
				num++;
			}
		}
		//已经选择携带的卡片的打印
		for (int i = 0; i < Lb.size; i++)
		{
			putimage(82 + CARDS_WIDTH * i, 5, &c[Lb.id[i]]);
		}

		//检测鼠标操作
		int choose_id = 0;
		int id = 0;
		int re = 0;
		if (m.message == WM_LBUTTONDOWN)
		{
			//选择卡片的操作
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					//判断具体的点击位置
					if (m.x > 20 + CARDS_WIDTH * j && m.x < 20 + CARDS_WIDTH * (j + 1) && m.y >122 + CARDS_HIGH * i && m.y < 122 + CARDS_HIGH * (i + 1))
					{

						choose_id = id;//将选择的植物id传递
						printf("%d\n", choose_id);//后台检查用
						//确认此植物没有被选择后添加到线性表中
						if (find(&Lb, id))
						{
							add(&Lb, choose_id);
						}
						int re = 1;
						break;
					}
					id++;
					if (id > 16)
					{
						re = 1;
						break;
					}
				}
				if (re)
				{
					break;
				}
			}
			//删除卡片的操作
			for (int i = 0; i < Lb.size; i++)
			{
				if (m.x > 82 + CARDS_WIDTH * i && m.x < 82 + CARDS_WIDTH * (i + 1) && m.y > 5 && m.y < 5 + CARDS_HIGH)
				{
					del(&Lb, i);
				}
			}
			//跳出操作
			if (m.x > 150 && m.x < 304 && m.y>548 && m.y < 585)
			{
				break;
			}
		}

		FlushBatchDraw();
	}
}
void text() {
	for (int i = 0; i < 10; i++)
	{
		line(128 + 81 * i, 90, 128 + 81 * i, 565);
	}
	for (int i = 0; i < 6; i++)
	{
		line(128, 90 + 95 * i, 857, 90 + 95 * i);
	}
	FlushBatchDraw();
}
void zombie_creat_time(clock_t startime) {

	clock_t nowtime = clock();
	long interbal = nowtime - startime;
	static int i = 1;
	if (interbal == 5000 && i == 1)
	{
		printf("%ld %ld\t第%d波\n", startime, nowtime, i);
		zombie_creat();
		i++;
	}
	if (interbal == 10000 && i == 2)
	{
		printf("%ld %ld\t第%d波\n", startime, nowtime, i);
		zombie_creat();
		i++;
	}
	if (interbal == 15000 && i == 3)
	{
		printf("%ld %ld\t第%d波\n", startime, nowtime, i);
		zombie_creat();
		i++;
	}
	if (interbal == 20000 && i == 4)
	{
		printf("%ld %ld\t第%d波\n", startime, nowtime, i);
		zombie_creat();
		i++;
	}
	if (interbal == 25000 && i == 5)
	{
		printf("%ld %ld\t第%d波\n", startime, nowtime, i);
		zombie_creat();
		i++;
	}
}


//改了initplant（）和plant（）函数 换成curplant

//void initplant() {
//	for (int i = 0; i < 9; i++)
//	{
//		for (int j = 0; j < 5; j++)
//		{
//			inner_game_map[i][j]->number = 0;
//			inner_game_map[i][j]->flag = 0;
//			inner_game_map[i][j]->Info->x = 128 + 81 * i;
//			inner_game_map[i][j]->Info->y = 90 + 95 * j;
//		}
//	}
//}
//
//void plant() {
//
//	ExMessage msg;
//	static int SetHp_Judge = 1;//为了后续操作中使种下的植物的初始hp只定义一次，定义此静态局部变量
//
//	static int pick = -1;//！！！我感觉这里这个pick在gameview循环的时候好像会出问题，这个pick可能需要弄成全局变量！！！
//
//
//	if (peekmessage(&msg, EX_MOUSE))//当有鼠标操作
//	{
//
//		if (WM_LBUTTONDOWN)//当接收到鼠标左键点击时进入循环
//		{
//
//			//识别是否点击植物栏
//			/*1.判断位置
//			* 2.该植物的cd是否好了
//			*/
//			clock_t click_time = clock();
//			for (int i = 0; i < 10; i++)
//			{
//				if (msg.y > 0 && msg.y < CARDS_HIGH)         //位置？？？？？？？？？？
//				{
//					if (msg.x > 86 + 55.5 * i + (55.5 - CARDS_WIDTH) && msg.x < 86 + 55.5 * (i + 1) - (55.5 - CARDS_WIDTH))
//					{
//						if (click_time - Lb.plant_time[i] > plants_in[Lb.id[i]].cd)
//						{
//							pick = i;//pick为选择栏的选择的植物的序号
//						}
//
//					}
//				}
//
//			}
//			//判断鼠标选择的草皮的位置
//			for (int i = 0; i < 9; i++)
//			{
//				if (pick == -1)
//				{
//					break;
//				}
//				else
//				{
//					if (msg.x > 128 + 81 * i && msg.x < 128 + 81 * (i + 1))
//					{
//						for (int j = 0; j < 5; j++)
//						{
//							if (msg.y > 90 + 95 * i && msg.y < 90 + 95 * (i + 1))
//							{
//								if (inner_game_map[i][j]->flag == 0)
//								{
//									inner_game_map[i][j]->flag = 1;
//									inner_game_map[i][j]->number = pick; /*顺序表的植物位置*/
//									inner_game_map[i][j]->id = Lb.id[pick];
//									//1.放置后的植物进入cd状态
//									//暂时不知道怎么写。。。
//									Lb.plant_time[pick] = clock();
//
//									//添加已种植的植物信息
//									inner_game_map[i][j]->Info->ID = Lb.id[pick];
//
//									if (SetHp_Judge == 1)
//									{
//										//下面这句怎么写？？？怎么根据ID去找对应的植物的hp？？？
//										inner_game_map[i][j]->Info->hp = plants_in[i].HP;//顺序表第n个的对应植物的总hp值
//
//
//
//
//										SetHp_Judge == 0;//使种下的植物的初始hp只定义一次（此处若直接static hp会在植物死掉后再在此地种植时出问题，故我目前选择这么操作）
//									}
//									//选择的植物pick状态取消
//									pick = -1;
//								}
//
//								else if (inner_game_map[i][j]->flag != 0)
//								{
//									pick = -1;
//
//								}
//							}
//						}
//
//					}
//				}
//
//			}
//		}
//
//
//	}
//
//	//将草皮格子中处于空地状态的信息标为0  
//	for (int i = 0; i < 9; i++)
//	{
//		for (int j = 0; j < 5; j++)
//		{
//			if (inner_game_map[i][j]->flag == 0)
//			{
//				inner_game_map[i][j]->number = 0;
//				inner_game_map[i][j]->Info->ID = -1;
//				inner_game_map[i][j]->Info->hp = 0;
//				SetHp_Judge = 1;
//			}
//		}
//	}
//
//
//}
// 





void inituser()
{
	memset(user.data, 0, sizeof(Userdata) * 99);
	user.n = 0;
}

//绘制登录注册首菜单
void mainmenu_draw()
{
	cleardevice();
	setbkmode(TRANSPARENT);
	//设置背景图片 Menu/登录界面
	IMAGE img;
	loadimage(&img, "主菜单.png");
	putimagePNG(0, 0, &img);


	int x = 270;		//方框栏的起始X坐标
	int y = 170;		//方框栏的起始Y坐标
	int rx = 120;		//方框栏的X长度
	int ry = 90;		//方框栏的Y长度

	setfillcolor(RGB(126, 147, 158));
	solidrectangle(0, 170, 0 + 120, 170 + 50);	//普通模式按钮方框

	solidrectangle(0, 240, 0 + 120, 240 + 50);	//图鉴按钮

	solidrectangle(0, 310, 0 + 120, 310 + 50);	//设置按钮

	solidrectangle(0, 380, 0 + 120, 380 + 50);	//制作名单按钮

	solidrectangle(0, 100, 0 + 120, 100 + 50);	//制作登录按钮

	solidrectangle(0, 450, 0 + 120, 450 + 50);	//制作退出按钮


	char text1[] = "普通模式";
	char text2[] = "图鉴";
	char text3[] = "设置";
	char text4[] = "制作名单";
	char text5[] = "登录";
	char text6[] = "退出";

	settextcolor(BLACK);
	settextstyle(30, 0, "微软雅黑");

	//打印普通模式字体
	outtextxy(0 + (120 - textwidth(text1)) / 2, 170 + (50 - textheight(text1)) / 2, text1);

	//打印图鉴模式字体
	outtextxy(0 + (120 - textwidth(text2)) / 2, 240 + (50 - textheight(text2)) / 2, text2);

	//打印设置字体
	outtextxy(0 + (120 - textwidth(text1)) / 2, 310 + (50 - textheight(text1)) / 2, text3);

	//打印制作名单字体
	outtextxy(0 + (120 - textwidth(text1)) / 2, 380 + (50 - textheight(text1)) / 2, text4);

	//打印登录字体
	outtextxy(0 + (120 - textwidth(text5)) / 2, 100 + (50 - textheight(text5)) / 2, text5);

	outtextxy(0 + (120 - textwidth(text6)) / 2, 450 + (50 - textheight(text6)) / 2, text6);

	FlushBatchDraw();
}

//登录注册首菜单
void main_menu()
{
	cleardevice();
	mainmenu_draw();
	while (true)
	{
		ExMessage msg;
		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				//进入登录注册界面
				if (msg.x >= 0 && msg.x <= 0 + 120 && msg.y >= 100 && msg.y <= 100 + 50)
				{
					printf("登录\n");
					initfileGet();		//将原来文件里用户的数据复制过来
					Register();			//登录注册的界面
					break;

				}
				else if (msg.x >= 0 && msg.x <= 0 + 120 && msg.y >= 450 && msg.y <= 450 + 50)
				{
					printf("退出\n");
					initfileAdd();						//将所注册的用户信息保存
					//退出函数
					exit(0);
					mainmenu_draw();			//返回到游戏开始界面
					break;
				}
				else if (msg.x >= 0 && msg.x <= 0 + 120 && msg.y >= 170 && msg.y <= 170 + 50)
				{
					printf("普通模式\n");
					Levle_choose_view();
					break;
				}
				else if (msg.x >= 0 && msg.x <= 0 + 120 && msg.y >= 310 && msg.y <= 310 + 50)
				{
					printf("设置\n");
					break;
				}
				else if (msg.x >= 0 && msg.x <= 0 + 120 && msg.y >= 240 && msg.y <= 240 + 50)
				{
					printf("图鉴模式\n");
					break;
				}
				else if (msg.x >= 0 && msg.x <= 0 + 120 && msg.y >= 380 && msg.y <= 380 + 50)
				{
					printf("制作名单\n");
				}
			default:
				break;
			}
		}

	}
}

void RegisterDraw()
{
	cleardevice();
	BeginBatchDraw();
	setbkcolor(GREEN);
	cleardevice();
	char text1[] = "用户名";
	char text2[] = "密码";
	char text3[] = "登录";
	char text5[] = "注册";
	char text6[] = "退出";
	char text7[99] = { 0 };
	char text8[99] = { 0 };
	setfillcolor(WHITE);

	fillrectangle(310, 180, 310 + 280, 180 + 40);		//设置用户名的框
	fillrectangle(310, 240, 310 + 280, 240 + 40);		//设置密码的框

	fillrectangle(290, 320, 290 + 90, 320 + 50);		//登录的框

	fillrectangle(520, 320, 520 + 90, 320 + 50);		//注册的框

	fillrectangle(315, 410, 315 + 250, 410 + 60);		//退出的框

	settextcolor(BLACK);

	//打印 用户名 的字
	outtextxy(310 - textwidth(text1), (40 - textheight(text1)) / 2 + 180, text1);

	//打印密码的字
	outtextxy(310 - textwidth(text2), (40 - textheight(text2)) / 2 + 240, text2);


	if (!signname)	//当signname 为 0 时打印输入用户名
	{
		outtextxy(310, 180, name);
	}
	if (!signpassword && sign3)	////当signpassword 为 0 时打印输入密码
	{
		outtextxy(310, 240, "******");
	}

	//打印登录字体
	outtextxy(290 + (90 - textwidth(text3)) / 2, (50 - textheight(text3)) / 2 + 320, text3);

	//打印注册字体
	outtextxy(520 + (90 - textwidth(text5)) / 2, (50 - textheight(text5)) / 2 + 320, text5);

	//打印退出字体
	outtextxy(315 + (250 - textwidth(text6)) / 2, (60 - textheight(text5)) / 2 + 410, text6);

	EndBatchDraw();
}


//登录菜单
void Register()
{
	RegisterDraw();
	ExMessage msg;
	while (true)
	{

		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				//进行输入用户名操作
				if (msg.x >= 310 && msg.x <= 310 + 280 && msg.y >= 180 && msg.y <= 180 + 40)
				{
					printf("用户名\n");
					signname = 0;					//当signname为0时可以打印输入用户名
					InputBox(name, 10, "输入名字");
					RegisterDraw();					//使得用户名显示
					break;
				}
				else if (msg.x >= 310 && msg.x <= 310 + 280 && msg.y >= 240 && msg.y <= 240 + 40)
				{
					printf("密码\n");
					signpassword = 0;				//当signpassword为0时可以打印输入密码
					InputBox(password, 10, "密码");
					sign3 = 1;
					RegisterDraw();					//使得密码显示
					break;
				}
				else if (msg.x >= 290 && msg.x <= 290 + 90 && msg.y >= 320 && msg.y <= 320 + 50)
				{

					printf("登录\n");
					int flag1 = 0;
					int flag2 = 0;
					for (int i = 0; i < user.n; i++)
					{
						//与注册的用户信息进行比对
						if (strcmp(name, user.data[i].name) == 0 && name)
						{
							flag1 = 1;
						}
						if (strcmp(password, user.data[i].password) == 0 && password)
						{
							flag2 = 1;
						}
					}
					if (flag1 == 0)
					{
						printf("用户名错误\n");
						MessageBox(GetHWnd(), "用户名不存在或者错误", "警告!!!", MB_OK);
						RegisterDraw();
					}
					else if (flag2 == 0)
					{
						printf("密码错误\n");
						MessageBox(GetHWnd(), "密码错误", "警告!!!", MB_OK);
						RegisterDraw();
					}
					else if (flag1 && flag2)
					{
						printf("登录成功\n");
						signname = signpassword = 1;		//放在进入游戏开始界面时进入登录主菜单显示信息
						MessageBox(GetHWnd(), "登录成功", "恭喜!!!", MB_OK);
						main_menu();							//进入游戏开始界面
					}
					break;
				}
				else if (msg.x >= 520 && msg.x <= 520 + 90 && msg.y >= 320 && msg.y <= 320 + 50)
				{
					printf("注册\n");
					addUserdata();		//进行注册账号操作
					break;
				}
				else if (msg.x >= 260 && msg.x <= 260 + 250 && msg.y >= 410 && msg.y <= 410 + 60)
				{
					printf("退出\n");
					signname = signpassword = 1;		//防止再次进入登录界面显示用户的信息
					sign3 = 0;
					main_menu();							//进入登录注册主菜单
					break;
				}
			default:
				break;
			}
		}
	}
}

//注册用户信息
void addUserdata()
{
	addUserdatadraw();//绘制用户信息界面

	while (true)
	{
		ExMessage msg;
		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				//进行输入注册用户名的操作
				if (msg.x >= 310 && msg.x <= 310 + 280 && msg.y >= 190 && msg.y <= 190 + 40)
				{
					printf("输入用户名\n");
					signnameadd = 0;			//当signnameadd为0时打印输入用户名内容
					signname = 0;				//signname为0时防止进入登录注册菜单显示用户用户名信息
					InputBox(user.data[user.n].name, 40, "请输入用户名");
					addUserdatadraw();			//打印出输入的用户名信息
					break;
				}
				else if (msg.x >= 310 && msg.x <= 310 + 280 && msg.y >= 250 && msg.y <= 250 + 40)
				{
					printf("输入密码\n");
					sign1 = 1;					//打印隐藏密码信息
					signpasswordadd = 0;		//当signpassworadd为0时打印输入密码内容
					signpassword = 0;			//signpassword为0时防止进入登录注册菜单显示用户密码信息
					InputBox(user.data[user.n].password, 40, "请输入密码");
					if (strlen(user.data[user.n].password))
					{
						passwordlen = 1;
					}
					addUserdatadraw();			////打印出输入的密码
					break;
				}
				else if (msg.x >= 310 && msg.x <= msg.x <= 310 + 280 && msg.y >= 310 && msg.y <= 310 + 40)
				{

					InputBox(passwordagain, 40, "请确认密码");
					signpasswordaddagain = 0;	//当signpassworaddagain为0时打印输入密码内容
					sign2 = 1;				//打印隐藏密码信息
					if (strlen(passwordagain))
					{
						passwordlen = 1;
					}
					addUserdatadraw();
					break;
				}
				else if (msg.x >= 290 && msg.x <= 290 + 90 && msg.y >= 380 && msg.y <= 380 + 50)
				{
					int flag = 1;
					printf("注册\n");
					//判断两次输入的密码是否一致
					if (strcmp(passwordagain, user.data[user.n].password) == 0)
					{
						signpasswordaddagain = 0;		//当为0时打印打二次输入密码的内容
						addUserdatadraw();				//绘制
					}
					int ret = judeguser();				//判断注册的账号是否重复
					if (strcmp(passwordagain, user.data[user.n].password) != 0)
					{
						signpasswordaddagain = 1;		//清除二次输入的密码
						signpasswordadd = 1;			//清除一次输入的密码
						MessageBox(GetHWnd(), "两次密码输入不一致,请重新输入", "警告！！！", MB_OK);
						addUserdatadraw();
					}
					else if (ret)				//账号不重复
					{
						namelen = strlen(user.data[user.n].name);
						passwordlen = strlen(user.data[user.n].password);

						if (namelen > 10 || passwordlen > 20 || namelen == 0 || passwordlen == 0)
						{
							printf("错误");
							MessageBox(GetHWnd(), "账号或者密码不规范", "警告！！！", MB_OK);
							flag = 0;
						}
						else if (flag && namelen <= 10 && passwordlen <= 20)
						{

							MessageBox(GetHWnd(), "注册成功", "恭喜！！！", MB_OK);
							printf("%s %s\n", user.data[user.n].name, user.data[user.n].password);
							user.n++;


						}
						printf("注册成功\n");
					}
					else if (ret == 0)			//账号重复
					{
						printf("账号重复\n");
						MessageBox(GetHWnd(), "账号重复", "警告！！！", MB_OK);
					}
					break;

				}
				else if (msg.x >= 520 && msg.x <= 520 + 90 && msg.y >= 380 && msg.y <= 380 + 50)
				{
					printf("返回\n");
					signnameadd = signpasswordadd = 1;		 //清除界面的内容
					signname = signpassword = 1;			 //清除界面的内容
					signpasswordaddagain = 1;				 //清除界面的内容
					Register();								//反回到登录主菜单
					sign1 = sign2 = 0;
					namelen = passwordlen = 0;
					break;
				}
			default:
				break;
			}
		}
	}

}
void addUserdatadraw()
{
	char text1[] = "用户名";
	char text2[] = "密码";
	char text3[] = "注册";
	char text5[] = "返回";
	char text6[] = "确认密码";

	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "注册");

	setbkcolor(GREEN);
	cleardevice();

	fillrectangle(310, 190, 310 + 280, 190 + 40);		//打印用户名的框

	fillrectangle(310, 250, 310 + 280, 250 + 40);		//打印输入密码的框

	fillrectangle(310, 310, 310 + 280, 310 + 40);		//打印再次输入密码的框

	fillrectangle(290, 380, 290 + 90, 380 + 50);		//打印注册按钮的框

	fillrectangle(520, 380, 520 + 90, 380 + 50);		//打印返回的框

	//打印用户名的文字
	outtextxy(310 - textwidth(text1), (40 - textheight(text1)) / 2 + 190, text1);

	//打印密码文字
	outtextxy(310 - textwidth(text2), (40 - textheight(text2)) / 2 + 250, text2);

	//打印再次输入密码文字
	outtextxy(310 - textwidth(text6), (40 - textheight(text6)) / 2 + 310, text6);

	if (!signnameadd)
	{
		//打印注册输入的账户名
		outtextxy(310, 190, user.data[user.n].name);
	}
	if (!signpasswordadd && sign1 && passwordlen != 0)
	{
		//打印注册输入的密码
		outtextxy(310, 250, "**********");
	}
	if (!signpasswordaddagain && sign2 && passwordlen != 0)
	{
		//打印注册再次输入的密码
		outtextxy(310, 310, "**********");
	}

	//打印注册文字
	outtextxy(290 + (90 - textwidth(text3)) / 2, (50 - textheight(text3)) / 2 + 380, text3);

	//打印返回文字
	outtextxy(520 + (90 - textwidth(text5)) / 2, (50 - textheight(text5)) / 2 + 380, text5);

}

//储存用户的信息
void initfileAdd()
{
	FILE* file;
	fopen_s(&file, "user/data.txt", "w");
	for (int i = 0; i < user.n; ++i)
	{
		fprintf(file, "%s %s\n", user.data[i].name, user.data[i].password);

	}
	fclose(file);
}

//将储存的信息读取出来
void initfileGet()
{
	int i = 0;
	FILE* file;
	fopen_s(&file, "user/data.txt", "r");
	if (file != NULL)
	{
		while ((fscanf_s(file, "%s %s\n", user.data[i].name, user.data[i].password)) != EOF)
		{
			user.n++;
			i++;

		}
	}

}

//判断注册账号是否一致
int judeguser()
{

	for (int i = 0; i < user.n; ++i)
	{
		if (strcmp(user.data[user.n].name, user.data[i].name) == 0)		//用户名
		{
			//账号重复
			return 0;
		}
	}
	return 1;
}





void Levle_choose_view()
{
	IMAGE mag1;//选关界面
	IMAGE ima1, ima2, ima3, ima4;//按钮图片
	IMAGE tu1, tu2, tu3, tu4, tu5;//关卡图标
	loadimage(&mag1, "imgs/l_choose_img/选关界面.jpg", SCREEN_WIDTH, SCREEN_HIGH);
	loadimage(&ima1, "imgs/l_choose_img/图片/按钮1.png", 90, 30);//鼠标没点时的 
	loadimage(&ima2, "imgs/l_choose_img/图片/按钮2.png", 90, 30);//鼠标点击时 
	loadimage(&ima3, "imgs/l_choose_img/图片/返回键1.png", 200, 40);//鼠标没点时的 
	loadimage(&ima4, "imgs/l_choose_img/图片/返回键2.png", 200, 40);//鼠标点击时 
	loadimage(&tu1, "imgs/l_choose_img/图片/关卡1图标.png", 90, 90);
	loadimage(&tu2, "imgs/l_choose_img/图片/关卡2图标.png", 90, 90);
	loadimage(&tu3, "imgs/l_choose_img/图片/关卡3图标.png", 90, 90);
	loadimage(&tu4, "imgs/l_choose_img/图片/关卡4图标.png", 90, 90);
	loadimage(&tu5, "imgs/l_choose_img/图片/关卡5图标.png", 90, 90);
	int flag = 1;//设置点击时的图片细微变化 
	BeginBatchDraw();
	while (1)
	{

		putimage(0, 0, &mag1);
		putimagePNG(100, 300, flag ? &ima1 : &ima2);
		putimagePNG(250, 300, flag ? &ima1 : &ima2);
		putimagePNG(400, 300, flag ? &ima1 : &ima2);
		putimagePNG(550, 300, flag ? &ima1 : &ima2);
		putimagePNG(700, 300, flag ? &ima1 : &ima2);
		putimagePNG(350, 515, flag ? &ima3 : &ima4);
		putimagePNG(90, 200, &tu1);
		putimagePNG(240, 200, &tu2);
		putimagePNG(390, 200, &tu3);
		putimagePNG(540, 200, &tu4);
		putimagePNG(690, 200, &tu5);
		settextstyle(15, 10, "黑体");
		setbkmode(TRANSPARENT);
		settextcolor(RGB(30, 30, 30));
		outtextxy(115, 307, "关卡一");
		outtextxy(265, 307, "关卡二");
		outtextxy(415, 307, "关卡三");
		outtextxy(565, 307, "关卡四");
		outtextxy(715, 307, "关卡五");
		outtextxy(400, 527, "返回主菜单");
		settextstyle(38, 40, "黑体");
		setbkmode(TRANSPARENT);
		outtextxy(285, 32, "关卡选项");
		ExMessage m;
		if (peekmessage(&m, EX_MOUSE))//关卡1 
		{
			int ischoose = 0;
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 100 && m.y >= 300 && m.x <= 100 + 90 && m.y <= 300 + 30)
				{
					flag = 0;
					//调用关卡1
					level = 1;
					ischoose = 1;
					break;
				}
				if (m.x >= 250 && m.y >= 300 && m.x <= 250 + 90 && m.y <= 300 + 30)
				{
					flag = 0;
					//调用关卡2
					level = 2;
					ischoose = 1;
					break;
				}
				if (m.x >= 400 && m.y >= 300 && m.x <= 400 + 90 && m.y <= 300 + 30)
				{
					flag = 0;
					//调用关卡3
					level = 3;
					ischoose = 1;
					break;
				}
				if (m.x >= 550 && m.y >= 300 && m.x <= 550 + 90 && m.y <= 300 + 30)
				{
					flag = 0;
					//调用关卡4
					level = 4;
					ischoose = 1;
					break;
				}
				if (m.x >= 700 && m.y >= 300 && m.x <= 700 + 90 && m.y <= 300 + 30)
				{
					flag = 0;
					//调用关卡5
					level = 5;
					ischoose = 1;
					break;
				}
				if (m.x >= 350 && m.y >= 515 && m.x <= 350 + 200 && m.y <= 515 + 40)
				{
					flag = 0;
					//返回主菜单
					main_menu();
					break;
				}
			}
			if (ischoose)
			{
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	Star_game_view();
}

void game_init()
{
	/*char name[64];*/
	//int plantput[8];
	//plantput[0] = 1;
	//plantput[1] = 2;
	//plantput[2] = 3;
	////memset(m, 0, sizeof(m));
	

	int ballmax = sizeof(s) / sizeof(s[0]);
	for (int j = 0; j < ballmax; j++)
	{
		balls[j].isused = 0;
	}

	//loadimage(&g[0], "map/garden.jpg", GARDEN_WIDTH, GARDEN_HIGH); 初始化过了
	//loadimage(&plantlist, "res/bar4.png");
	//for (int i = 0; i <= 8; i++)  //先试两个       卡片已经初始化过了
	//{
	//	sprintf_s(name, sizeof(name), "res/Cards/card_%d.png", plantput[i]);
	//	loadimage(&c[i], name, CARDS_WIDTH, CARDS_HIGH);
	//}

	//loadimage(&imgBullet, "res/bullets/bullet_normal.png");
	//bullets = new bullet;   //创建子弹头指针
	//bullets->next = NULL;
	loadimage(&imgBulletBlast[3], "res/bullets/bullet_blast.png");
	for (int i = 0; i < 3; i++) {
		float k = (i + 1) * 0.2;
		loadimage(&imgBulletBlast[i], "res/bullets/bullet_blast.png",
			imgBulletBlast[3].getwidth() * k,
			imgBulletBlast[3].getheight() * k, true);
	}
	//loadimage()
	initgraph(SCREEN_WIDTH, SCREEN_HIGH);
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 30;                      // 设置字体高度为 48
	f.lfWidth = 15;
	strcpy_s(f.lfFaceName, "Segoe UI Black");
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	setbkmode(TRANSPARENT);
	setcolor(BLACK);

	//mciSendString("play res/bg.mp3 repeat", 0, 0, 0);



}
void createSunshine() {
	int ballMax = sizeof(s) / sizeof(s[0]);

	static int SunCount = 0;
	static int count = 400;
	SunCount++;
	if (SunCount >= count) {
		count = 200 + rand() % 200;
		SunCount = 0;
		int i;
		for (i = 0; i < ballMax && balls[i].isused; i++);
		if (i >= ballMax) return;

		balls[i].isused = 1;
		balls[i].frame = 0;
		balls[i].x = 125 + rand() % (905 - 260);
		balls[i].y = 60;
		balls[i].desty = 180 + (rand() % 4) * 90 + 20;
		balls[i].timer = 0;
	}
}
void updataSunshine()
{
	int ballmax = sizeof(s) / sizeof(s[0]);
	int i = 0;
	for (i; i < ballmax; i++)
	{
		if (balls[i].isused == 1)
		{
			balls[i].frame++;
			if (balls[i].frame == 29)
			{
				balls[i].frame = 0;
			}
			if (balls[i].y > balls[i].desty)
			{
				balls[i].timer++;
				if (balls[i].timer > 200)
				{
					balls[i].isused = 0;

				}
			}
			if (balls[i].timer == 0)
			{
				balls[i].y += 2;
			}
		}
	}





}
void collectSunshine(ExMessage* msg) {
	int count = sizeof(s) / sizeof(s[0]);
	int w = shine[0].getwidth();
	int h = shine[0].getheight();
	for (int i = 0; i < count; i++) {
		if (balls[i].isused) {
			int x = balls[i].x;
			int y = balls[i].y;
			if (msg->x > x && msg->x < x + w && msg->y > y && msg->y < y + h) {
				balls[i].isused = 0;
				sun += 25;
				mciSendString("play res/sunshine.mp3", 0, 0, 0);
			}
		}
	}
}
/*检查各个单位
负责人：幻風
功能：
( 以僵尸为视角检查 含义是逐个对比僵尸和其他链表的数据 )
1、对比僵尸链表和植物链表判断行动	按情况修改 该僵尸节点和植物节点 各自的 .isAtk 数据 以及植物的 .hp值 并判断死亡
2、根据所读到的僵尸的xy坐标 判断是否进入了房间 并修改小推车的 .isAtk 或者调用失败页面 defete_view()
2、触发特殊行为或者攻击
3、按 .buff 作不同反应
5、对应该消失的节点进行删除
*/

void _check(LinkList_z Znode)	//传入植物、僵尸、子弹的头结点(为空的头结点)
{
	LinkList_z zp = Znode, zpre = Znode;

	while (zp->next != NULL)
	{
		zp = zp->next;
		//根据僵尸坐标计算格子
		int i = 0, j = 0;
		switch ((zp->y - 90) / 95) //!! !! ! ! ! !!优化！！！！！
		{
		case 1:
			j = 0;
			break;
		case 2:
			j = 1;
			break;
		case 3:
			j = 2;
			break;
		case 4:
			j = 3;
			break;
		case 5:
			j = 4;
			break;
		}
		if (zp->x > 128)
			switch ((zp->x - 128) / 81)
			{
			case 1:
				i = 0;
				break;
			case 2:
				i = 1;
				break;
			case 3:
				i = 2;
				break;
			case 4:
				i = 3;
				break;
			case 5:
				i = 4;
				break;
			case 6:
				i = 5;
				break;
			case 7:
				i = 6;
				break;
			case 8:
				i = 7;
				break;
			case 9:
				i = 8;
				break;
			default:
				i = -1;
			}

		//判断僵尸是否死亡,删除节点，连上链表
		if (zp->hp <= 0)
		{
			zpre->next = zp->next;
			zombie_num[j]--;
			free(zp);
			zp = zpre->next;
		}

		////根据buff给予效果
		//switch (zp->buff)
		//{
		//case 1:

		//	break;
		//default:

		//	break;
		//}	

		//是否触发僵尸攻击
		if (i >= 0)
			if (inner_game_map[i][j].type != 0)
				zp->isAtk = 1;
			else zp->isAtk = 0;

		//触发小车
		if (zp->x <= 128)
			car[j].isAtk = 1;

		if (zp->x < 88);
		//defete_view();

		zpre = zpre->next;//前指针
	}

	//判断植物攻击
	for (int j = 0; j < 5; j++)
	{
		if (zombie_num[j] > 0)
			for (int i = 0; i < 9; i++)
				inner_game_map[i][j].isAtk = 1;    // 幻风这么写恐龙（我）打印子弹的时候还要再加个限制条件（id） 不然所有植物全射子弹了
		else
			for (int i = 0; i < 9; i++)
				inner_game_map[i][j].isAtk = 0;
	}

	//遍历数组判断植物是否死亡
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			/*if (inner_game_map[i][j]->flag == 0)*/ 
			if (inner_game_map[i][j].hp <= 0)		////？？？？？？？？？？什么意思 赋值？判断？          改了
				//if (inner_game_map[i][j].hp <= 0)
				inner_game_map[i][j].type = 0;        // inner_game_map[i][j]->number = 0;

		}
	}
}

/*僵尸行为以及动画加载
负责人：幻風
功能：
1、检查此僵尸节点的数据
	*检查 .buff数据异常 则按照异常要求行动
	*检查 .isAct  判断是否停下并攻击
	*若无以上 则向前行动
2、改变加载的图片文件
*/
void zombie_act(LinkList_z Znode)
{
	LinkList_z zp = Znode;
	int atk = 0;
	while (zp->next != NULL)
	{
		zp->frame = (zp->frame+1)%20
		putimage(zp->x, zp->y, &z[zp->ID]);
		if (zp->isAtk == 1)//记录攻击力
		{
			int atk = zombiein[zp->ID].Atk;
			zp->speed = 0; //攻击时停下
			
			//根据僵尸坐标计算格子
			int i = 0, j = 0;
			switch ((zp->y - 90) / 95)
			{
			case 1:
				j = 0;
				break;
			case 2:
				j = 1;
				break;
			case 3:
				j = 2;
				break;
			case 4:
				j = 3;
				break;
			case 5:
				j = 4;
				break;
			}
			if (zp->x > 128)
				switch ((zp->x - 128) / 81)
				{
				case 1:
					i = 0;
					break;
				case 2:
					i = 1;
					break;
				case 3:
					i = 2;
					break;
				case 4:
					i = 3;
					break;
				case 5:
					i = 4;
					break;
				case 6:
					i = 5;
					break;
				case 7:
					i = 6;
					break;
				case 8:
					i = 7;
					break;
				case 9:
					i = 8;
					break;
				default:
					i = -1;
				}
			//被攻击植物扣血
			inner_game_map[i][j].hp -= atk;
		}
		else zp->speed = zombiein[zp->ID].speed;//不攻击时运动
		//僵尸运动
		zp->x -= zp->speed;
		////改变图片
		//if (zp->hp <= zombiein[zp->ID].danmage_point);

		zp = zp->next;
	}
}


//gameview 里用到的函数
void userClick() {
	ExMessage msg;
	static int status = 0;
	if (peekmessage(&msg)) {
		if (msg.message == WM_LBUTTONDOWN) {
			if (msg.x > 86 && msg.x < 86 + 55 * 8 && msg.y < 90) {
				int index = (msg.x - 86) / 55;
				//printf("%d\n", index); 搞定
				status = 1;
				curZhiWu = Lb.id[index]; // 传来的存着选择植物的id的数组
				curX = msg.x;
				curY = msg.y;
			}
			else
			{
				collectSunshine(&msg);
			}
		}
		else if (msg.message == WM_MOUSEMOVE && status == 1) {
			curX = msg.x;
			curY = msg.y;
		}
		else if (msg.message == WM_LBUTTONUP && status == 1) {
			//printf("up\n"); 搞定
			if (msg.x > 128 && msg.x < 850 && msg.y > 90 && msg.y < 570) {
				if (sun >= plantshuzu[curZhiWu].cost) {    // plantshuzu是存所有植物的结构体数组 还没建呢
					sun -= plantshuzu[curZhiWu].cost;
					int col = (msg.x - 128) / 81;
					int row = (msg.y - 90) / 95;
					//printf("[%d,%d]\n", row, col); 搞定
					if (inner_game_map[col][row].type == 0) {
						inner_game_map[col][row].type = curZhiWu+1;
						inner_game_map[col][row].frameindex = 0;
					}
				}
			}

			status = 0;
			curZhiWu = 0;
		}
	}
}
void curplant()
{
	if (curZhiWu > 0) {  // 绘制正在移动的植物
		IMAGE* img = p[curZhiWu][0];   //植物图片   curzhiwu存的是（在plantshuzu结构体数组里）植物的id
		putimagePNG(curX - img->getwidth() * 0.5, curY - img->getheight() * 0.5, img);
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 5; j++) {
			if (inner_game_map[i][j].type > 0) {
				int x = 128 + i * 81 + 30;    //int col = (msg.x - 128) / 81;  未知
				int y = 90 + j * 95 + 70; 	//int row = (msg.y - 90) / 95;


				int zhiWuIndex = inner_game_map[i][j].type;
				int frameIndex = inner_game_map[i][j].frameindex;
				putimagePNG(x, y, p[zhiWuIndex][frameIndex]);    
			}
		}
	}

}
void zombie_creat() {
	srand((unsigned int)time(NULL));
	
	static int id = 1;
	int ret = rand() % 5 + 1;
	int x = 0, y = 0;
	switch (ret)
	{
	case 1:
		x = 900;
		y = 90;
		break;
	case 2:
		x = 900;
		y = 185;
		break;
	case 3:
		x = 900;
		y = 280;
		break;
	case 4:
		x = 900;
		y = 375;
		break;
	case 5:
		x = 900;
		y = 460;
		break;
	default:
		break;
	}
	Lz = add(Lz, id, x, y);
	print(Lz);
	printf("在第%d路\n\n", ret);
	id++;
}
void drawZombie(LinkList_z Znode)
{
	LinkList_z zp = Znode;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (inner_game_map[i][j].isAtk = 1)
			{
				
				putimagePNG(zp->x,zp->y,z[1][zp->frame]);
			}
			else
			{
				putimagePNG(zp->x, zp->y, z[0][zp->frame]);
			}
			
		}
	}
	
	
}
void window_updata()
{
	BeginBatchDraw();
	putimage(-125, 0, &g[0]);   //打印g[0]
	putimage(10, 0, &plantlist);
	//int n = 2;// 要打印的植物数量 建一个要打印植物的数组 将植物ID存进去
	for (int i = 0; i < 8; i++)
	{
		putimage(86 + i * 55, 5, &c[Lb.id[i]]);   
	}
	int ballmax = sizeof(s) / sizeof(s[0]);
	for (int i = 0; i < ballmax; i++)
	{
		if (balls[i].isused == 1)
		{
			putimagePNG(balls[i].x, balls[i].y, &shine[balls[i].frame]);
			
		}
	}
	curplant();
	drawZombie(Lz);

	char scoreText[8];
	sprintf_s(scoreText, sizeof(scoreText), "%d", sun);
	outtextxy(30, 55, scoreText);   // over
	EndBatchDraw();
}

void game_creat_updata()
{
	//更新植物
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			if (inner_game_map[i][j].type > 0) {
				inner_game_map[i][j].frameindex++;
				if (p[inner_game_map[i][j].type - 1][inner_game_map[i][j].frameindex] == NULL) {
					inner_game_map[i][j].frameindex = 0;
				}
			}
		}
	}
	//创造更新太阳
	createSunshine();
	updataSunshine();
	//创造更新太阳
	zombie_creat();
	_check();
	zombie_act();  //更新僵尸


}
int main()
{
	initgraph(SCREEN_WIDTH, SCREEN_HIGH);
	InitImages();
	BeginBatchDraw();
	main_menu();
	EndBatchDraw();
	return 0;
}


//
//int main() {
//	initgraph(SCREEN_WIDTH, SCREEN_HIGH);
//	InitImages();
//	BeginBatchDraw();
//
//	while (true)
//	{
//		Star_game_view();
//		clock_t startime = clock();
//		putimage(0, 0, &s[1]);
//		Lz = initlist_z();
//		while (true)
//		{
//			zombie_creat_time(startime);
//		}
//		scanf_s("%d", &level);
//	}
//	EndBatchDraw();
//	closegraph();
//	return 0;
//}
















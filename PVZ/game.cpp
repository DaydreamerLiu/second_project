#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<time.h>
#include "tools.h"
#define SCREEN_WIDTH 960
#define SCREEN_HIGH 720
#define GARDEN_WIDTH 1680
#define GARDEN_HIGH 720
typedef struct map{
	int x;
	int y;
	int speed;
}MAP;
struct guanqiamap  //新加
{
	int isused;
};
MAP garden = { 0,0,8 };

//游戏内实体的数据结构
typedef struct bullet
{
	int ID;			//物品ID
	int x;
	int y;			//子弹xy坐标
	int atk;		//子弹伤害
	int speed;		//子弹速度
	int buff;		//子弹特殊效果

	struct bullet* next;
};

typedef struct plants
{
	int ID;			//物品ID
	int HP;			//血量
	int atk;		//攻击力
	int recharge;	//攻击间隔
	int cd;			//购买冷却
	int cost;		//购买花费
	int PT;			//种植后生效时间（比如土豆地雷1500）
	int danmage_point;//破损点
	int frame;  //植物帧数

	struct plants* next;
}Plants;
typedef struct plants* LinkList_p;

typedef struct zombie
{
	int ID;			//物品ID
	int HP;			//血量
	int x;
	int y;			//僵尸坐标
	int atk;		//攻击力
	int isAtk;       //是否攻击
	int speed;
	int cost;		//购买花费(小游戏模式可能需要)
	int danmage_point;//破损点
	int buff;		//僵尸受到的负面影响
	int star_time;   //buff效果的计时器 （用于计时消除buff效果）

	struct zombie* next;
}Zombie;
struct sunshine
{
	int isused;
	int frame;
	int x;
	int y;
	int desty;

};
IMAGE imgbg[6];
IMAGE cards[10];  //卡片功能完成
IMAGE plantlist;
MAP map[5];  //该结构体存的是 某关是几行几列 图片序号
IMAGE sunshine[10][29];
struct sunshine s[10]; //阳光池
int mousestatus = 0;
struct guanqiamap m[5][9];  //该结构体存的是小关卡里某行某列那个是否有植物
Plants plant[8]; //创建一个存植物的结构体数组 //选植物界面选择的植物字符串链表-> Plant链表 -> 如果id相等把它放到这个plant[8]数组里
//用这个结构体里面的id来快捷loadimag cards ， plants ，plants 的 frame （这就是为什么要把id改成字符串） 这样把植物帧数放在植物对应id的文件夹里就可以实现帧数的变化
void mouse_click()
{
	ExMessage msg;
	if (peekmessage(&msg))
	{
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x > 350 && msg.x < 826 && msg.y < 96)
			{
				mousestatus = 1;
				int plantchoose = (msg.x - 350) / 68;  //chooselist的index  打印的时候的%d用cards[plantchoose]
				loadimage()

			}
			if (msg.y > 96 && mousestatus == 2 )
			{
				int x = (msg.x - 235) / 80;
				int y = (msg.y - 80) / 120;
				m[x][y].isused = 1;
			}
		}
		if (msg.message == WM_MOUSEMOVE && mousestatus ==1)
		{
			mousestatus = 2;
		}
		
	}
}
// 载入PNG图并去透明部分
void _putimagePNG(int  picture_x, int picture_y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)
					| (sb * sa / 255 + db * (255 - sa) / 255);
			}
		}
	}
}
// 适用于 y <0 以及x<0的任何情况
void putimagePNG(int x, int y, IMAGE* picture) {

	IMAGE imgTmp, imgTmp2, imgTmp3;
	int winWidth = getwidth();
	int winHeight = getheight();
	if (y < 0) {
		SetWorkingImage(picture);
		getimage(&imgTmp, 0, -y,
			picture->getwidth(), picture->getheight() + y);
		SetWorkingImage();
		y = 0;
		picture = &imgTmp;
	}
	else if (y >= getheight() || x >= getwidth()) {
		return;
	}
	else if (y + picture->getheight() > winHeight) {
		SetWorkingImage(picture);
		getimage(&imgTmp, x, y, picture->getwidth(), winHeight - y);
		SetWorkingImage();
		picture = &imgTmp;
	}

	if (x < 0) {
		SetWorkingImage(picture);
		getimage(&imgTmp2, -x, 0, picture->getwidth() + x, picture->getheight());
		SetWorkingImage();
		x = 0;
		picture = &imgTmp2;
	}

	if (x > winWidth - picture->getwidth()) {
		SetWorkingImage(picture);
		getimage(&imgTmp3, 0, 0, winWidth - x, picture->getheight());
		SetWorkingImage();
		picture = &imgTmp3;
	}


	_putimagePNG(x, y, picture);
}

int getDelay() {
	static unsigned long long lastTime = 0;
	unsigned long long currentTime = GetTickCount();
	if (lastTime == 0) {
		lastTime = currentTime;
		return 0;
	}
	else {
		int ret = currentTime - lastTime;
		lastTime = currentTime;
		return ret;
	}
}
void game_init()
{
	char name[64];
	int plantput[8];
	plantput[0] = 1;
	plantput[1] = 2;
	plantput[2] = 3;
	memset(m, 0, sizeof(m));
	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 29; i++)
		{
			sprintf_s(name, sizeof(name), "res/sunshine/%d.png", i + 1);
			loadimage(&sunshine[j][i], name);
		}
	}
	int ballmax = sizeof(s) / sizeof(s[0]);
	for (int j = 0; j < ballmax; j++)
	{
		s[j].isused = 0;
	}

	loadimage(&imgbg[0], "map/garden.jpg");
	loadimage(&plantlist, "小部分组件/菜单栏/bar5.png");
	for (int i = 0; i <= 2; i++)  //先试两个
	{
		sprintf_s(name, sizeof(name), "res/Cards/card_%d.png", plantput[i]);
		loadimage(&cards[i], name);
	}
	
	
	//loadimage()
	initgraph(SCREEN_WIDTH,SCREEN_HIGH);

	

}
void creatsunshine()
{
	//memset(0, 0, sizeof(s));
	
	int i;
	int ballmax = sizeof(s) / sizeof(s[0]);
	srand(time(NULL));
	static int count = 0;
	count++;
	if (count > 200+(rand()%200))
	{
		for (i = 0; i < ballmax; i++)
		{
			if (s[i].isused == 0)
			{
				s[i].isused = 1; //使用中
				s[i].x = 100 + 102 * ((rand() % 3) + 1); //
				s[i].y = 0;  
				s[i].desty = 400;  //以后补上 目前先考虑打印;
				s[i].frame = 0;

				break;
			}
		}
		count = 0;
	}



	
}
void updatasunshine()
{
	int ballmax = sizeof(s) / sizeof(s[0]);
	int i = 0;
	while (s[i++].isused == 0);

	if (i > ballmax)
	{
		return;
	}
	else
	{
		s[i].frame++;
		if (s[i].frame == 29)
		{
			s[i].frame = 0;
		}
		if (s[i].y >= s[i].desty)
		{
			static int count = 0;
			count++;
			if (count > 200)
			{
				s[i].isused = 0;
			}
		
		}
		else
		{
			s[i].y +=2;
		}
	}
	

	
	
	
}
void curplant()
{
	if (mousestatus == 1)
	{
		putimagePNG()
	}
}
void window_updata()
{
	BeginBatchDraw();
	putimage(0, 0, &imgbg[0]);   //从别的函数处决定imgbg[]中的值 此时先这么写着
	putimage(270,0, &plantlist);
	int n = 2;// 要打印的植物数量 建一个要打印植物的数组 将植物ID存进去
	for (int i = 0; i <= n; i++)
	{
		putimage(350 + i * 68,5, &cards[i]);
	}
	int ballmax = sizeof(s) / sizeof(s[0]);
	for (int i = 0; i < ballmax; i++)
	{
		if (s[i].isused == 1)
		{
			putimagePNG(s[i].x, s[i].y, &sunshine[i][s[i].frame]);
			//putimagePNG(400, 300, &sunshine[0][0]);
		}
	}
	EndBatchDraw();
}
void game_creat_updata()
{
	creatsunshine();
	updatasunshine();
}
int main()
{
	int flag = 0;
	int timer = 0;
	game_init();
	while (1)
	{	
		timer += getDelay();
		if (timer > 20)
		{
			flag = 1;
			timer = 0;
		}
		if (flag)
		{
			flag = 0;
			game_creat_updata();
			window_updata();
		}
		

		
		
	}
}
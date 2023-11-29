#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<time.h>
#include "tools.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define SCREEN_WIDTH 900
#define SCREEN_HIGH 600
#define GARDEN_WIDTH 1400
#define GARDEN_HIGH 600
#define CARD_WIDTH 53.3
#define CARD_HIGH 75
typedef struct map{
	int x;
	int y;
	int speed;
}MAP;
struct guanqiamap  //新加
{
	int used;
	int type;
	int frameindex;
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
	int row;
	int frame;
	struct zombie* next;
}Zombie;
struct sunshine
{
	int isused;
	int frame;
	int x;
	int y;
	int desty;
	int timer = 0;

};
int sun = 50;  //会变 现在不会
Plants plantshuzu[100];
void luru()
{
	plantshuzu[1].cost = 100;
}
Zombie* zp;



struct bullet *bullets;    //子弹
IMAGE imgBullet;
IMAGE imgBulletBlast[4];
int curZhiWu;
int curX, curY;
IMAGE imgbg[6];
IMAGE cards[10];  //卡片功能完成
IMAGE plantlist;
IMAGE *plants[100][30];
IMAGE imgzombies[100][30];
MAP map[5];  //该结构体存的是 某关是几行几列 图片序号
IMAGE sunshine[29];
struct sunshine s[10]; //阳光池
struct guanqiamap m[5][9];  //该结构体存的是小关卡里某行某列那个是否有植物
int listplant[8]; //创建一个存选择植物id（按顺序）的数组
int zombie_num[];
ExMessage msg;
int plantchoose;
void collectSunshine(ExMessage* msg) {
	int count = sizeof(s) / sizeof(s[0]);
	int w = sunshine[0].getwidth();
	int h = sunshine[0].getheight();
	for (int i = 0; i < count; i++) {
		if (s[i].isused) {
			int x = s[i].x;
			int y = s[i].y;
			if (msg->x > x && msg->x < x + w && msg->y > y && msg->y < y + h) {
				s[i].isused = 0;
				sun += 25;
				mciSendString("play res/sunshine.mp3", 0, 0, 0);
			}
		}
	}
}
void userClick() {
	ExMessage msg;
	static int status = 0;
	if (peekmessage(&msg)) {
		if (msg.message == WM_LBUTTONDOWN) {
			if (msg.x > 86 && msg.x < 86 + 55*8 && msg.y < 90) {
				int index = (msg.x - 86) / 55;
				//printf("%d\n", index); 搞定
				status = 1;
				curZhiWu = listplant[index]; // 传来的存着选择植物的id的数组  curchiwu 存的是listplant[0到7]对应植物的id  从0开始 index -> curzhiwu -> plantshuzu[curzhiwu]
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
				if ( sun >= plantshuzu[curZhiWu].cost) {    // plantshuzu是存所有植物的结构体数组
					sun -= plantshuzu[curZhiWu].cost;
					int col = (msg.x - 128) / 81;
					int row = (msg.y - 90) / 95;
					//printf("[%d,%d]\n", row, col); 搞定
					if (m[row][col].type == 0) {
						m[row][col].type = curZhiWu;
						m[row][col].frameindex = 0;
					}
				}
			}
			
			status = 0;
			curZhiWu = 0;
		}
	}
}
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
	for (int i = 0; i < 29; i++)
	{
		sprintf_s(name, sizeof(name), "res/sunshine/%d.png", i + 1);
		loadimage(&sunshine[i], name);
	}

	int ballmax = sizeof(s) / sizeof(s[0]);
	for (int j = 0; j < ballmax; j++)
	{
		s[j].isused = 0;
	}

	loadimage(&imgbg[0], "map/garden.jpg", GARDEN_WIDTH, GARDEN_HIGH);
	loadimage(&plantlist, "res/bar4.png");
	for (int i = 0; i <= 2; i++)  //先试两个
	{
		sprintf_s(name, sizeof(name), "res/Cards/card_%d.png", plantput[i]);
		loadimage(&cards[i], name, CARD_WIDTH, CARD_HIGH);
	}

	loadimage(&imgBullet, "res/bullets/bullet_normal.png");
	bullets = new bullet;   //创建子弹头指针
	bullets->next = NULL;
	loadimage(&imgBulletBlast[3], "res/bullets/bullet_blast.png");
	for (int i = 0; i < 3; i++) {
		float k = (i + 1) * 0.2;
		loadimage(&imgBulletBlast[i], "res/bullets/bullet_blast.png",
			imgBulletBlast[3].getwidth() * k,
			imgBulletBlast[3].getheight() * k, true);
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
		for (i = 0; i < ballMax && s[i].isused; i++);
		if (i >= ballMax) return;

		s[i].isused = 1;
		s[i].frame = 0;
		s[i].x = 125 + rand() % (905 - 260);
		s[i].y = 60;
		s[i].desty = 180 + (rand() % 4) * 90 + 20;
		s[i].timer = 0;
	}
}
void updataSunshine()
{
	int ballmax = sizeof(s) / sizeof(s[0]);
	int i = 0;
	for (i; i < ballmax; i++)
	{
		if (s[i].isused == 1)
		{
			s[i].frame++;
			if (s[i].frame == 29)
			{
				s[i].frame = 0;
			}
			if (s[i].y > s[i].desty)
			{
				s[i].timer++;
				if (s[i].timer > 200)
				{
					s[i].isused = 0;
					
				}
			}
			if (s[i].timer == 0)
			{
				s[i].y += 2;
			}
		}
	}
	

	
	
	
}
void curplant()
{
	if (curZhiWu > 0) {  // 绘制正在移动的植物
		IMAGE* img = plants[curZhiWu][0];   //植物图片   curzhiwu存的是（在plantshuzu结构体数组里）植物的id
		putimagePNG(curX - img->getwidth() * 0.5, curY - img->getheight() * 0.5, img);
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			if (m[i][j].type > 0) {
				int x = 128 + j * 81 + 30;    //int col = (msg.x - 128) / 81;  未知
				int y = 90 + i * 95 + 70; 	//int row = (msg.y - 90) / 95;
				
				
				int zhiWuIndex = m[i][j].type;
				int frameIndex = m[i][j].frameindex;
				putimagePNG(x, y, plants[zhiWuIndex][frameIndex]);    //zhiwuindex 此时和 curzhiwu是一个值都是种植植物的id
			}
		}
	}

}
void insertzombie();
void createZombie()
{
	static int zmFre = 500;
	static int count = 0;
	count++;
	if (count > zmFre) {
		insertzombie();
	}


	while (zp->next != NULL)
	{
		zp->row = rand() % 5;
		zp->x = GARDEN_WIDTH;
		zp->y = 90 + (1 + zp->row) * 95;
		zp->speed = 1;
		zp = zp->next;
		//根据僵尸坐标计算格子
		int i = 0, j = 0;
	}
}
void updateZM() {
	Zombie* zb = (Zombie*)malloc(sizeof(Zombie));
	Zombie* z = (Zombie*)malloc(sizeof(Zombie));
	z = zb = zp;
	while (zb != NULL)
	{
		if(zb->isAtk ==0)
		zb->x -= zb->speed;
		
		/*if (zb->HP <= 0)
		{
			z->next = zp->next;
			zombie_num[1]--;  //中括号里填这是第几关（每关僵尸数目不同）
			free(zb);
			zp = zb->next;
		}*/
		zb = zb->next;
	}
	

	static int count = 0;
	count++;
	if (count > 4) {
		count = 0;
		while (z->next != NULL)
		{
			zp->frame = (zp->frame + 1) % 22;
		}
	}
}
void drawZombie() {
	Zombie* zb = (Zombie*)malloc(sizeof(Zombie));
	zb = zp;
	while (zb->next != NULL)
	{
		IMAGE* img = &imgzombies[zb->ID][zb->frame];
		int x = zb->x;
		int y = zb->y;
		putimagePNG(x, y, img);
		if (zb->HP < 50)
		{
			//putimage()
		}
		if (zb->HP <= 0)
		{
			//putimage()
		}
	}

}
void window_updata()
{
	BeginBatchDraw();
	putimage(-125, 0, &imgbg[0]);   //从别的函数处决定imgbg[]中的值 此时先这么写着
	putimage(10,0, &plantlist);
	int n = 2;// 要打印的植物数量 建一个要打印植物的数组 将植物ID存进去
	for (int i = 0; i <= n; i++)
	{
		putimage(86 + i * 55,5, &cards[i]);
	}
	int ballmax = sizeof(s) / sizeof(s[0]);
	for (int i = 0; i < ballmax; i++)
	{
		if (s[i].isused == 1)
		{
			putimagePNG(s[i].x, s[i].y, &sunshine[s[i].frame]);
			//putimagePNG(400, 300, &sunshine[0][0]);
		}
	}
	curplant();
	drawZombie();
	
	char scoreText[8];
	sprintf_s(scoreText, sizeof(scoreText), "%d", sun);
	outtextxy(30, 55, scoreText);   // over
	EndBatchDraw();
}

void game_creat_updata()
{
	createSunshine();
	updataSunshine();
	createZombie();
	updateZM();


}
int main()
{
	int flag = 0;
	int timer = 0;
	game_init();
	
	while (1)
	{	
		userClick();
		//mouse_click;
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
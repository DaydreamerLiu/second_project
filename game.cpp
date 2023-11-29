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
struct guanqiamap  //�¼�
{
	int used;
	int type;
	int frameindex;
};

MAP garden = { 0,0,8 };

//��Ϸ��ʵ������ݽṹ
typedef struct bullet
{
	int ID;			//��ƷID
	int x;
	int y;			//�ӵ�xy����
	int atk;		//�ӵ��˺�
	int speed;		//�ӵ��ٶ�
	int buff;		//�ӵ�����Ч��

	struct bullet* next;
};

typedef struct plants
{
	int ID;			//��ƷID
	int HP;			//Ѫ��
	int atk;		//������
	int recharge;	//�������
	int cd;			//������ȴ
	int cost;		//���򻨷�
	int PT;			//��ֲ����Чʱ�䣨������������1500��
	int danmage_point;//�����

	struct plants* next;
}Plants;
typedef struct plants* LinkList_p;

typedef struct zombie
{
	int ID;			//��ƷID
	int HP;			//Ѫ��
	int x;
	int y;			//��ʬ����
	int atk;		//������
	int isAtk;       //�Ƿ񹥻�
	int speed;
	int cost;		//���򻨷�(С��Ϸģʽ������Ҫ)
	int danmage_point;//�����
	int buff;		//��ʬ�ܵ��ĸ���Ӱ��
	int star_time;   //buffЧ���ļ�ʱ�� �����ڼ�ʱ����buffЧ����
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
int sun = 50;  //��� ���ڲ���
Plants plantshuzu[100];
void luru()
{
	plantshuzu[1].cost = 100;
}
Zombie* zp;



struct bullet *bullets;    //�ӵ�
IMAGE imgBullet;
IMAGE imgBulletBlast[4];
int curZhiWu;
int curX, curY;
IMAGE imgbg[6];
IMAGE cards[10];  //��Ƭ�������
IMAGE plantlist;
IMAGE *plants[100][30];
IMAGE imgzombies[100][30];
MAP map[5];  //�ýṹ������ ĳ���Ǽ��м��� ͼƬ���
IMAGE sunshine[29];
struct sunshine s[10]; //�����
struct guanqiamap m[5][9];  //�ýṹ������С�ؿ���ĳ��ĳ���Ǹ��Ƿ���ֲ��
int listplant[8]; //����һ����ѡ��ֲ��id����˳�򣩵�����
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
				//printf("%d\n", index); �㶨
				status = 1;
				curZhiWu = listplant[index]; // �����Ĵ���ѡ��ֲ���id������  curchiwu �����listplant[0��7]��Ӧֲ���id  ��0��ʼ index -> curzhiwu -> plantshuzu[curzhiwu]
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
			//printf("up\n"); �㶨
			if (msg.x > 128 && msg.x < 850 && msg.y > 90 && msg.y < 570) {
				if ( sun >= plantshuzu[curZhiWu].cost) {    // plantshuzu�Ǵ�����ֲ��Ľṹ������
					sun -= plantshuzu[curZhiWu].cost;
					int col = (msg.x - 128) / 81;
					int row = (msg.y - 90) / 95;
					//printf("[%d,%d]\n", row, col); �㶨
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
void _putimagePNG(int  picture_x, int picture_y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
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
// ������ y <0 �Լ�x<0���κ����
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
	for (int i = 0; i <= 2; i++)  //��������
	{
		sprintf_s(name, sizeof(name), "res/Cards/card_%d.png", plantput[i]);
		loadimage(&cards[i], name, CARD_WIDTH, CARD_HIGH);
	}

	loadimage(&imgBullet, "res/bullets/bullet_normal.png");
	bullets = new bullet;   //�����ӵ�ͷָ��
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
		gettextstyle(&f);                     // ��ȡ��ǰ��������
		f.lfHeight = 30;                      // ��������߶�Ϊ 48
		f.lfWidth = 15;
		strcpy_s(f.lfFaceName, "Segoe UI Black");
		f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
		settextstyle(&f);                     // ����������ʽ
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
	if (curZhiWu > 0) {  // ���������ƶ���ֲ��
		IMAGE* img = plants[curZhiWu][0];   //ֲ��ͼƬ   curzhiwu����ǣ���plantshuzu�ṹ�������ֲ���id
		putimagePNG(curX - img->getwidth() * 0.5, curY - img->getheight() * 0.5, img);
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			if (m[i][j].type > 0) {
				int x = 128 + j * 81 + 30;    //int col = (msg.x - 128) / 81;  δ֪
				int y = 90 + i * 95 + 70; 	//int row = (msg.y - 90) / 95;
				
				
				int zhiWuIndex = m[i][j].type;
				int frameIndex = m[i][j].frameindex;
				putimagePNG(x, y, plants[zhiWuIndex][frameIndex]);    //zhiwuindex ��ʱ�� curzhiwu��һ��ֵ������ֲֲ���id
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
		//���ݽ�ʬ����������
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
			zombie_num[1]--;  //�������������ǵڼ��أ�ÿ�ؽ�ʬ��Ŀ��ͬ��
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
	putimage(-125, 0, &imgbg[0]);   //�ӱ�ĺ���������imgbg[]�е�ֵ ��ʱ����ôд��
	putimage(10,0, &plantlist);
	int n = 2;// Ҫ��ӡ��ֲ������ ��һ��Ҫ��ӡֲ������� ��ֲ��ID���ȥ
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
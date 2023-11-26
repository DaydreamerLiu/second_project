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
struct guanqiamap  //�¼�
{
	int isused;
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
	int frame;  //ֲ��֡��

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
IMAGE cards[10];  //��Ƭ�������
IMAGE plantlist;
MAP map[5];  //�ýṹ������ ĳ���Ǽ��м��� ͼƬ���
IMAGE sunshine[10][29];
struct sunshine s[10]; //�����
int mousestatus = 0;
struct guanqiamap m[5][9];  //�ýṹ������С�ؿ���ĳ��ĳ���Ǹ��Ƿ���ֲ��
Plants plant[8]; //����һ����ֲ��Ľṹ������ //ѡֲ�����ѡ���ֲ���ַ�������-> Plant���� -> ���id��Ȱ����ŵ����plant[8]������
//������ṹ�������id�����loadimag cards �� plants ��plants �� frame �������ΪʲôҪ��id�ĳ��ַ����� ������ֲ��֡������ֲ���Ӧid���ļ�����Ϳ���ʵ��֡���ı仯
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
				int plantchoose = (msg.x - 350) / 68;  //chooselist��index  ��ӡ��ʱ���%d��cards[plantchoose]
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
// ����PNGͼ��ȥ͸������
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
	loadimage(&plantlist, "С�������/�˵���/bar5.png");
	for (int i = 0; i <= 2; i++)  //��������
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
				s[i].isused = 1; //ʹ����
				s[i].x = 100 + 102 * ((rand() % 3) + 1); //
				s[i].y = 0;  
				s[i].desty = 400;  //�Ժ��� Ŀǰ�ȿ��Ǵ�ӡ;
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
	putimage(0, 0, &imgbg[0]);   //�ӱ�ĺ���������imgbg[]�е�ֵ ��ʱ����ôд��
	putimage(270,0, &plantlist);
	int n = 2;// Ҫ��ӡ��ֲ������ ��һ��Ҫ��ӡֲ������� ��ֲ��ID���ȥ
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
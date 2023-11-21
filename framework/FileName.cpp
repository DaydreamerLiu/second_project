#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<conio.h>
#include<time.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HIGH 720
#define GARDEN_WIDTH 1680
#define GARDEN_HIGH 720

//���������level��¼��ǰ�ؿ� ���ܣ���ӡ��Ӧ�ĵ�ͼ ���ö�Ӧ��ͨ�ؽ�����Ӧ�ԵĽ�ʬ
int level = 0;

//��ͼ�زı�����
IMAGE g[5];
//ֲ���زı�����
IMAGE p[100];
//��ʬ�زı�����
IMAGE z[100];


//���ص�ͼ�����ݽṹ
typedef struct map{
	int x;
	int y;
	int speed;
}MAP;
MAP garden = { 0,0,8 };


typedef struct plants
{
	int HP;
	int x;
	int y;	//ֲ������
	int atc;//������
	int atc_inter;//�������
	int cd;	//������ȴ
	int cost;//���򻨷�



};

//��ʱ�� ��������������int����������ǰһ��Ϊʱ��������λΪ���룬��һ���Ǽ�ʱ��ID��
int Timer(int duration, int id) {
	static int starTime[100];
	int endTime = clock();
	if (endTime - starTime[id] > duration)
	{
		starTime[id] = endTime;
		return 1;
	}
	return 0;
}

//***************  view  **************/

//ͼƬ�ļ�Ԥ����
void InitImages() {
	loadimage(&g[0], _T("./imgs/garden.jpg"), GARDEN_WIDTH, GARDEN_HIGH);
	loadimage(&g[1], _T("./imgs/garden2.jpg"), GARDEN_WIDTH, GARDEN_HIGH);
}

/*��¼����
���ܣ��н��������û������������������
�Լ�ȷ����¼ǰ��ע��ҳ���;��*/
void log_on_view() {}

/*ע�����
���ܣ��н����û�������һ���������롢�ڶ����������������
�Լ�ȷ��ע��ͷ��ص�½��;��*/

/*���˵�����
���ݣ�����ؿ�ѡ�����á��˺�ѡ��ͼ�����˳���;��*/
void Menu_view() {}

/*�ؿ�ѡ��
���ݣ������������ؿ���ͼ�Σ��Լ��������˵���ͼ��*/
void Levle_choose(){}


/*���˵������ý���
���ܣ��޸�����������������Ч���������˵�*/
void Seting_view_menu() {
}

/*��Ϸ�����ò˵�
���ܣ�������Ϸ��������Ϸ��Ч���������˵������¿�ʼ��Ϸ��������Ϸ*/
void Seting_view_game() {
}








//����ؿ��Ķ��� ����ͷ������ʬ����� PlantsChoose
void prepara() {
	while (garden.x > -600)
	{
		if (Timer(20, 0))
		{
			cleardevice();
			garden.speed = 10 - pow(garden.x + (GARDEN_WIDTH - SCREEN_WIDTH) / 2, 2) / 11000;
			garden.x -= garden.speed;
			putimage(garden.x, garden.y, &g[0]);
			FlushBatchDraw();
		}
		
	}
}


void begin() {
	while (garden.x < -240)
	{
		if (Timer(20, 0))
		{
			cleardevice();
			garden.speed = 10 - pow(garden.x + 420 , 2) / 3600;
			garden.x += garden.speed;
			/*printf("%d", garden.speed);*///�ٶȼ����
			putimage(garden.x, garden.y, &g[0]);
			FlushBatchDraw();
		}
	}
}





//*************  service  *************/


void plants_choose() {
	
}


void Star_game() {
	putimage(garden.x, garden.y, &g[0]);
	FlushBatchDraw();
	Sleep(8000);
	prepara();;
	plants_choose();
	begin();
	Sleep(3000);
}



int main() {
	initgraph(SCREEN_WIDTH, SCREEN_HIGH);
	InitImages();
	BeginBatchDraw();

	while (true)
	{
		Star_game();
	}
	EndBatchDraw();
	closegraph();
	return 0;
}
#pragma once
#include<stdio.h>
#include<graphics.h>
#include<easyx.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<time.h>
#include "tools.h"
#include <mmsystem.h>
#include<string>
#include"Begin.h"
#pragma comment(lib,"winmm.lib")
#define _CRT_SECURE_NO_WARNINGS 1
#define SCREEN_WIDTH 900
#define SCREEN_HIGH 600
#define GARDEN_WIDTH 1400
#define GARDEN_HIGH 600
#define CARDS_WIDTH 53.3
#define CARDS_HIGH 75
//���������level��¼��ǰ�ؿ� ���ܣ���ӡ��Ӧ�ĵ�ͼ ���ö�Ӧ��ͨ�ؽ�����Ӧ�ԵĽ�ʬ
int level = 0;
int zombie_num[5] = { 0 };
//gameviewʱ�õ���ȫ�ֱ���
int curZhiWu;
int curX, curY;
int sun = 50;
// ��Ϸ��ֲ��ѡ����
IMAGE plantlist;
//��ͼ�زı�����
IMAGE g[5];
//ֲ���زı�����
IMAGE *p[100][30];
//��ʬ�زı�����
IMAGE *z[100][30];
//�����ز���
IMAGE s[50];
IMAGE c[50];
//�����ز���
IMAGE shine[29];
//�ӵ��ز���
struct bullet* bullets;    //�ӵ�
IMAGE imgBullet;
IMAGE imgBulletBlast[4];



//���ص�ͼ�����ݽṹ
typedef struct map {
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
//��Ϸ��ʵ�����Ϣ
typedef struct plant_in
{
	int ID;			//��ƷID
	int HP;			//Ѫ��
	int Atk;		//������
	int recharge;	//�������
	int cd;			//������ȴ
	int cost;		//���򻨷�
	int PT;			//��ֲ����Чʱ�䣨������������1500��
	int danmage_point;//�����
}Plants_in;
Plants_in plants_in[100];
typedef struct zombie_in
{
	int ID;			//��ƷID
	int HP;			//Ѫ��
	int Atk;		//������
	int speed;		//ԭʼ�ٶ�
	int cost;		//���򻨷�(С��Ϸģʽ������Ҫ)
	int danmage_point;//�����
}Zombie_in;
Zombie_in zombiein[100];

typedef struct bag {
	int* id;//ָ��ģ�⿪���� 
	int* plant_time;//��¼���ֲ������ȥ��ʱ��
	int length;//�����������
	int size;//ʵ������ 
}Bag;
Bag Lb;
Bag initAarry(int n)
{
	Bag ar;
	ar.id = (int*)malloc(sizeof(int) * n);
	ar.plant_time = (int*)malloc(sizeof(int) * n);
	if (ar.id == NULL || ar.plant_time == NULL)
	{
		printf("�ռ����ʧ��\n");
	}
	ar.length = n;
	ar.size = 0;
	return ar;
}
//��˳���a������һ��Ԫ��k 
void add(Bag* a, int k)
{
	if (a->size < a->length)
	{
		a->id[a->size] = k;
		a->plant_time = 0;
		a->size++;
	}
	else {
		printf("�ռ����������ܲ���\n");
	}
}

//��˳���a��ɾ��Ԫ��k 
void del(Bag* a, int i)
{
	for (int j = i + 1; j < a->size; j++)
	{
		a->id[j - 1] = a->id[j];
	}
	a->size--;
}

int find(Bag* a, int k)
{
	for (int i = 0; i < a->size; i++)
	{
		if (a->id[i] == k)
		{
			return 0;
		}
	}
	return 1;
}
/****************     �ڴ�д���������     *****************/


/***********************************************************/



//��Ϸ����ʱ��ʵ����Ϣ
typedef struct cars
{
	int isAtk;      //�Ƿ񹥻�
	int x;
	int y;

}Cars;
Cars car[5];

typedef struct plants
{
	int ID;			//��ƷID
	int hp;			//Ѫ��
	int isAtk;      //�Ƿ񹥻�
	int x;
	int y;
	struct plants* next;
}Plants;
typedef struct plants* LinkList_p;

typedef struct zombie
{
	int ID;			//��ƷID
	int hp;			//Ѫ��
	int speed;		//ԭʼ�ٶ�
	int star_time;   //buffЧ���ļ�ʱ�� �����ڼ�ʱ����buffЧ����
	int buff;		//��ʬ�ܵ��ĸ���Ӱ��
	int isAtk;       //�Ƿ񹥻�
	int x;
	int y;			//��ʬ����
	struct zombie* next;

}Zombie;
typedef struct sunshine
{
	int isused;
	int frame;
	int x;
	int y;
	int desty;
	int timer = 0;

}Sunshine;
struct sunshine balls[10]; //�����
typedef struct zombie* LinkList_z;
LinkList_z Lz;

LinkList_p initlist_p()
{
	LinkList_p Lp = (plants*)malloc(sizeof(plants));
	if (Lp == NULL)
	{
		printf("����ʧ��\n");
	}
	else {
		Lp->next = NULL;
	}
	return Lp;
}
LinkList_z initlist_z()
{
	LinkList_z Lz = (zombie*)malloc(sizeof(zombie));
	if (Lz == NULL)
	{
		printf("����ʧ��\n");
	}
	else {
		Lz->next = NULL;
	}
	return Lz;
}
LinkList_z add(LinkList_z head, int id, int x, int y)
{
	zombie* s = (zombie*)malloc(sizeof(zombie));
	if (s == NULL)
	{
		printf("����ʧ��\n");
	}
	else
	{
		s->ID = id;
		s->x = x;
		s->y = y;
		s->next = head->next;
		head->next = s;
	}
	return head;
}
void print(LinkList_z head)
{
	zombie* p = head->next;
	while (p != NULL)
	{
		printf("ID=%d x=%d y=%d\n", p->ID, p->x, p->y);
		p = p->next;
	}
}

typedef struct pplant_in_map {
	//int id;
	//int number;//���ڱ�ʾ�ǵڼ���ѡ���ֲ�0Ϊ�գ���������nΪ�Ϸ�ѡ�����ĵ�n��ֲ��
	//int flag;//���ڱ�ʾ�Ƿ���Է���ֲ�0Ϊ���Է��ã�1Ϊ����ֲ��Ϲ�ͷ���ֿ��ص����õ�ֲ���Ժ��Ż���Ū��
	int type;
	int x;
	int y;
	int frameindex;
	int hp;
	int isAtk;
}plant_in_map;
plant_in_map inner_game_map[9][5];


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

//ͼƬ�ļ�Ԥ����  ������������ǰ��
//�����Ժ�����Ҫȡ��
void InitImages();

/*��¼����
�����ˣ����
���ܣ��н��������û������������������
�Լ�ȷ����¼ǰ��ע��ҳ���;��*/
void login_view();

/*ע�����
�����ˣ����
���ܣ��н����û�������һ���������롢�ڶ����������������
�Լ�ȷ��ע��ͷ��ص�½��;��*/
void sign_up_view();


/*���˵�����
* �����ˣ�����
���ݣ�����ؿ�ѡ�����á��˺�ѡ��ͼ�����˳���;��*/
void Menu_view();

/*�ؿ�ѡ��
* �����ˣ�С��
���ݣ������������ؿ���ͼ�Σ��Լ��������˵���ͼ��*/
void Levle_choose_view();


/*���˵������ý���
* �����ˣ�����
���ܣ��޸�����������������Ч���������˵�*/
void Seting_view_menu();

/*��Ϸ�����ò˵�
* �����ˣ�����
���ܣ�
1��������Ϸ��������Ϸ��Ч���������˵������¿�ʼ��Ϸ��������Ϸ
2���ڱ���ͣʱ�����
*/
void Seting_view_game();

/*��Ϸ��ʽ��ʼǰ�Ļ���
�����ˣ�����
���ܣ�
1����ͼ�͵���չʾ����
2������plants_choose����
3���������Ƶ���ȷ��λ�ò���ʽ��ʼ��Ϸ
*/
void Star_game_view();

/*��Ϸ�����еĻ����ӡ
�����ˣ������
���ܣ�
1����˳���ӡ���£�
	* ��ͼ����
	* �������
	* ���ݳ�
	* ֲ��
	* ��ʬ
	* �ӵ� �� һ�ɲ������ƶ� ֻ�����ӡ ��
	* ����	��ֻ�����ӡ��
	* ����
2������service��֧����Ϸ���еĺ���
*/
void game_view() {
	/*1����˳���ӡ���£�
		* ��ͼ����
		* �������
		* ���ݳ�
		* ֲ��
		* ��ʬ
		* �ӵ� �� һ�ɲ������ƶ� ֻ�����ӡ ��
		* ����	��ֻ�����ӡ��
		* ����*/
		/*_check();
		zombie_act();
		plants_act();
		bullet_act();*/
}
/*ʧ��ҳ��
�����ˣ�
���ܣ�չʾʧ�ܶ�������Ч
*/
void defeat_view();


//*************  service  *************/

/*��¼�ɹ��ж�
�����ˣ����
���ܣ����˺ŵĵ�¼�û���������Ĵ��ں�ƥ�������ж�
*/
int login_judgment();

/*ע���ж�
�����ˣ����
���ܣ�
1�����˻����Ƿ��ظ����ж�
2�����������������Ƿ���ͬ���ж�
3�����������ַ���
3������չ�����˴�Ӧ����ע����û����Զ�����
*/
int sign_up_judgment();

/* ��ͣ
�����ˣ���������Ա��
���ܣ�
��ͣ������Ϸ��service����
�÷���ֵ����
*/
int suspend();

/*����Ϸѡ�����ʵ��
�����ˣ�С��
���ܣ�
1�������Ӧ��ѡ��Ĺؿ� ����¼
*/
void Level_choose();

/*��Ϸ ֲ��ѡ�����ʵ��
�����ˣ�����
���ܣ�
1��������ӵ�и�������֮��ѡ�������Ϸ��ֲ��
2������������ ���� 0 ����ѡ��ʧ��
3���ɹ��򷵻� 1 ����ѡ��ɹ�
4����û��ѡ����Բ��������ֲ�� �򷵻� 2 ����Ҫ������ʾ
*/
int plants_choose();
void plants_choose_view();



/*ֲ����ֲ
�����ˣ���ѧ
���ܣ�
1����ȡѡ���ֲ������
2���ж�ѡ��������Ƿ������ֲ
3����ֲ�ɹ����Ƕ�Ӧ����Ϊ������ֲ
*/
void plant();



/*��������λ
�����ˣ����L
���ܣ�
( �Խ�ʬΪ�ӽǼ�� ����������ԱȽ�ʬ��������������� )
1���ԱȽ�ʬ�����ֲ�������ж��ж�	������޸� �ý�ʬ�ڵ��ֲ��ڵ� ���Ե� .isAtk ���� �Լ�ֲ��� .hpֵ ���ж�����
2�������������Ľ�ʬ��xy���� �ж��Ƿ�����˷��� ���޸�С�Ƴ��� .isAtk ���ߵ���ʧ��ҳ�� defete_view()
2������������Ϊ���߹���
3���� .buff ����ͬ��Ӧ
5����Ӧ����ʧ�Ľڵ����ɾ��
*/
void _check();


/*��ʬ��Ϊ�Լ���������
�����ˣ����L
���ܣ�

1�����˽�ʬ�ڵ������
	*��� .hp  �ж��Ƿ�����
	*��� .buff�����쳣 �����쳣Ҫ���ж�
	*��� .isAct  �ж��Ƿ�ͣ�²�����
	*�������� ����ǰ�ж�
2���ı���ص�ͼƬ�ļ�

*/
void zombie_act();

/*ֲ����Ϊ�Լ���������
�����ˣ���ѧ
���ܣ�
1���ı���ص�ͼƬ�ļ�
2����ȡ .isAtk �ж��Ƿ���� creat_bullet()
*/
void plants_act();

/*�ӵ����
�����ˣ�С��
���ܣ�
2���ԱȽ�ʬ������ӵ������ж��ܻ�   ���޸ĸý�ʬ�ڵ� .hp ����; ������޸ĸýڵ� .buff �� .star_time ����
*/
void bullet_check();


/*�ӵ���Ϊ�Լ���������
�����ˣ�С��
���ܣ�
1���ı���ص�ͼƬ�ļ�
*/
void bullet_act();

/*�ӵ�����
�����ˣ�С��
���ܣ�
1���½��ӵ��ڵ�
2���ı���ص�ͼƬ�ļ�
*/
void creat_bullet();

/*�������
�����ˣ�����
���ܣ�
1����������
2���������x�������ɲ�����
3��ֲ�ﶨʱ���ɲ���������
4��һ��ʱ������ʧ
5���ռ����г���ֿ�Ķ���
*/
void sunshine();

/*ʤ���ж�
�����ˣ�
���ܣ�
1���ж����һ����ʬ�Ƿ�����
*/
int iswin();

/*С�Ƴ�
�����ˣ�
���ܣ�
1��
*/


/*��ʬ����
�����ˣ�
���ܣ�
1�����պ���Ľ����ڸ���·��������ɽ�ʬ
*/
void zombie_creat();

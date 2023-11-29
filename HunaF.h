//�����150�п�ʼ ����71����ѧ��ƵĵĽṹ�� ȫ�ֱ�����ʬ��ƽṹ��zombiein[100] ÿ�н�ʬ����zombie_num[5]
#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<time.h>
#include<easyx.h>
#include<string>

#define SCREEN_WIDTH 900
#define SCREEN_HIGH 600
#define GARDEN_WIDTH 1400
#define GARDEN_HIGH 600

//���������level��¼��ǰ�ؿ� ���ܣ���ӡ��Ӧ�ĵ�ͼ ���ö�Ӧ��ͨ�ؽ�����Ӧ�ԵĽ�ʬ
int level = 0;
int zombie_num[5] = { 0 };

//��ͼ�زı�����
IMAGE g[5];
//ֲ���زı�����
IMAGE p[100];
//��ʬ�زı�����
IMAGE z[100];
//�����ز���
IMAGE s[50];

//���ص�ͼ�����ݽṹ
typedef struct map {
	int x;
	int y;
	int speed;
}MAP;
MAP garden = { 0,0,8 };

//��Ϸ��ʵ�����Ϣ
typedef struct plants_in
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

/****************     �ڴ�д���������     *****************/



/***********************************************************/



//��Ϸ����ʱ��ʵ����Ϣ
typedef struct pplant_in_map {
	int number;//���ڱ�ʾ�ǵڼ���ѡ���ֲ�0Ϊ�գ���������nΪ�Ϸ�ѡ�����ĵ�n��ֲ��
	int flag;//���ڱ�ʾ�Ƿ���Է���ֲ�0Ϊ���Է��ã�1Ϊ����ֲ��Ϲ�ͷ���ֿ��ص����õ�ֲ���Ժ��Ż���Ū��
	Plants* Info;
}plant_in_map;
plant_in_map* inner_game_map[9][5];


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
	int ID;				//��ƷID
	int hp;				//Ѫ��
	int speed;			//ԭʼ�ٶ�
	int star_time;		 //buffЧ���ļ�ʱ�� �����ڼ�ʱ����buffЧ����
	int buff;			//��ʬ�ܵ��ĸ���Ӱ��
	int isAtk;		   //�Ƿ񹥻�
	int x;
	int y;				//��ʬ����
	int danmage_point;	//�����
	struct zombie* next;

}Zombie;
typedef struct zombie* LinkList_z;

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

///////////////////////////////////////////////////////////////////////////////////////////////////////

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

void _check(LinkList_z Znode)	//����ֲ���ʬ���ӵ���ͷ���(Ϊ�յ�ͷ���)
{
	LinkList_z zp = Znode, zpre = Znode;

	while (zp->next != NULL)
	{
		zp = zp->next;
		//���ݽ�ʬ����������
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

		//�жϽ�ʬ�Ƿ�����,ɾ���ڵ㣬��������
		if (zp->hp <= 0)
		{
			zpre->next = zp->next;
			zombie_num[j]--;
			free(zp);
			zp = zpre->next;
		}

		////����buff����Ч��
		//switch (zp->buff)
		//{
		//case 1:

		//	break;
		//default:

		//	break;
		//}	

		//�Ƿ񴥷���ʬ����
		if (i >= 0)
			if (inner_game_map[i][j] != 0)
				zp->isAtk = 1;
			else zp->isAtk = 0;

		//����С��
		if (zp->x <= 128)
			car[j].isAtk = 1;

		if (zp->x < 88);
		//defete_view();

		zpre = zpre->next;//ǰָ��
	}

	//�ж�ֲ�﹥��
	for (int j = 0; j < 5; j++)
	{
		if (zombie_num[j] > 0)
			for (int i = 0; i < 9; i++)
				inner_game_map[i][j]->Info->isAtk = 1;
		else
			for (int i = 0; i < 9; i++)
				inner_game_map[i][j]->Info->isAtk = 0;
	}

	//���������ж�ֲ���Ƿ�����
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (inner_game_map[i][j]->number = 0)
				if (inner_game_map[i][j]->Info->hp <= 0)
					inner_game_map[i][j]->flag = 0, inner_game_map[i][j]->number = 0;

		}
	}
}

/*��ʬ��Ϊ�Լ���������
�����ˣ����L
���ܣ�
1�����˽�ʬ�ڵ������
	*��� .buff�����쳣 �����쳣Ҫ���ж�
	*��� .isAct  �ж��Ƿ�ͣ�²�����
	*�������� ����ǰ�ж�
2���ı���ص�ͼƬ�ļ�
*/
void zombie_act(LinkList_z Znode)
{
	LinkList_z zp = Znode;
	int atk = 0;
	while (zp->next != NULL)
	{
		putimage(zp->x, zp->y, &z[zp->ID]);
		if (zp->isAtk == 1)//��¼������
		{
			int atk = zombiein[zp->ID].Atk;
			zp = zp->next;
			zp->speed = 0; //����ʱͣ��

			//���ݽ�ʬ����������
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
			//������ֲ���Ѫ
			inner_game_map[i][j]->Info->hp -= atk;
		}
		else zp->speed = zombiein[zp->ID].speed;//������ʱ�˶�
		//��ʬ�˶�

		////�ı�ͼƬ
		//if (zp->hp <= zombiein[zp->ID].danmage_point);


	}
}

int main()
{
	initgraph(SCREEN_WIDTH, SCREEN_HIGH, EX_SHOWCONSOLE);
	setbkcolor(RGB(230, 211, 222));
	cleardevice();
	getchar();
	return 0;
}
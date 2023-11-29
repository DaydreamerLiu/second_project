//代码从150行开始 新增71行舸学设计的的结构体 全局变量僵尸设计结构体zombiein[100] 每行僵尸数量zombie_num[5]
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

//用这个变量level记录当前关卡 功能：打印对应的地图 调用对应的通关奖励和应对的僵尸
int level = 0;
int zombie_num[5] = { 0 };

//地图素材变量组
IMAGE g[5];
//植物素材变量组
IMAGE p[100];
//僵尸素材变量组
IMAGE z[100];
//窗口素材组
IMAGE s[50];

//加载地图的数据结构
typedef struct map {
	int x;
	int y;
	int speed;
}MAP;
MAP garden = { 0,0,8 };

//游戏内实体的信息
typedef struct plants_in
{
	int ID;			//物品ID
	int HP;			//血量
	int Atk;		//攻击力
	int recharge;	//攻击间隔
	int cd;			//购买冷却
	int cost;		//购买花费
	int PT;			//种植后生效时间（比如土豆地雷1500）
	int danmage_point;//破损点
}Plants_in;

typedef struct zombie_in
{
	int ID;			//物品ID
	int HP;			//血量
	int Atk;		//攻击力
	int speed;		//原始速度
	int cost;		//购买花费(小游戏模式可能需要)
	int danmage_point;//破损点
}Zombie_in;

Zombie_in zombiein[100];

/****************     在此写入数据设计     *****************/



/***********************************************************/



//游戏进行时的实体信息
typedef struct pplant_in_map {
	int number;//用于表示是第几个选择的植物，0为空，其他数字n为上方选择栏的第n个植物
	int flag;//用于表示是否可以放置植物，0为可以放置，1为已有植物（南瓜头那种可重叠放置的植物以后优化再弄）
	Plants* Info;
}plant_in_map;
plant_in_map* inner_game_map[9][5];


typedef struct cars
{
	int isAtk;      //是否攻击
	int x;
	int y;

}Cars;
Cars car[5];
typedef struct plants
{
	int ID;			//物品ID
	int hp;			//血量
	int isAtk;      //是否攻击
	int x;
	int y;
	struct plants* next;
}Plants;
typedef struct plants* LinkList_p;
typedef struct zombie
{
	int ID;				//物品ID
	int hp;				//血量
	int speed;			//原始速度
	int star_time;		 //buff效果的计时器 （用于计时消除buff效果）
	int buff;			//僵尸受到的负面影响
	int isAtk;		   //是否攻击
	int x;
	int y;				//僵尸坐标
	int danmage_point;	//破损点
	struct zombie* next;

}Zombie;
typedef struct zombie* LinkList_z;

LinkList_p initlist_p()
{
	LinkList_p Lp = (plants*)malloc(sizeof(plants));
	if (Lp == NULL)
	{
		printf("分配失败\n");
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
		printf("分配失败\n");
	}
	else {
		Lz->next = NULL;
	}
	return Lz;
}

//计时器 （接受输入两个int类型整数，前一个为时间间隔，单位为毫秒，后一个是计时器ID）
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
			if (inner_game_map[i][j] != 0)
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
				inner_game_map[i][j]->Info->isAtk = 1;
		else
			for (int i = 0; i < 9; i++)
				inner_game_map[i][j]->Info->isAtk = 0;
	}

	//遍历数组判断植物是否死亡
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
		putimage(zp->x, zp->y, &z[zp->ID]);
		if (zp->isAtk == 1)//记录攻击力
		{
			int atk = zombiein[zp->ID].Atk;
			zp = zp->next;
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
			inner_game_map[i][j]->Info->hp -= atk;
		}
		else zp->speed = zombiein[zp->ID].speed;//不攻击时运动
		//僵尸运动

		////改变图片
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
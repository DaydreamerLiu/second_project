# 项目架构
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

//用这个变量level记录当前关卡 功能：打印对应的地图 调用对应的通关奖励和应对的僵尸
int level = 0;

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

	struct zombie* next;
}Zombie;
typedef struct zombie* LinkList_z;

int InitList_plants(LinkList_p* L)
{
	*L = (LinkList_p)malloc(sizeof(plants)); /* 产生头结点,并使L指向此头结点 */
	if (!(*L)) /* 存储分配失败 */
		return 0;
	(*L)->next = NULL; /* 指针域为空 */

	return 1;
}

int InitList_zombie(LinkList_z* L)
{
	*L = (LinkList_z)malloc(sizeof(plants)); /* 产生头结点,并使L指向此头结点 */
	if (!(*L)) /* 存储分配失败 */
		return 0;
	(*L)->next = NULL; /* 指针域为空 */

	return 1;
}
//尾插法增加新实体



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








//***************  view  **************/

//图片文件预加载  放在其他代码前方
//按各自函数需要取用
void InitImages() {}

/*登录界面
负责人：晚风
功能：有接受输入用户名和密码的两个输入
以及确定登录前往注册页面的途径*/
void login_view() {}

/*注册界面
负责人：晚风
功能：有接受用户名、第一次密码输入、第二次密码输入的输入
以及确定注册和返回登陆的途径*/
void sign_up_view() {}


/*主菜单界面
* 负责人：永乐
内容：进入关卡选择、设置、账号选择、图鉴、退出等途径*/
void Menu_view() {}

/*关卡选择
* 负责人：小雷
内容：代表进入各个关卡的图形，以及返回主菜单的图形*/
void Levle_choose_view() {}


/*主菜单的设置界面
* 负责人：星起
功能：修改音乐音量，音乐音效，返回主菜单*/
void Seting_view_menu() {
}

/*游戏内设置菜单
* 负责人：星起
功能：
1、设置游戏音量、游戏音效、返回主菜单、重新开始游戏、继续游戏
2、在被暂停时候调用
*/
void Seting_view_game() {
}

/*游戏正式开始前的画面
负责人：粒子
功能：
1、地图和敌人展示动画
2、调用plants_choose（）
3、将画面移到正确的位置并正式开始游戏
*/
void Star_game_view() {}

/*游戏经行中的画面打印
负责人：大恐龙
功能：
1、按顺序打印以下：
	*地图背景
	*窗口组件
	* 植物
	* 僵尸
	* 子弹 （ 一律不进行移动 只负责打印 ）
	* 阳光	（只负责打印）
	* 铲子
2、调用service中支持游戏进行的函数
*/
void game_view(){
	/*1、按顺序打印以下：
		* 地图背景
		* 窗口组件
		* 植物	
		* 僵尸
		* 子弹 （ 一律不进行移动 只负责打印 ）
		* 阳光	（只负责打印）
		* 铲子*/
	if (suspend())
	{
		/*_check();
		zombie_act();
		plants_act();
		bullet_act();*/
	}
}


//*************  service  *************/

/*登录成功判断
负责人：晚风
功能：对账号的登录用户名和密码的存在和匹配性作判断
*/
int login_judgment(){}

/*注册判断
负责人：晚风
功能：
1、对账户名是否重复作判断
2、对两次密码输入是否相同作判断
3、限制输入字符数
3、（扩展）当此打开应用中注册的用户名自动填入
*/
int sign_up_judgment() {}

/* 暂停
负责人：（整合人员）
功能：
暂停所有游戏内service函数
用返回值控制
*/
int suspend(){}

/*游游戏选择代码实现
负责人：小雷
功能：
1、进入对应的选择的关卡 并记录
*/
void Level_choose() {}

/*游戏 植物选择代码实现
负责人：粒子
功能：
1、按照在拥有格子数量之内选择带入游戏的植物
2、若超出上限 返回 0 代表选择失败
3、成功则返回 1 代表选择成功
4、若没有选择可以产生阳光的植物 则返回 2 代表要触发提示
*/
int plants_choose() {}


/*植物种植
负责人：舸学
功能：
1、读取选择的植物类型
2、判断选择的区域是否可以种植
3、种植成功后标记对应区域为不可种植
*/
void plant() {}





/*检查各个单位
负责人：幻風
功能：
( 以僵尸为视角检查 含义是逐个对比僵尸和其他链表的数据 )
1、对比僵尸链表和植物链表判断行动	按情况修改 该僵尸节点和植物节点 各自的 .isAtk 数据 以及植物的 .hp值 并判断死亡
2、触发特殊行为或者攻击 
3、按 .buff 作不同反应
5、对应该消失的节点进行删除
*/
int _check() {}


/*僵尸行为以及动画加载
负责人：幻風
功能：

1、检查此僵尸节点的数据
	*检查 .hp  判断是否死亡
	*检查 .buff数据异常 则按照异常要求行动
	*检查 .isAct  判断是否停下并攻击
	*若无以上 则向前行动
2、改变加载的图片文件

*/
void zombie_act() {}

/*植物行为以及动画加载
负责人：舸学
功能：
1、改变加载的图片文件
2、读取 .isAtk 判断是hi否调用 creat_bullet()
*/
void plants_act() {}

/*子弹检查
负责人：小雷
功能：
1、检查当前坐标所在格子的植物类型，若遇到特殊植物（火树）则改变 .buff 和加载的图片
2、对比僵尸链表和子弹链表判断受击   并修改该僵尸节点 .hp 数据; 按情况修改该节点 .buff 和 .star_time 数据
*/
void bullet_check() {}


/*子弹行为以及动画加载
负责人：小雷
功能：
1、改变加载的图片文件
*/
void bullet_act() {}

/*子弹制造
负责人：小雷
功能：
1、新建子弹节点
2、改变加载的图片文件
*/
void creat_bullet() {}

/*阳光加载
负责人：永乐
功能：
1、生成阳光
2、场景随机x坐标生成并下落
3、植物定时生成并动画弹出
4、一定时间后会消失
5、收集会有冲向仓库的动画
*/
void sunshine() {}





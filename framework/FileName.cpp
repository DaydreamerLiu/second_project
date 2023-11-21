#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<conio.h>
#include<time.h>

#define SCREEN_WIDTH 1080
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


//加载地图的数据结构
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
	int y;	//植物坐标
	int atc;//攻击力
	int atc_inter;//攻击间隔
	int cd;	//购买冷却
	int cost;//购买花费



};

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

//图片文件预加载
void InitImages() {
	loadimage(&g[0], _T("./imgs/garden.jpg"), GARDEN_WIDTH, GARDEN_HIGH);
	loadimage(&g[1], _T("./imgs/garden2.jpg"), GARDEN_WIDTH, GARDEN_HIGH);
}

/*登录界面
功能：有接受输入用户名和密码的两个输入
以及确定登录前往注册页面的途径*/
void log_on_view() {}

/*注册界面
功能：有接受用户名、第一次密码输入、第二次密码输入的输入
以及确定注册和返回登陆的途径*/

/*主菜单界面
内容：进入关卡选择、设置、账号选择、图鉴、退出等途径*/
void Menu_view() {}

/*关卡选择
内容：代表进入各个关卡的图形，以及返回主菜单的图形*/
void Levle_choose(){}


/*主菜单的设置界面
功能：修改音乐音量，音乐音效，返回主菜单*/
void Seting_view_menu() {
}

/*游戏内设置菜单
功能：设置游戏音量、游戏音效、返回主菜单、重新开始游戏、继续游戏*/
void Seting_view_game() {
}








//进入关卡的动画 将镜头移至僵尸后调用 PlantsChoose
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
			/*printf("%d", garden.speed);*///速度检查器
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
#include"framework.h"

void InitImages() {
	loadimage(&g[0], _T("./imgs/map/garden.jpg"), GARDEN_WIDTH, GARDEN_HIGH);
	loadimage(&g[1], _T("./imgs/map/garden2.jpg"), GARDEN_WIDTH, GARDEN_HIGH);

}


int plants_choose() {
	Sleep(3000);
	return 0;
}


void Star_game() {
	putimage(garden.x, garden.y, &g[0]);
	FlushBatchDraw();
	Sleep(3000);
	while (garden.x > -(GARDEN_WIDTH - SCREEN_WIDTH))
	{
		if (Timer(20, 0))
		{
			cleardevice();
			garden.speed = 10 - pow(garden.x + (GARDEN_WIDTH - SCREEN_WIDTH) / 2, 2) / (pow((GARDEN_WIDTH - SCREEN_WIDTH) / 2, 2) / 9);
			garden.x -= garden.speed;
			putimage(garden.x, garden.y, &g[0]);
			FlushBatchDraw();
			/*printf("%d %d\n", garden.speed, garden.x);*///检查器
		}
	}
	plants_choose();
	while (garden.x < -230)
	{
		if (Timer(20, 0))
		{
			cleardevice();
			garden.speed = 10 - pow(garden.x + (GARDEN_WIDTH - SCREEN_WIDTH + 265) / 2, 2) / (pow((GARDEN_WIDTH - SCREEN_WIDTH) / 2, 2) / 9);
			garden.x += garden.speed;
			/*printf("%d", garden.speed);*///速度检查器
			putimage(garden.x, garden.y, &g[0]);
			FlushBatchDraw();
		}
	}
}




int main() {
	initgraph(SCREEN_WIDTH, SCREEN_HIGH);
	InitImages();
	BeginBatchDraw();

	while (true)
	{
		Star_game();
		scanf_s("%d", &level);
	}
	EndBatchDraw();
	closegraph();
	return 0;
}

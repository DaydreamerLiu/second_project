#include"state.h"

void gameinit() {
	//��ͼ
	loadimage(&g[0], _T("./imgs/map/garden.jpg"), GARDEN_WIDTH, GARDEN_HIGH);
	//���
	loadimage(&s[0], _T("./imgs/screen/PanelBackground.png"));
	loadimage(&s[1], _T("./imgs/screen/ChooserBackground.png"));
	loadimage(&s[2], _T("./imgs/screen/StartButton.png"));
	//��Ƭ�ļ�
	loadimage(&c[0][0], _T("./cpzb/c0.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[0][1], _T("./cpzb/c0_cd.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[1][0], _T("./cpzb/c1.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[1][1], _T("./cpzb/c1_cd.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[2][0], _T("./cpzb/c2.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[2][1], _T("./cpzb/c2_cd.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[3][0], _T("./cpzb/c3.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[3][1], _T("./cpzb/c3_cd.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[4][0], _T("./cpzb/c4.png"), CARDS_WIDTH, CARDS_HIGH);
	loadimage(&c[4][1], _T("./cpzb/c4_cd.png"), CARDS_WIDTH, CARDS_HIGH);

	//ֲ�ｩʬ��Ϣ

		//ֲ��:
	//���տ�
	plantin[0].ID = 0;
	plantin[0].HP = 300;
	plantin[0].Atk = 0;
	plantin[0].recharge = 19000;
	plantin[0].cd = 6000;
	plantin[0].cost = 50;
	plantin[0].PT = 0;
	plantin[0].danmage_point = 0;
	loadimage(&plantin[0].img, _T("./cpzb/p01.png"));
	//�㶹����
	plantin[1].ID = 1;
	plantin[1].HP = 300;
	plantin[1].Atk = 35;
	plantin[1].recharge = 1400;
	plantin[1].cd = 7000;
	plantin[1].cost = 125;
	plantin[1].PT = 0;
	plantin[1].danmage_point = 0;
	loadimage(&plantin[1].img, _T("./cpzb/p02.png"));
	//��������
	plantin[2].ID = 2;
	plantin[2].HP = 300;
	plantin[2].Atk = 20;
	plantin[2].recharge = 1400;
	plantin[2].cd = 7000;
	plantin[2].cost = 200;
	plantin[2].PT = 0;
	plantin[2].danmage_point = 0;
	loadimage(&plantin[2].img, _T("./cpzb/p03.png"));
	//�δ�  p[3]��p[4]�д���ԭͼƬ������ͼƬ,ʹ��ID��Ϊ����
	plantin[3].ID = 3;
	plantin[3].HP = 5000;
	plantin[3].Atk = 0;
	plantin[3].recharge = 100000;
	plantin[3].cd = 20000;
	plantin[3].PT = 0;
	plantin[3].danmage_point = 2500;
	loadimage(&plantin[3].img, _T("./cpzb/p04.png"));
	//Ӯ ��غ�ֱ��ʤ��
	plantin[4].ID = 5;
	plantin[4].HP = 300;
	plantin[4].Atk = 0;
	plantin[4].recharge = 100;
	plantin[4].cd = 0;
	plantin[4].PT = 0;
	plantin[4].danmage_point = 0;
	loadimage(&plantin[4].img, _T("./cpzb/p5.png"));
	//��ʬ:
	//��ͨ��ʬ z[0]��z[1]�д���ԭͼƬ������ͼƬ,ʹ��ID��Ϊ����
	zombiein[0].ID = 0;
	zombiein[0].HP = 210;
	zombiein[0].Atk = 10;
	zombiein[0].speed = 2;
	zombiein[0].cost = 25;
	zombiein[0].buff = 0;
	zombiein[0].danmage_point = 105;
	loadimage(&zombiein[0].img[0][0], _T("./cpzb/z001.png"));
	loadimage(&zombiein[0].img[0][1], _T("./cpzb/z002.png"));
	loadimage(&zombiein[0].img[1][0], _T("./cpzb/z003.png"));
	loadimage(&zombiein[0].img[1][1], _T("./cpzb/z004.png"));
	loadimage(&zombiein[0].img[2][0], _T("./cpzb/z005.png"));
	loadimage(&zombiein[0].img[2][1], _T("./cpzb/z006.png"));
	loadimage(&zombiein[0].img[3][0], _T("./cpzb/z007.png"));
	loadimage(&zombiein[0].img[3][1], _T("./cpzb/z008.png"));
	//���׽�ʬ ͼƬ��������
	zombiein[1].ID = 2;
	zombiein[1].HP = 420;
	zombiein[1].Atk = 10;
	zombiein[1].speed = 2;
	zombiein[1].cost = 50;
	zombiein[1].buff = 0;
	zombiein[1].danmage_point = 180;
	loadimage(&zombiein[1].img[0][0], _T("./cpzb/z011.png"));
	loadimage(&zombiein[1].img[0][1], _T("./cpzb/z012.png"));
	loadimage(&zombiein[1].img[1][0], _T("./cpzb/z013.png"));
	loadimage(&zombiein[1].img[1][1], _T("./cpzb/z014.png"));
	loadimage(&zombiein[1].img[2][0], _T("./cpzb/z015.png"));
	loadimage(&zombiein[1].img[2][1], _T("./cpzb/z016.png"));
	loadimage(&zombiein[1].img[3][0], _T("./cpzb/z017.png"));
	loadimage(&zombiein[1].img[3][1], _T("./cpzb/z018.png"));
	//��ʬ������ ee
	zombiein[2].ID = 4;
	zombiein[2].HP = 350;
	zombiein[2].Atk = 15;
	zombiein[2].speed = 3;
	zombiein[2].cost = 100;
	zombiein[2].buff = 999;	//buff999ʱ�����˺�Ϊ10000,��check��ʹ��
	zombiein[2].danmage_point = 125;
	loadimage(&zombiein[2].img[0][0], _T("./cpzb/z031.png"));
	loadimage(&zombiein[2].img[0][1], _T("./cpzb/z032.png"));
	loadimage(&zombiein[2].img[1][0], _T("./cpzb/z033.png"));
	loadimage(&zombiein[2].img[1][1], _T("./cpzb/z034.png"));
	loadimage(&zombiein[2].img[2][0], _T("./cpzb/z035.png"));
	loadimage(&zombiein[2].img[2][1], _T("./cpzb/z036.png"));
	loadimage(&zombiein[2].img[3][0], _T("./cpzb/z037.png"));
	loadimage(&zombiein[2].img[3][1], _T("./cpzb/z038.png"));

	loadimage(&zombiein[2].img[4][0], _T("./cpzb/z0021.png"));
	loadimage(&zombiein[2].img[4][1], _T("./cpzb/z0022.png"));
	loadimage(&zombiein[2].img[5][0], _T("./cpzb/z0023.png"));
	loadimage(&zombiein[2].img[5][1], _T("./cpzb/z0024.png"));

	//����8
	zombiein[3].ID = 6;
	zombiein[3].HP = 370;
	zombiein[3].Atk = 15;
	zombiein[3].speed = 2;
	zombiein[3].cost = 50;
	zombiein[3].buff = 0;//HP<�����ʱ,buff��Ϊ10,speed��Ϊ4,atk��Ϊ30
	zombiein[3].danmage_point = 120;
	loadimage(&zombiein[3].img[0][0], _T("./cpzb/z041.png"));
	loadimage(&zombiein[3].img[0][1], _T("./cpzb/z041.png"));
	loadimage(&zombiein[3].img[1][0], _T("./cpzb/z043.png"));
	loadimage(&zombiein[3].img[1][1], _T("./cpzb/z043.png"));
	loadimage(&zombiein[3].img[2][0], _T("./cpzb/z042.png"));
	loadimage(&zombiein[3].img[2][1], _T("./cpzb/z042.png"));
	loadimage(&zombiein[3].img[3][0], _T("./cpzb/z044.png"));
	loadimage(&zombiein[3].img[3][1], _T("./cpzb/z044.png"));

}

void game_view() {
	BeginBatchDraw();
	while (true)
	{
		putimage(garden.x, garden.y, &g[0]);
		putimage(0, 0, &s[1]);
		setbkmode(TRANSPARENT);
		settextstyle(25, 0, "΢���ź�");
		outtextxy(28, 58, _T("50"));
		for (int i = 0; i < Lb.size; i++)
		{
			putimage(82 + CARDS_WIDTH * i, 5, &c[Lb.id[i]][0]);
		}
	}
}

//��ʼǰ�Ķ�����Я����ֲ���ѡ��
void Star_game_view() {
	BeginBatchDraw();
	putimage(garden.x, garden.y, &g[0]);
	FlushBatchDraw();
	Sleep(3000);//����ԭ����Ϸ�ȴ�����
	while (garden.x > -(GARDEN_WIDTH - SCREEN_WIDTH))//���ӽ��ƶ������ұ�ǰ�����ƶ�
	{
		if (Timer(20, 0))
		{
			cleardevice();
			garden.speed = 10 - pow(garden.x + (GARDEN_WIDTH - SCREEN_WIDTH) / 2, 2) / (pow((GARDEN_WIDTH - SCREEN_WIDTH) / 2, 2) / 9);//ͨ���������ʵ�ִ��������ٵ�����ƽ���ĵ�ͼ�ƶ�
			garden.x -= garden.speed;
			putimage(garden.x, garden.y, &g[0]);
			FlushBatchDraw();
			/*printf("%d %d\n", garden.speed, garden.x);*///�����
		}
	}
	plants_choose_view();
	while (garden.x < -125)
	{
		if (Timer(20, 0))
		{
			cleardevice();
			garden.speed = 7 - pow(garden.x + (GARDEN_WIDTH - SCREEN_WIDTH + 125) / 2, 2) / (pow((GARDEN_WIDTH - SCREEN_WIDTH) / 2, 2) / 9);//ͬ�� Ϊ��ʵ�ֱ����˶�
			garden.x += garden.speed;
			/*printf("%d", garden.speed);*///�ٶȼ����
			putimage(garden.x, garden.y, &g[0]);
			putimage(0, 0, &s[1]);
			setbkmode(TRANSPARENT);
			settextstyle(25, 0, "΢���ź�");
			outtextxy(28, 58, _T("50"));
			for (int i = 0; i < Lb.size; i++)
			{
				putimage(82 + CARDS_WIDTH * i, 5, &c[Lb.id[i]][0]);
			}
			FlushBatchDraw();
		}
	}
	printf("\n");
	EndBatchDraw();
}
void plants_choose_view() {

	Lb = initAarry(8);//��ʼ������ֲ������Ա�
	while (1)
	{
		ExMessage m = getmessage(EX_MOUSE);
		//�ײ�ͼƬ�Ĵ�ӡ
		putimage(garden.x, garden.y, &g[0]);//��ͼ
		putimage(0, 87, &s[0]);
		putimage(0, 0, &s[1]);
		setbkmode(TRANSPARENT);
		settextstyle(25, 0, "΢���ź�");
		outtextxy(28, 58, _T("50"));
		if (m.x > 150 && m.x < 304 && m.y>548 && m.y < 585)
		{
			putimage(155, 548, &s[2]);//��ʼ��Ϸ��ť�Ķ�Ч��������ƶ�����ťλ��ʱ��ť���⣩
		}
		//�ֿ⿨Ƭ�Ĵ�ӡ
		int num = 0;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				
				if (!find(&Lb, num))
				{
					putimage(20 + CARDS_WIDTH * j, 122 + CARDS_HIGH * i, &c[num][1]);
				}
				else
				{
					putimage(20 + CARDS_WIDTH * j, 122 + CARDS_HIGH * i, &c[num][0]);
				}
				num++;
			}
		}
		//�Ѿ�ѡ��Я���Ŀ�Ƭ�Ĵ�ӡ
		for (int i = 0; i < Lb.size; i++)
		{
			putimage(82 + CARDS_WIDTH * i, 5, &c[Lb.id[i]][0]);
		}

		//���������
		int choose_id = 0;
		int id = 0;
		int re = 0;
		if (m.message == WM_LBUTTONDOWN)
		{
			//ѡ��Ƭ�Ĳ���
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					//�жϾ���ĵ��λ��
					if (m.x > 20 + CARDS_WIDTH * j && m.x < 20 + CARDS_WIDTH * (j + 1) && m.y >122 + CARDS_HIGH * i && m.y < 122 + CARDS_HIGH * (i + 1))
					{

						choose_id = id;//��ѡ���ֲ��id����
						printf("%d\n", choose_id);//��̨�����
						//ȷ�ϴ�ֲ��û�б�ѡ�����ӵ����Ա���
						if (find(&Lb, id))
						{
							add(&Lb, choose_id);
						}
						int re = 1;
						break;
					}
					id++;
					if (id > 4)
					{
						re = 1;
						break;
					}
				}
				if (re)
				{
					break;
				}
			}
			//ɾ����Ƭ�Ĳ���
			for (int i = 0; i < Lb.size; i++)
			{
				if (m.x > 82 + CARDS_WIDTH * i && m.x < 82 + CARDS_WIDTH * (i + 1) && m.y > 5 && m.y < 5 + CARDS_HIGH)
				{
					del(&Lb, i);
				}
			}
			//��������
			if (m.x > 150 && m.x < 304 && m.y>548 && m.y < 585)
			{
				break;
			}
		}

		FlushBatchDraw();
	}
}
void text() {
	for (int i = 0; i < 10; i++)
	{
		line(128 + 81 * i, 90, 128 + 81 * i, 565);
	}
	for (int i = 0; i < 6; i++)
	{
		line(128, 90 + 95 * i, 857, 90 + 95 * i);
	}
	FlushBatchDraw();
}
void zombie_creat_time(clock_t startime) {

	clock_t nowtime = clock();
	long interbal = nowtime - startime;
	static int i = 1;
	if (interbal == 5000 && i == 1)
	{
		printf("%ld %ld\t��%d��\n", startime, nowtime, i);
		zombie_creat();
		i++;
	}
	if (interbal == 10000 && i == 2)
	{
		printf("%ld %ld\t��%d��\n", startime, nowtime, i);
		zombie_creat();
		i++;
	}
	if (interbal == 15000 && i == 3)
	{
		printf("%ld %ld\t��%d��\n", startime, nowtime, i);
		zombie_creat();
		i++;
	}
	if (interbal == 20000 && i == 4)
	{
		printf("%ld %ld\t��%d��\n", startime, nowtime, i);
		zombie_creat();
		i++;
	}
	if (interbal == 25000 && i == 5)
	{
		printf("%ld %ld\t��%d��\n", startime, nowtime, i);
		zombie_creat();
		i++;
	}
}

void zombie_creat() {
	srand((unsigned int)time(NULL));

	static int id = 1;
	int ret = rand() % 5 + 1;
	int x = 0, y = 0;
	switch (ret)
	{
	case 1:
		x = 900;
		y = 90;
		break;
	case 2:
		x = 900;
		y = 185;
		break;
	case 3:
		x = 900;
		y = 280;
		break;
	case 4:
		x = 900;
		y = 375;
		break;
	case 5:
		x = 900;
		y = 460;
		break;
	default:
		break;
	}
	Lz = add(Lz, id, x, y);
	print(Lz);
	printf("�ڵ�%d·\n\n", ret);
	id++;
}

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
		switch ((zp->y - 90) / 95) //!! !! ! ! ! !!�Ż�����������
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
			/*if (inner_game_map[i][j]->flag == 0)*/
			if (inner_game_map[i][j]->number = 0)		////��������������������ʲô��˼ ��ֵ���жϣ�
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
		if (zp->isAtk == 1)//��¼������
		{
			double atk = zombiein[zp->ID].Atk;
			if (zp->buff==1)
			{
				atk *= 0.75;
			}
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
		zp->x -= zp->speed;
		////�ı�ͼƬ
		//if (zp->hp <= zombiein[zp->ID].danmage_point);


	}
}

void initplant() {
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			inner_game_map[i][j]->number = 0;
			inner_game_map[i][j]->flag = 0;
			inner_game_map[i][j]->Info->x = 128 + 81 * i;
			inner_game_map[i][j]->Info->y = 90 + 95 * j;
		}
	}
}

void plant() {

	ExMessage msg;
	static int SetHp_Judge = 1;//Ϊ�˺���������ʹ���µ�ֲ��ĳ�ʼhpֻ����һ�Σ�����˾�̬�ֲ�����

	static int pick = -1;//�������Ҹо��������pick��gameviewѭ����ʱ����������⣬���pick������ҪŪ��ȫ�ֱ���������


	if (peekmessage(&msg, EX_MOUSE))//����������
	{

		if (WM_LBUTTONDOWN)//�����յ����������ʱ����ѭ��
		{

			//ʶ���Ƿ���ֲ����
			/*1.�ж�λ��
			* 2.��ֲ���cd�Ƿ����
			*/
			clock_t click_time = clock();
			for (int i = 0; i < 10; i++)
			{
				if (msg.y > 0 && msg.y < CARDS_HIGH)         //λ�ã�������������������
				{
					if (msg.x > 86 + 55.5 * i + (55.5 - CARDS_WIDTH) && msg.x < 86 + 55.5 * (i + 1) - (55.5 - CARDS_WIDTH))
					{
						if (click_time - Lb.plant_time[i] > plantin[Lb.id[i]].cd)
						{
							pick = i;//pickΪѡ������ѡ���ֲ������
						}

					}
				}

			}
			//�ж����ѡ��Ĳ�Ƥ��λ��
			for (int i = 0; i < 9; i++)
			{
				if (pick==-1)
				{
					break;
				}
				else
				{
					if (msg.x > 128 + 81 * i && msg.x < 128 + 81 * (i + 1))
					{
						for (int j = 0; j < 5; j++)
						{
							if (msg.y > 90 + 95 * i && msg.y < 90 + 95 * (i + 1))
							{
								if (inner_game_map[i][j]->flag == 0)
								{
									inner_game_map[i][j]->flag = 1;
									inner_game_map[i][j]->number = pick; /*˳����ֲ��λ��*/
									inner_game_map[i][j]->id = Lb.id[pick];
									//1.���ú��ֲ�����cd״̬
									//��ʱ��֪����ôд������
									Lb.plant_time[pick] = clock();

									//�������ֲ��ֲ����Ϣ
									inner_game_map[i][j]->Info->ID = Lb.id[pick];

									if (SetHp_Judge == 1)
									{
										//���������ôд��������ô����IDȥ�Ҷ�Ӧ��ֲ���hp������
										inner_game_map[i][j]->Info->hp = plantin[i].HP;//˳����n���Ķ�Ӧֲ�����hpֵ




										SetHp_Judge == 0;//ʹ���µ�ֲ��ĳ�ʼhpֻ����һ�Σ��˴���ֱ��static hp����ֲ�����������ڴ˵���ֲʱ�����⣬����Ŀǰѡ����ô������
									}
									//ѡ���ֲ��pick״̬ȡ��
									pick = -1;
								}

								else if (inner_game_map[i][j]->flag != 0)
								{
									pick = -1;

								}
							}
						}

					}
				}
				
			}
		}


	}

	//����Ƥ�����д��ڿյ�״̬����Ϣ��Ϊ0  
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (inner_game_map[i][j]->flag == 0)
			{
				inner_game_map[i][j]->number = 0;
				inner_game_map[i][j]->Info->ID = -1;
				inner_game_map[i][j]->Info->hp = 0;
				SetHp_Judge = 1;
			}
		}
	}


}






void inituser()
{
	memset(user.data, 0, sizeof(Userdata) * 99);
	user.n = 0;
}

//���Ƶ�¼ע���ײ˵�
void mainmenu_draw()
{
	cleardevice();
	setbkmode(TRANSPARENT);
	//���ñ���ͼƬ Menu/��¼����
	IMAGE img;
	loadimage(&img, "���˵�.png");
	putimagePNG(0, 0, &img);


	int x = 270;		//����������ʼX����
	int y = 170;		//����������ʼY����
	int rx = 120;		//��������X����
	int ry = 90;		//��������Y����

	setfillcolor(RGB(126, 147, 158));
	solidrectangle(0, 170, 0 + 120, 170 + 50);	//��ͨģʽ��ť����

	solidrectangle(0, 240, 0 + 120, 240 + 50);	//ͼ����ť

	solidrectangle(0, 310, 0 + 120, 310 + 50);	//���ð�ť

	solidrectangle(0, 380, 0 + 120, 380 + 50);	//����������ť

	solidrectangle(0, 100, 0 + 120, 100 + 50);	//������¼��ť

	solidrectangle(0, 450, 0 + 120, 450 + 50);	//�����˳���ť


	char text1[] = "��ͨģʽ";
	char text2[] = "ͼ��";
	char text3[] = "����";
	char text4[] = "��������";
	char text5[] = "��¼";
	char text6[] = "�˳�";

	settextcolor(BLACK);
	settextstyle(30, 0, "΢���ź�");

	//��ӡ��ͨģʽ����
	outtextxy(0 + (120 - textwidth(text1)) / 2, 170 + (50 - textheight(text1)) / 2, text1);

	//��ӡͼ��ģʽ����
	outtextxy(0 + (120 - textwidth(text2)) / 2, 240 + (50 - textheight(text2)) / 2, text2);

	//��ӡ��������
	outtextxy(0 + (120 - textwidth(text1)) / 2, 310 + (50 - textheight(text1)) / 2, text3);

	//��ӡ������������
	outtextxy(0 + (120 - textwidth(text1)) / 2, 380 + (50 - textheight(text1)) / 2, text4);

	//��ӡ��¼����
	outtextxy(0 + (120 - textwidth(text5)) / 2, 100 + (50 - textheight(text5)) / 2, text5);

	outtextxy(0 + (120 - textwidth(text6)) / 2, 450 + (50 - textheight(text6)) / 2, text6);

	FlushBatchDraw();
}

//��¼ע���ײ˵�
void main_menu()
{
	cleardevice();
	mainmenu_draw();
	while (true)
	{
		ExMessage msg;
		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				//�����¼ע�����
				if (msg.x >= 0 && msg.x <= 0 + 120 && msg.y >= 100 && msg.y <= 100 + 50)
				{
					printf("��¼\n");
					initfileGet();		//��ԭ���ļ����û������ݸ��ƹ���
					Register();			//��¼ע��Ľ���
					break;

				}
				else if (msg.x >= 0 && msg.x <= 0 + 120 && msg.y >= 450 && msg.y <= 450 + 50)
				{
					printf("�˳�\n");
					initfileAdd();						//����ע����û���Ϣ����
					//�˳�����
					exit(0);
					mainmenu_draw();			//���ص���Ϸ��ʼ����
					break;
				}
				else if (msg.x >= 0 && msg.x <= 0 + 120 && msg.y >= 170 && msg.y <= 170 + 50)
				{
					printf("��ͨģʽ\n");
					Levle_choose_view();
					break;
				}
				else if (msg.x >= 0 && msg.x <= 0 + 120 && msg.y >= 310 && msg.y <= 310 + 50)
				{
					printf("����\n");
					break;
				}
				else if (msg.x >= 0 && msg.x <= 0 + 120 && msg.y >= 240 && msg.y <= 240 + 50)
				{
					printf("ͼ��ģʽ\n");
					break;
				}
				else if (msg.x >= 0 && msg.x <= 0 + 120 && msg.y >= 380 && msg.y <= 380 + 50)
				{
					printf("��������\n");
				}
			default:
				break;
			}
		}

	}
}

void RegisterDraw()
{
	cleardevice();
	BeginBatchDraw();
	setbkcolor(GREEN);
	cleardevice();
	char text1[] = "�û���";
	char text2[] = "����";
	char text3[] = "��¼";
	char text5[] = "ע��";
	char text6[] = "�˳�";
	char text7[99] = { 0 };
	char text8[99] = { 0 };
	setfillcolor(WHITE);

	fillrectangle(310, 180, 310 + 280, 180 + 40);		//�����û����Ŀ�
	fillrectangle(310, 240, 310 + 280, 240 + 40);		//��������Ŀ�

	fillrectangle(290, 320, 290 + 90, 320 + 50);		//��¼�Ŀ�

	fillrectangle(520, 320, 520 + 90, 320 + 50);		//ע��Ŀ�

	fillrectangle(315, 410, 315 + 250, 410 + 60);		//�˳��Ŀ�

	settextcolor(BLACK);

	//��ӡ �û��� ����
	outtextxy(310 - textwidth(text1), (40 - textheight(text1)) / 2 + 180, text1);

	//��ӡ�������
	outtextxy(310 - textwidth(text2), (40 - textheight(text2)) / 2 + 240, text2);


	if (!signname)	//��signname Ϊ 0 ʱ��ӡ�����û���
	{
		outtextxy(310, 180, name);
	}
	if (!signpassword && sign3)	////��signpassword Ϊ 0 ʱ��ӡ��������
	{
		outtextxy(310, 240, "******");
	}

	//��ӡ��¼����
	outtextxy(290 + (90 - textwidth(text3)) / 2, (50 - textheight(text3)) / 2 + 320, text3);

	//��ӡע������
	outtextxy(520 + (90 - textwidth(text5)) / 2, (50 - textheight(text5)) / 2 + 320, text5);

	//��ӡ�˳�����
	outtextxy(315 + (250 - textwidth(text6)) / 2, (60 - textheight(text5)) / 2 + 410, text6);

	EndBatchDraw();
}
//��¼�˵�
void Register()
{
	RegisterDraw();
	ExMessage msg;
	while (true)
	{

		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				//���������û�������
				if (msg.x >= 310 && msg.x <= 310 + 280 && msg.y >= 180 && msg.y <= 180 + 40)
				{
					printf("�û���\n");
					signname = 0;					//��signnameΪ0ʱ���Դ�ӡ�����û���
					InputBox(name, 10, "��������");
					RegisterDraw();					//ʹ���û�����ʾ
					break;
				}
				else if (msg.x >= 310 && msg.x <= 310 + 280 && msg.y >= 240 && msg.y <= 240 + 40)
				{
					printf("����\n");
					signpassword = 0;				//��signpasswordΪ0ʱ���Դ�ӡ��������
					InputBox(password, 10, "����");
					sign3 = 1;
					RegisterDraw();					//ʹ��������ʾ
					break;
				}
				else if (msg.x >= 290 && msg.x <= 290 + 90 && msg.y >= 320 && msg.y <= 320 + 50)
				{

					printf("��¼\n");
					int flag1 = 0;
					int flag2 = 0;
					for (int i = 0; i < user.n; i++)
					{
						//��ע����û���Ϣ���бȶ�
						if (strcmp(name, user.data[i].name) == 0 && name)
						{
							flag1 = 1;
						}
						if (strcmp(password, user.data[i].password) == 0 && password)
						{
							flag2 = 1;
						}
					}
					if (flag1 == 0)
					{
						printf("�û�������\n");
						MessageBox(GetHWnd(), "�û��������ڻ��ߴ���", "����!!!", MB_OK);
						RegisterDraw();
					}
					else if (flag2 == 0)
					{
						printf("�������\n");
						MessageBox(GetHWnd(), "�������", "����!!!", MB_OK);
						RegisterDraw();
					}
					else if (flag1 && flag2)
					{
						printf("��¼�ɹ�\n");
						signname = signpassword = 1;		//���ڽ�����Ϸ��ʼ����ʱ�����¼���˵���ʾ��Ϣ
						MessageBox(GetHWnd(), "��¼�ɹ�", "��ϲ!!!", MB_OK);
						main_menu();							//������Ϸ��ʼ����
					}
					break;
				}
				else if (msg.x >= 520 && msg.x <= 520 + 90 && msg.y >= 320 && msg.y <= 320 + 50)
				{
					printf("ע��\n");
					addUserdata();		//����ע���˺Ų���
					break;
				}
				else if (msg.x >= 260 && msg.x <= 260 + 250 && msg.y >= 410 && msg.y <= 410 + 60)
				{
					printf("�˳�\n");
					signname = signpassword = 1;		//��ֹ�ٴν����¼������ʾ�û�����Ϣ
					sign3 = 0;
					main_menu();							//�����¼ע�����˵�
					break;
				}
			default:
				break;
			}
		}
	}
}

//ע���û���Ϣ
void addUserdata()
{
	addUserdatadraw();//�����û���Ϣ����

	while (true)
	{
		ExMessage msg;
		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				//��������ע���û����Ĳ���
				if (msg.x >= 310 && msg.x <= 310 + 280 && msg.y >= 190 && msg.y <= 190 + 40)
				{
					printf("�����û���\n");
					signnameadd = 0;			//��signnameaddΪ0ʱ��ӡ�����û�������
					signname = 0;				//signnameΪ0ʱ��ֹ�����¼ע��˵���ʾ�û��û�����Ϣ
					InputBox(user.data[user.n].name, 40, "�������û���");
					addUserdatadraw();			//��ӡ��������û�����Ϣ
					break;
				}
				else if (msg.x >= 310 && msg.x <= 310 + 280 && msg.y >= 250 && msg.y <= 250 + 40)
				{
					printf("��������\n");
					sign1 = 1;					//��ӡ����������Ϣ
					signpasswordadd = 0;		//��signpassworaddΪ0ʱ��ӡ������������
					signpassword = 0;			//signpasswordΪ0ʱ��ֹ�����¼ע��˵���ʾ�û�������Ϣ
					InputBox(user.data[user.n].password, 40, "����������");
					if (strlen(user.data[user.n].password))
					{
						passwordlen = 1;
					}
					addUserdatadraw();			////��ӡ�����������
					break;
				}
				else if (msg.x >= 310 && msg.x <= msg.x <= 310 + 280 && msg.y >= 310 && msg.y <= 310 + 40)
				{

					InputBox(passwordagain, 40, "��ȷ������");
					signpasswordaddagain = 0;	//��signpassworaddagainΪ0ʱ��ӡ������������
					sign2 = 1;				//��ӡ����������Ϣ
					if (strlen(passwordagain))
					{
						passwordlen = 1;
					}
					addUserdatadraw();
					break;
				}
				else if (msg.x >= 290 && msg.x <= 290 + 90 && msg.y >= 380 && msg.y <= 380 + 50)
				{
					int flag = 1;
					printf("ע��\n");
					//�ж���������������Ƿ�һ��
					if (strcmp(passwordagain, user.data[user.n].password) == 0)
					{
						signpasswordaddagain = 0;		//��Ϊ0ʱ��ӡ������������������
						addUserdatadraw();				//����
					}
					int ret = judeguser();				//�ж�ע����˺��Ƿ��ظ�
					if (strcmp(passwordagain, user.data[user.n].password) != 0)
					{
						signpasswordaddagain = 1;		//����������������
						signpasswordadd = 1;			//���һ�����������
						MessageBox(GetHWnd(), "�����������벻һ��,����������", "���棡����", MB_OK);
						addUserdatadraw();
					}
					else if (ret)				//�˺Ų��ظ�
					{
						namelen = strlen(user.data[user.n].name);
						passwordlen = strlen(user.data[user.n].password);

						if (namelen > 10 || passwordlen > 20 || namelen == 0 || passwordlen == 0)
						{
							printf("����");
							MessageBox(GetHWnd(), "�˺Ż������벻�淶", "���棡����", MB_OK);
							flag = 0;
						}
						else if (flag && namelen <= 10 && passwordlen <= 20)
						{

							MessageBox(GetHWnd(), "ע��ɹ�", "��ϲ������", MB_OK);
							printf("%s %s\n", user.data[user.n].name, user.data[user.n].password);
							user.n++;


						}
						printf("ע��ɹ�\n");
					}
					else if (ret == 0)			//�˺��ظ�
					{
						printf("�˺��ظ�\n");
						MessageBox(GetHWnd(), "�˺��ظ�", "���棡����", MB_OK);
					}
					break;

				}
				else if (msg.x >= 520 && msg.x <= 520 + 90 && msg.y >= 380 && msg.y <= 380 + 50)
				{
					printf("����\n");
					signnameadd = signpasswordadd = 1;		 //������������
					signname = signpassword = 1;			 //������������
					signpasswordaddagain = 1;				 //������������
					Register();								//���ص���¼���˵�
					sign1 = sign2 = 0;
					namelen = passwordlen = 0;
					break;
				}
			default:
				break;
			}
		}
	}

}
void addUserdatadraw()
{
	char text1[] = "�û���";
	char text2[] = "����";
	char text3[] = "ע��";
	char text5[] = "����";
	char text6[] = "ȷ������";

	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "ע��");

	setbkcolor(GREEN);
	cleardevice();

	fillrectangle(310, 190, 310 + 280, 190 + 40);		//��ӡ�û����Ŀ�

	fillrectangle(310, 250, 310 + 280, 250 + 40);		//��ӡ��������Ŀ�

	fillrectangle(310, 310, 310 + 280, 310 + 40);		//��ӡ�ٴ���������Ŀ�

	fillrectangle(290, 380, 290 + 90, 380 + 50);		//��ӡע�ᰴť�Ŀ�

	fillrectangle(520, 380, 520 + 90, 380 + 50);		//��ӡ���صĿ�

	//��ӡ�û���������
	outtextxy(310 - textwidth(text1), (40 - textheight(text1)) / 2 + 190, text1);

	//��ӡ��������
	outtextxy(310 - textwidth(text2), (40 - textheight(text2)) / 2 + 250, text2);

	//��ӡ�ٴ�������������
	outtextxy(310 - textwidth(text6), (40 - textheight(text6)) / 2 + 310, text6);

	if (!signnameadd)
	{
		//��ӡע��������˻���
		outtextxy(310, 190, user.data[user.n].name);
	}
	if (!signpasswordadd && sign1 && passwordlen != 0)
	{
		//��ӡע�����������
		outtextxy(310, 250, "**********");
	}
	if (!signpasswordaddagain && sign2 && passwordlen != 0)
	{
		//��ӡע���ٴ����������
		outtextxy(310, 310, "**********");
	}

	//��ӡע������
	outtextxy(290 + (90 - textwidth(text3)) / 2, (50 - textheight(text3)) / 2 + 380, text3);

	//��ӡ��������
	outtextxy(520 + (90 - textwidth(text5)) / 2, (50 - textheight(text5)) / 2 + 380, text5);

}

//�����û�����Ϣ
void initfileAdd()
{
	FILE* file;
	fopen_s(&file, "user/data.txt", "w");
	for (int i = 0; i < user.n; ++i)
	{
		fprintf(file, "%s %s\n", user.data[i].name, user.data[i].password);

	}
	fclose(file);
}

//���������Ϣ��ȡ����
void initfileGet()
{
	int i = 0;
	FILE* file;
	fopen_s(&file,"user/data.txt", "r");
	if (file != NULL)
	{
		while ((fscanf_s(file, "%s %s\n", user.data[i].name, user.data[i].password)) != EOF)
		{
			user.n++;
			i++;

		}
	}

}

//�ж�ע���˺��Ƿ�һ��
int judeguser()
{

	for (int i = 0; i < user.n; ++i)
	{
		if (strcmp(user.data[user.n].name, user.data[i].name) == 0)		//�û���
		{
			//�˺��ظ�
			return 0;
		}
	}
	return 1;
}

void Levle_choose_view()
{
	IMAGE mag1;//ѡ�ؽ���
	IMAGE ima1, ima2, ima3, ima4;//��ťͼƬ
	IMAGE tu1, tu2, tu3, tu4, tu5;//�ؿ�ͼ��
	loadimage(&mag1, "imgs/l_choose_img/ѡ�ؽ���.jpg", SCREEN_WIDTH, SCREEN_HIGH);
	loadimage(&ima1, "imgs/l_choose_img/ͼƬ/��ť1.png", 90, 30);//���û��ʱ�� 
	loadimage(&ima2, "imgs/l_choose_img/ͼƬ/��ť2.png", 90, 30);//�����ʱ 
	loadimage(&ima3, "imgs/l_choose_img/ͼƬ/���ؼ�1.png", 200, 40);//���û��ʱ�� 
	loadimage(&ima4, "imgs/l_choose_img/ͼƬ/���ؼ�2.png", 200, 40);//�����ʱ 
	loadimage(&tu1, "imgs/l_choose_img/ͼƬ/�ؿ�1ͼ��.png", 90, 90);
	loadimage(&tu2, "imgs/l_choose_img/ͼƬ/�ؿ�2ͼ��.png", 90, 90);
	loadimage(&tu3, "imgs/l_choose_img/ͼƬ/�ؿ�3ͼ��.png", 90, 90);
	loadimage(&tu4, "imgs/l_choose_img/ͼƬ/�ؿ�4ͼ��.png", 90, 90);
	loadimage(&tu5, "imgs/l_choose_img/ͼƬ/�ؿ�5ͼ��.png", 90, 90);
	int flag = 1;//���õ��ʱ��ͼƬϸ΢�仯 
	BeginBatchDraw();
	while (1)
	{
	
		putimage(0, 0, &mag1);
		putimagePNG(100, 300, flag ? &ima1 : &ima2);
		putimagePNG(250, 300, flag ? &ima1 : &ima2);
		putimagePNG(400, 300, flag ? &ima1 : &ima2);
		putimagePNG(550, 300, flag ? &ima1 : &ima2);
		putimagePNG(700, 300, flag ? &ima1 : &ima2);
		putimagePNG(350, 515, flag ? &ima3 : &ima4);
		putimagePNG(90, 200, &tu1);
		putimagePNG(240, 200, &tu2);
		putimagePNG(390, 200, &tu3);
		putimagePNG(540, 200, &tu4);
		putimagePNG(690, 200, &tu5);
		settextstyle(15, 10, "����");
		setbkmode(TRANSPARENT);
		settextcolor(RGB(30, 30, 30));
		outtextxy(115, 307, "�ؿ�һ");
		outtextxy(265, 307, "�ؿ���");
		outtextxy(415, 307, "�ؿ���");
		outtextxy(565, 307, "�ؿ���");
		outtextxy(715, 307, "�ؿ���");
		outtextxy(400, 527, "�������˵�");
		settextstyle(38, 40, "����");
		setbkmode(TRANSPARENT);
		outtextxy(285, 32, "�ؿ�ѡ��");
		ExMessage m;
		if (peekmessage(&m, EX_MOUSE))//�ؿ�1 
		{
			int ischoose = 0;
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 100 && m.y >= 300 && m.x <= 100 + 90 && m.y <= 300 + 30)
				{
					flag = 0;
					//���ùؿ�1
					level = 1;
					ischoose = 1;
					break;
				}
				if (m.x >= 250 && m.y >= 300 && m.x <= 250 + 90 && m.y <= 300 + 30)
				{
					flag = 0;
					//���ùؿ�2
					level = 2;
					ischoose = 1;
					break;
				}
				if (m.x >= 400 && m.y >= 300 && m.x <= 400 + 90 && m.y <= 300 + 30)
				{
					flag = 0;
					//���ùؿ�3
					level = 3;
					ischoose = 1;
					break;
				}
				if (m.x >= 550 && m.y >= 300 && m.x <= 550 + 90 && m.y <= 300 + 30)
				{
					flag = 0;
					//���ùؿ�4
					level = 4;
					ischoose = 1;
					break;
				}
				if (m.x >= 700 && m.y >= 300 && m.x <= 700 + 90 && m.y <= 300 + 30)
				{
					flag = 0;
					//���ùؿ�5
					level = 5;
					ischoose = 1;
					break;
				}
				if (m.x >= 350 && m.y >= 515 && m.x <= 350 + 200 && m.y <= 515 + 40)
				{
					flag = 0;
					//�������˵�
					main_menu();
					break;
				}
			}
			if (ischoose)
			{
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	Star_game_view();
}


//
//int main()
//{
//	initgraph(SCREEN_WIDTH, SCREEN_HIGH);
//	gameinit();
//	BeginBatchDraw();
//	main_menu();
//	EndBatchDraw();
//	return 0;
//}

int main() {
	const int frameDlay = 1000 / 60;
	int frameStart = 0;
	int frameTime = 0;
	int index = 0;

	initgraph(SCREEN_WIDTH, SCREEN_HIGH);
	gameinit();
	BeginBatchDraw();
	while (true)
	{
		
		frameStart = clock();
		
		cleardevice();

		putimage(garden.x, garden.y, &g[0]);
		drawImg(200, 250, 64, 95, &zombiein[0].img[0][0], index * 64, 0);
		drawImg(200, 150,70, 71, &plantin[4].img, index * 64, 0);

		

		index = (clock() / 200) % frameStart % 9;

		frameTime = clock() - frameStart;
		if (frameDlay - frameTime > 0)
		{
			Sleep(frameDlay - frameTime);
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
	return 0;
}













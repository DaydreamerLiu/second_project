void Levle_choose_view()
{
	IMAGE mag1;//ѡ�ؽ���
	IMAGE ima1,ima2,ima3,ima4;//��ťͼƬ
	loadimage(&mag1, "ͼƬ/ѡ�ؽ���.jpg", SCREEN_WIDTH, SCREEN_HIGH);
	loadimage(&ima1, "ͼƬ/��ť1.png", 90, 30);//���û��ʱ�� 
	loadimage(&ima2, "ͼƬ/��ť2.png", 90, 30);//�����ʱ 
	loadimage(&ima3, "ͼƬ/���ؼ�.png", 200, 40);//���û��ʱ�� 
	loadimage(&ima4, "ͼƬ/���ؼ�.png", 200, 40);//�����ʱ 
	int flag = 1;//���õ��ʱ��ͼƬϸ΢�仯 
	while (1)
	{
		BeginBatchDraw();
		putimage( 0, 0, &mag1);
		putimagePNG(100, 300, flag ? &ima1 : &ima2 );
		putimagePNG(250, 300, flag ? &ima1 : &ima2 );
		putimagePNG(400, 300, flag ? &ima1 : &ima2 );
		putimagePNG(550, 300, flag ? &ima1 : &ima2 );
		putimagePNG(700, 300, flag ? &ima1 : &ima2 );
		putimagePNG(350, 515, flag ? &ima3 : &ima4 );
		ExMessage m;
		if (peekmessage(&m, EX_MOUSE))//�ؿ�1 
		{
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 100 && m.y >= 300 && m.x <= 100 + 90 && m.y <= 300 + 30)
				{
					flag=0;
					//���ùؿ�1
					break;
				}
				
			}
		
		}
		if (peekmessage(&m, EX_MOUSE))//�ؿ�2 
		{
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 250 && m.y >= 300 && m.x <= 250 + 90 && m.y <= 300 + 30)
				{
					flag=0;
					//���ùؿ�2
					break;
				}

			}

		}
		if (peekmessage(&m, EX_MOUSE))//�ؿ�3 
		{
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 400 && m.y >= 300 && m.x <= 400 + 90 && m.y <= 300 + 30)
				{
					flag=0;
					//���ùؿ�3
					break;
				}

			}

		}
		if (peekmessage(&m, EX_MOUSE))//�ؿ�4 
		{
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 550 && m.y >= 300 && m.x <= 550 + 90 && m.y <= 300 + 30)
				{
					flag=0;
					//���ùؿ�4
					break;
				}

			}

		}
		if (peekmessage(&m, EX_MOUSE))//�ؿ�5 
		{
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 700 && m.y >= 300 && m.x <= 700 + 90 && m.y <= 300 + 30)
				{
					flag=0;
					//���ùؿ�5
					break;
				}

			}

		}
		if (peekmessage(&m, EX_MOUSE))//�������˵� 
		{
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 350 && m.y >= 515 && m.x <= 350 + 200 && m.y <= 515 + 40)
				{
					flag=0;
					//�������˵�
					break;
				}

			}

		}
        EndBatchDraw();
	}
}


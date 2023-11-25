void Levle_choose_view()
{
	IMAGE mag1;//选关界面
	IMAGE ima1,ima2,ima3,ima4;//按钮图片
	loadimage(&mag1, "图片/选关界面.jpg", SCREEN_WIDTH, SCREEN_HIGH);
	loadimage(&ima1, "图片/按钮1.png", 90, 30);//鼠标没点时的 
	loadimage(&ima2, "图片/按钮2.png", 90, 30);//鼠标点击时 
	loadimage(&ima3, "图片/返回键.png", 200, 40);//鼠标没点时的 
	loadimage(&ima4, "图片/返回键.png", 200, 40);//鼠标点击时 
	int flag = 1;//设置点击时的图片细微变化 
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
		if (peekmessage(&m, EX_MOUSE))//关卡1 
		{
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 100 && m.y >= 300 && m.x <= 100 + 90 && m.y <= 300 + 30)
				{
					flag=0;
					//调用关卡1
					break;
				}
				
			}
		
		}
		if (peekmessage(&m, EX_MOUSE))//关卡2 
		{
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 250 && m.y >= 300 && m.x <= 250 + 90 && m.y <= 300 + 30)
				{
					flag=0;
					//调用关卡2
					break;
				}

			}

		}
		if (peekmessage(&m, EX_MOUSE))//关卡3 
		{
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 400 && m.y >= 300 && m.x <= 400 + 90 && m.y <= 300 + 30)
				{
					flag=0;
					//调用关卡3
					break;
				}

			}

		}
		if (peekmessage(&m, EX_MOUSE))//关卡4 
		{
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 550 && m.y >= 300 && m.x <= 550 + 90 && m.y <= 300 + 30)
				{
					flag=0;
					//调用关卡4
					break;
				}

			}

		}
		if (peekmessage(&m, EX_MOUSE))//关卡5 
		{
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 700 && m.y >= 300 && m.x <= 700 + 90 && m.y <= 300 + 30)
				{
					flag=0;
					//调用关卡5
					break;
				}

			}

		}
		if (peekmessage(&m, EX_MOUSE))//返回主菜单 
		{
			switch (m.message)
			{
			case WM_LBUTTONDOWN:
				if (m.x >= 350 && m.y >= 515 && m.x <= 350 + 200 && m.y <= 515 + 40)
				{
					flag=0;
					//返回主菜单
					break;
				}

			}

		}
        EndBatchDraw();
	}
}


#pragma once

#include<easyx.h>

void drawImg(int x, int y, IMAGE* src)
{
	// 变量初始化
	DWORD* pwin = GetImageBuffer();			//窗口缓冲区指针
	DWORD* psrc = GetImageBuffer(src);		//图片缓冲区指针
	int win_w = getwidth();				//窗口宽高
	int win_h = getheight();
	int src_w = src->getwidth();				//图片宽高
	int src_h = src->getheight();

	// 计算贴图的实际长宽
	int real_w = (x + src_w > win_w) ? win_w - x : src_w;			// 处理超出右边界
	int real_h = (y + src_h > win_h) ? win_h - y : src_h;			// 处理超出下边界
	if (x < 0) { psrc += -x;			real_w -= -x;	x = 0; }	// 处理超出左边界
	if (y < 0) { psrc += (src_w * -y);	real_h -= -y;	y = 0; }	// 处理超出上边界


	// 修正贴图起始位置
	pwin += (win_w * y + x);

	// 实现透明贴图
	for (int iy = 0; iy < real_h; iy++)
	{
		for (int ix = 0; ix < real_w; ix++)
		{
			byte a = (byte)(psrc[ix] >> 24);//计算透明通道的值[0,256) 0为完全透明 255为完全不透明
			if (a > 100)
			{
				pwin[ix] = psrc[ix];
			}
		}
		//换到下一行
		pwin += win_w;
		psrc += src_w;
	}
}

void drawImg(int x, int y, int dstW, int dstH, IMAGE* src, int srcX, int srcY)
{
	// 变量初始化
	DWORD* pwin = GetImageBuffer();			//窗口缓冲区指针
	DWORD* psrc = GetImageBuffer(src);		//图片缓冲区指针
	int win_w = getwidth();				//窗口宽高
	int win_h = getheight();
	int src_w = src->getwidth();				//图片宽高
	int src_h = src->getheight();


	// 计算贴图的实际长宽
	int real_w = (x + dstW > win_w) ? win_w - x : dstW;			// 处理超出右边界
	int real_h = (y + dstH > win_h) ? win_h - y : dstH;			// 处理超出下边界
	if (x < 0) { psrc += -x;			real_w -= -x;	x = 0; }	// 处理超出左边界
	if (y < 0) { psrc += (dstW * -y);	real_h -= -y;	y = 0; }	// 处理超出上边界

	//printf("realw,h(%d,%d)\n", real_w, real_h);
	// 修正贴图起始位置
	pwin += (win_w * y + x);

	// 实现透明贴图
	for (int iy = 0; iy < real_h; iy++)
	{
		for (int ix = 0; ix < real_w; ix++)
		{
			byte a = (byte)(psrc[ix + srcX + srcY * src_w] >> 24);//计算透明通道的值[0,256) 0为完全透明 255为完全不透明
			if (a > 100)
			{
				pwin[ix] = psrc[ix + srcX + srcY * src_w];
			}
		}
		//换到下一行
		pwin += win_w;
		psrc += src_w;
	}
}
// 载入PNG图并去透明部分
void _putimagePNG(int  picture_x, int picture_y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)
					| (sb * sa / 255 + db * (255 - sa) / 255);
			}
		}
	}
}

// 适用于 y <0 以及x<0的任何情况
void putimagePNG(int x, int y, IMAGE* picture) {

	IMAGE imgTmp, imgTmp2, imgTmp3;
	int winWidth = getwidth();
	int winHeight = getheight();
	if (y < 0) {
		SetWorkingImage(picture);
		getimage(&imgTmp, 0, -y,
			picture->getwidth(), picture->getheight() + y);
		SetWorkingImage();
		y = 0;
		picture = &imgTmp;
	}
	else if (y >= getheight() || x >= getwidth()) {
		return;
	}
	else if (y + picture->getheight() > winHeight) {
		SetWorkingImage(picture);
		getimage(&imgTmp, x, y, picture->getwidth(), winHeight - y);
		SetWorkingImage();
		picture = &imgTmp;
	}

	if (x < 0) {
		SetWorkingImage(picture);
		getimage(&imgTmp2, -x, 0, picture->getwidth() + x, picture->getheight());
		SetWorkingImage();
		x = 0;
		picture = &imgTmp2;
	}

	if (x > winWidth - picture->getwidth()) {
		SetWorkingImage(picture);
		getimage(&imgTmp3, 0, 0, winWidth - x, picture->getheight());
		SetWorkingImage();
		picture = &imgTmp3;
	}


	_putimagePNG(x, y, picture);
}

int getDelay() {
	static unsigned long long lastTime = 0;
	unsigned long long currentTime = GetTickCount();
	if (lastTime == 0) {
		lastTime = currentTime;
		return 0;
	}
	else {
		int ret = currentTime - lastTime;
		lastTime = currentTime;
		return ret;
	}
}
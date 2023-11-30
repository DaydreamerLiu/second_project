#pragma once
#include <stdio.h>
#include <easyx.h>
#include "tools.h"
#define _CRT_SECURE_NO_WARNINGS 1
#define Win_width 900	//背景窗口的宽度
#define Win_height 600	//背景窗口的宽度

char name[20] = { 0 };
char password[20] = { 0 };

int namelen = 0;
int passwordlen = 0;
char passwordagain[20] = { 0 };	//第二次输入密码的存储数组

/*
		规定    0 则为打印输入的内容   1 则为清除输入的内容
*/

int signname = 0;		//登录时的用户名条件
int signpassword = 0;	//登录时的密码条件

int signnameadd = 0;	//注册时输入账户的条件

int signpasswordadd = 0;		//注册时输入密码的条件 
int signpasswordaddagain = 0;	//注册再次输入密码的条件
int sign1 = 0;
int sign2 = 0;
int sign3 = 0;
typedef struct data
{
	char name[10];		//用户名
	char password[20];  //密码
}Userdata;

typedef struct
{
	Userdata data[99];
	int n;
}User;
User user;
void inituser();//初始化用s户数据
void Login();//登录注册首菜单
void Logindraw();//绘制登录注册首菜单
void Register();//登录菜单
void RegisterDraw();//绘制登录菜单
void addUserdata();//注册用户信息
void addUserdatadraw();//绘制用户信息界面
void initfileAdd();//用户数据存储
void initfileGet();//用户数据展开
int judeguser();	//用户数据判断
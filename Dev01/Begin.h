#pragma once
#include <stdio.h>
#include <easyx.h>
#include "tools.h"
#define _CRT_SECURE_NO_WARNINGS 1
#define Win_width 900	//�������ڵĿ��
#define Win_height 600	//�������ڵĿ��

char name[20] = { 0 };
char password[20] = { 0 };

int namelen = 0;
int passwordlen = 0;
char passwordagain[20] = { 0 };	//�ڶ�����������Ĵ洢����

/*
		�涨    0 ��Ϊ��ӡ���������   1 ��Ϊ������������
*/

int signname = 0;		//��¼ʱ���û�������
int signpassword = 0;	//��¼ʱ����������

int signnameadd = 0;	//ע��ʱ�����˻�������

int signpasswordadd = 0;		//ע��ʱ������������� 
int signpasswordaddagain = 0;	//ע���ٴ��������������
int sign1 = 0;
int sign2 = 0;
int sign3 = 0;
typedef struct data
{
	char name[10];		//�û���
	char password[20];  //����
}Userdata;

typedef struct
{
	Userdata data[99];
	int n;
}User;
User user;
void inituser();//��ʼ����s������
void Login();//��¼ע���ײ˵�
void Logindraw();//���Ƶ�¼ע���ײ˵�
void Register();//��¼�˵�
void RegisterDraw();//���Ƶ�¼�˵�
void addUserdata();//ע���û���Ϣ
void addUserdatadraw();//�����û���Ϣ����
void initfileAdd();//�û����ݴ洢
void initfileGet();//�û�����չ��
int judeguser();	//�û������ж�
#include<graphics.h>
#include<conio.h>
#include<Windows.h>
#include<iostream>
#include<math.h>
#include"EasyXPng.h"
#include<queue>
#include<stack>
#define PI 3.1415926
#pragma comment(lib,"Winmm.lib")
using namespace std;

IMAGE
wall, wall_2,
granary, granary_Png, granary2, granary2_Png,
mouse_up, mouse_down, mouse_left, mouse_right,
cover, cover1, cover2, cover3, cover4, cover5, cover6, cover7,
mouse_right_Png, mouse_left_Png, mouse_down_Png, mouse_up_Png;

int imSize = 30;//图片大小
int key = 0;//关卡数
int direction = 2;//默认方向
int bound = 0;//数组边界
int score = 0;//得分
int width = 800;//画面宽度
int deepth = 630;//画面高度
int item = 0;//item为3进入编辑模式,item = 4退出编辑模式；item = 5进入全部路径模式，item = 6进入最短路径模式。
int copyMap[25][25];//保留原值数组（找完需求路径后返还给数组原来的值）

ExMessage m;//定义一个消息变量
//-------------------------------结构体-------------------------------------------------
struct Player//玩家坐标
{
	int i, j;
};

struct Granary//粮仓坐标
{
	int i, j;
};

struct Granary2//粮仓坐标
{
	int i, j;
};

Player player;
Granary granarys;
Granary2 granarys2;

//-------------------------------初始化的迷宫地图---------------------------------------
int map[12][25][25] = {
	//关卡1地图
	{//21*21
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3},
		{3,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,3},
		{3,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,3},
		{3,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,3},
		{3,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,3},
		{3,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,3},
		{3,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,3},
		{3,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,3},
		{3,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,3},
		{3,1,0,1,0,1,0,1,0,1,1,9,1,1,0,1,0,1,0,1,3},
		{3,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,3},
		{3,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,3},
		{3,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,3},
		{3,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,3},
		{3,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3},
		{3,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	},
	//关卡2地图
	{
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,3},
		{3,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,1,3},
		{3,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,3},
		{3,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,3},
		{3,1,1,0,1,1,1,1,0,0,1,0,1,1,1,1,0,1,0,1,3},
		{3,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,1,1,3},
		{3,1,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,0,0,0,3},
		{3,1,0,1,1,1,0,1,0,0,1,0,0,0,0,0,1,1,1,1,3},
		{3,1,0,1,0,1,0,0,0,1,1,1,0,1,1,0,1,0,0,0,3},
		{3,1,0,1,0,1,1,1,1,1,9,1,1,1,1,0,1,1,1,1,3},
		{3,1,0,1,0,1,1,1,0,1,1,0,0,0,1,0,0,0,0,0,3},
		{3,1,0,1,0,0,0,0,0,0,1,0,0,0,1,1,1,0,1,1,3},
		{3,1,0,1,1,1,1,1,1,1,1,1,0,0,1,0,1,0,1,1,3},
		{3,1,0,0,0,0,0,0,1,1,1,1,0,0,1,0,1,0,1,1,3},
		{3,1,1,0,1,1,1,0,1,0,0,0,0,0,1,0,1,0,0,1,3},
		{3,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,0,1,3},
		{3,1,1,0,1,1,1,0,1,0,1,1,1,0,0,0,0,1,0,1,3},
		{3,1,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,1,0,1,3},
		{3,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,4,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	},
	//关卡3地图
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,3,3,3,3,3,1,1,1,1,1,3,3,3,3,3,1,1,1},
		{1,1,3,1,1,1,1,1,3,1,1,1,3,1,1,1,1,1,3,1,1},
		{1,3,1,1,0,0,0,1,1,3,1,3,1,1,0,0,0,1,1,3,1},
		{3,1,1,0,1,1,1,0,1,1,3,1,1,0,1,1,1,0,1,1,3},
		{3,1,0,1,1,0,1,1,0,1,9,1,0,1,1,0,1,1,0,1,3},
		{3,1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,3},
		{3,1,0,1,1,0,0,0,1,0,1,0,1,0,0,0,1,1,0,1,3},
		{3,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,3},
		{1,3,1,1,0,0,0,0,1,0,1,0,1,0,0,0,0,1,1,3,1},
		{1,1,3,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,3,1,1},
		{1,1,1,3,1,0,1,0,1,0,1,0,1,0,1,0,1,3,1,1,1},
		{1,1,1,1,3,1,0,1,1,0,1,0,1,1,0,1,3,1,1,1,1},
		{1,1,1,1,1,3,1,0,1,0,1,0,1,0,1,3,1,1,1,1,1},
		{1,1,1,1,1,1,3,1,1,0,1,0,1,1,3,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,3,1,1,0,1,1,3,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,3,1,1,1,3,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,3,4,3,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
	},
};

//--------------------------------图片加载函数------------------------------------------
void LoadImage()
{
	loadimage(&mouse_up, "老鼠上1.jpg", imSize, imSize);//
	loadimage(&mouse_down, "老鼠下1.jpg", imSize, imSize);
	loadimage(&mouse_left, "老鼠左1.jpg", imSize, imSize);
	loadimage(&mouse_right, "老鼠右1.jpg", imSize, imSize);
	//========================================================================PNG
	loadimage(&mouse_up_Png, "老鼠上1.png", imSize, imSize);
	loadimage(&mouse_down_Png, "老鼠下1.png", imSize, imSize);
	loadimage(&mouse_left_Png, "老鼠左1.png", imSize, imSize);
	loadimage(&mouse_right_Png, "老鼠右1.png", imSize, imSize);

	loadimage(&granary_Png, "粮仓.png", imSize, imSize);//4
	loadimage(&granary2_Png, "粮仓（）.png", imSize, imSize);//5
	//==========================================================================
	loadimage(&granary, "粮仓.jpg", imSize, imSize);//4
	loadimage(&granary2, "粮仓（）.jpg", imSize, imSize);//5
	loadimage(&wall, "墙1.jpg", imSize, imSize);
	loadimage(&wall_2, "墙2.jpg", imSize, imSize);
	loadimage(&cover, "cover.jpg", width, deepth);
	loadimage(&cover1, "cover1.jpg", width, deepth);
	loadimage(&cover2, "cover2.jpg", width, deepth);
	loadimage(&cover3, "cover3.jpg", width, deepth);
	loadimage(&cover4, "cover4.jpg", width, deepth);
	loadimage(&cover5, "cover5.jpg", width, deepth);
	loadimage(&cover6, "cover6.jpg", width, deepth);
	loadimage(&cover7, "cover7.jpg", width, deepth);

}

//--------------------------------绘制整体框架函数--------------------------------------
void Frame()
{
	setlinecolor(GREEN);
	setlinestyle(30);
	rectangle(0, 0, 630, 800);//游戏区
	rectangle(630, 0, 630, 800);//控制区
	rectangle(640, 180, 790, 210);//所有路径
	rectangle(640, 230, 790, 260);//最短路径
	rectangle(640, 290, 790, 320);//修改迷宫
	rectangle(640, 350, 790, 380);//修改完成
	rectangle(640, 410, 790, 580);//操作说明
	rectangle(640, 585, 790, 615);//保存并退出
	rectangle(635, 10, 795, 620);//区
}
//--------------------------------绘制控制区框架----------------------------------------
void Frame2()//编辑线框
{
	bound = 21;
	for (int i = 0;i < bound;i++) {
		for (int j = 0;j < bound;j++) {
			setlinecolor(GREEN);
			rectangle(j * imSize, i * imSize, (j + 1) * imSize, (i + 1) * imSize);
		}
	}
	FlushBatchDraw();
}
//--------------------------------消息提示函数1-----------------------------------------
void Texttip()
{
	int x;
	x = MessageBox(GetForegroundWindow(), "恭喜通过本关！", "Go through the Maze", 1);
	if (key != 3)cout << x;
}
//--------------------------------消息提示函数2-----------------------------------------
void Texttip2()
{
	int x;
	x = MessageBox(GetForegroundWindow(), "恭喜通过所有关卡！", "Go through the Maze", 1);
	cout << x;
}
//--------------------------------消息提示函数3-----------------------------------------
void Texttip3()
{
	//控制区
	TCHAR str[20];
	_stprintf_s(str, _T("控 制 区"));
	settextcolor(BLUE);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(width - 140, deepth - 600, str);
	//关卡数
	TCHAR str1[20];
	_stprintf_s(str1, _T(" 第 %d 关"), key + 1);
	settextcolor(RED);
	settextstyle(30, 0, _T("Times New Roman"));
	outtextxy(width - 140, deepth - 550, str1);
	//步数
	TCHAR str2[20];
	_stprintf_s(str2, _T("生命值：%d"), score);
	settextcolor(RED);
	settextstyle(25, 0, _T("隶书"));
	outtextxy(width - 150, deepth - 500, str2);

	//显示所有路径
	TCHAR str3[20];
	_stprintf_s(str3, _T("所有路径"));
	settextcolor(RED);
	settextstyle(30, 0, _T("隶书"));
	outtextxy(width - 140, deepth - 450, str3);
	//显示最短路径
	TCHAR str4[20];
	_stprintf_s(str4, _T("最短路径"));
	settextcolor(RED);
	settextstyle(30, 0, _T("隶书"));
	outtextxy(width - 140, deepth - 400, str4);
	//修改迷宫
	TCHAR str5[20];
	_stprintf_s(str5, _T("修改迷宫"));
	settextcolor(RED);
	settextstyle(30, 0, _T("隶书"));
	outtextxy(width - 140, deepth - 340, str5);
	//修改完成
	TCHAR str6[20];
	_stprintf_s(str6, _T("修改完成"));
	settextcolor(RED);
	settextstyle(30, 0, _T("隶书"));
	outtextxy(width - 140, deepth - 280, str6);
	//线框
	Frame();
	//游戏规则
	TCHAR str7[20];
	_stprintf_s(str7, _T("游戏规则"));
	settextcolor(BLUE);
	settextstyle(20, 0, _T("宋体"));
	outtextxy(width - 140, deepth - 230, str7);
	//移动
	TCHAR str8[50];
	_stprintf_s(str8, _T("移动：wsad控制移动"));
	settextcolor(YELLOW);
	settextstyle(15, 0, _T("宋体"));
	outtextxy(width - 160, deepth - 200, str8);
	//获取所有路径
	TCHAR str9[50];
	_stprintf_s(str9, _T("获取所有路径：按i键"));
	settextcolor(YELLOW);
	settextstyle(15, 0, _T("宋体"));
	outtextxy(width - 160, deepth - 170, str9);
	//获取最短路径
	TCHAR str10[50];
	_stprintf_s(str10, _T("获取最短路径：按o键"));
	settextcolor(YELLOW);
	settextstyle(15, 0, _T("宋体"));
	outtextxy(width - 160, deepth - 140, str10);
	//修改迷宫
	TCHAR str11[50];
	_stprintf_s(str11, _T("修改迷宫：按c键"));
	settextcolor(YELLOW);
	settextstyle(15, 0, _T("宋体"));
	outtextxy(width - 160, deepth - 110, str11);
	//完成修改
	TCHAR str12[50];
	_stprintf_s(str12, _T("完成修改：单击按钮"));
	settextcolor(YELLOW);
	settextstyle(15, 0, _T("宋体"));
	outtextxy(width - 160, deepth - 80, str12);
	//保存并退出
	TCHAR str13[50];
	_stprintf_s(str13, _T("保存并退出"));
	settextcolor(RED);
	settextstyle(20, 0, _T("隶书"));
	outtextxy(width - 130, deepth - 40, str13);
}
//--------------------------------文本提示函数4-----------------------------------------
void Texttip4()
{
	int x;
	x = MessageBox(GetForegroundWindow(), "小老鼠因为过度劳累加饥饿而死了！", "Go through the Maze", 1);
	cout << x;
}
//--------------------------------消息提示函数5-----------------------------------------
void Texttip5()
{
	int x;
	x = MessageBox(GetForegroundWindow(), "欢迎下次再玩！", "Go through the Maze", 1);
	cout << x;
}
//--------------------------------消息提示函数6-----------------------------------------
void Texttip6()
{
	//关卡提示
	if (key == 0)
	{
		TCHAR str[20];
		_stprintf_s(str, _T("第一关"));
		settextcolor(YELLOW);
		settextstyle(50, 0, _T("隶书"));
		outtextxy(width / 2, deepth / 2, str);
		_getch();
		return;
	}
}

//--------------------------------BFS广搜寻找全部路径-----------------------------------
int MMin = 1000;
void FindAllPath()//找出所有通路----------广度搜素
{
	//1、获取当前地图所有坐标点(copymap)，copymap：地图副本
	for (int i = 0; i < bound; i++)
	{
		for (int j = 0; j < bound; j++)
		{
			copyMap[i][j] = map[key][i][j];//克隆数组
		}
	}

	//2、寻找目标点：老鼠的起始位置(MouseX,MouseY)；奶酪的终止位置(EndX,EndY)
	int MouseX = player.i, MouseY = player.j, EndX = granarys.i, EndY = granarys.j;
	//创建一个访问数组用来做标记，初始化各个点为1
	int v[25][25] = {

		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},

	};
	//原地图复制
	for (int i = 0; i < bound; i++)
	{
		for (int j = 0; j < bound; j++)
		{
			v[i][j] = map[key][i][j];
		}
	}
	//3、定义坐标点结构体并申请一个队列
	struct point
	{
		int x;
		int y;
		int c;//步数
	};
	const int QUEUE_SIZE = 1000;
	point queueArray[QUEUE_SIZE];
	int front = 0, rear = 0;
	//以上三行相当于queue<point> r;   用于申请队列

	//4、定义方向数组:右下左上
	int dx[5] = { 0, 0, 1, 0, -1 };
	int dy[5] = { 0, 1, 0, -1, 0 };

	//5、进行广度搜索
	point begin;
	begin.x = MouseX;
	begin.y = MouseY;
	begin.c = 0;
	queueArray[rear++] = begin;//将起点入队，相当于r.push(begin);
	v[MouseX][MouseY] = 9;//起点已访问（老鼠位置）
	v[EndX][EndY] = 4;//显示终点
	
	while(front!=rear)//相当于while (!r.empty())
	{
		int x = queueArray[front].x, y = queueArray[front].y;//取出队首元素下标，相当于int x = r.front().x, y = r.front().y;
		if (x == EndX && y == EndY)
		{
			break;
		}

		for (int k = 1; k <= 4; k++)//进行四个方向的试探
		{
			int tx=x+dx[k];
			int ty=y+dy[k];
			if (copyMap[tx][ty] == 1 && v[tx][ty] == 1)//这个方向可走并且未被访问
			{
				point temp;
				temp.x = tx;
				temp.y = ty;
				temp.c = queueArray[front].c + 1;//相当于temp.c = r.front().c + 1;
				queueArray[(rear++)%QUEUE_SIZE] = temp;//相当于r.push(temp);
				v[tx][ty] = 7;//访问+1
			}
		}
		front=(front+1)%QUEUE_SIZE;//访问完后要将队首元素出队，相当于r.pop();
	}
	//v[][]数组存放的是全部路径的点，所以接下来将v中的特殊标记赋值给map在到show函数中将数字7绘制出来，在用copymap返回map原貌即可。
	for(int i=0;i<bound;i++){
		for (int j=0;j<bound;j++){
			map[key][i][j] = v[i][j];
		}
	}
	return;
}

//--------------------------------DFS深搜寻找最短路径-----------------------------------
struct point
{
	int i;
	int j;
};

const int STACK_SIZE = 1000;
point sta[STACK_SIZE];
int top = -1;
//以上三行相当于stack<point> sta;

int Endx, Endy;
int Min = 1000;
int v[100][100] = { 0 };//访问数组0未访问7访问
int v1[100][100] = { 0 };

void push(point p) {//相当于C++里stack类的push()函数
	if (top < STACK_SIZE - 1) {
		sta[++top] = p;
	}
}
point pop() {//相当于C++里stack类的pop()函数
	point temp;
	if (top >= 0) {
		temp = sta[top--];
	}
	return temp;
}

void DFS(int x, int y, int step)//x，y表示当前坐标点
{
	if (x == Endx - 1 && y == Endy - 1)//到达终点
	{
		if (step<Min){
			Min=step;
			for(int i=0;i<Min;i++){
				for(int j=0;j<Min;j++){
					map[key][sta[top].i][sta[top].j] = 8;//相当于map[key][sta.top().i][sta.top().j] = 8;
				}
				pop();//相当于sta.pop();
			}
		}
		while (top >= 0)pop();//相当于for (int i = 0; i < sta.size(); i++)sta.pop();
		return;
	}
	else//x，y不是终点:则开始试探
	{
		//顺时针右下左上试探
		if (map[key][x][y + 1] == 1 && v[x][y + 1] == 0)//向右
		{
			v[x][y + 1] = 7;//访问了
			point temp;
			temp.i = x;
			temp.j = y + 1;
			push(temp);//相当于sta.push(temp);
			DFS(x, y + 1, step + 1);
			v[x][y + 1] = 0;//回溯时设置为0未访问
		}
		if (map[key][x + 1][y] == 1 && v[x + 1][y] == 0)//向下
		{
			v[x + 1][y] = 7;//访问了
			point temp;
			temp.i = x + 1;
			temp.j = y;
			push(temp);//相当于sta.push(temp);
			DFS(x + 1, y, step + 1);
			v[x + 1][y] = 0;//回溯时设置为0未访问
		}
		if (map[key][x][y - 1] == 1 && v[x][y - 1] == 0)//向左
		{
			v[x][y - 1] = 7;//访问了
			point temp;
			temp.i = x;
			temp.j = y - 1;
			push(temp);//相当于sta.push(temp);
			DFS(x, y - 1, step + 1);
			v[x][y - 1] = 0;//回溯时设置为0未访问
		}
		if (map[key][x - 1][y] == 1 && v[x - 1][y] == 0)//向上
		{
			v[x - 1][y] = 7;//访问了
			point temp;
			temp.i = x - 1;
			temp.j = y;
			push(temp);//相当于sta.push(temp);
			DFS(x - 1, y, step + 1);
			v[x - 1][y] = 0;//回溯时设置为0未访问
		}
		return;
	}
}

void FindShortPath()
{
	const int m=21, n=21;

	for(int i=0;i<bound;i++){
		for(int j=0;j<bound;j++){
			copyMap[i][j] = map[key][i][j];//克隆数组
		}
	}
	for(int i=0;i<bound;i++){
		for(int j=0;j<bound;j++){
			if (map[key][i][j] == 9)
			{
				player.i = i;
				player.j = j;
				map[key][i][j] = 1;//将初始位置覆盖
			}
			if (map[key][i][j] == 4)
			{//放置粮仓
				granarys.i = i;
				granarys.j = j;
			}
		}
	}

	int Beginx, Beginy;

	if (key == 0)//第一关答案
	{
		Beginx = 12;
		Beginy = 10;
		Endx = 20;
		Endy = 19;
	}

	if (key == 1)//第二关答案
	{
		Beginx = 10;
		Beginy = 10;
		Endx = 20;
		Endy = 19;
	}

	if (key == 2)//第三关答案
	{
		Beginx = 5;
		Beginy = 10;
		Endx = 17;
		Endy = 10;
	}

	v[Beginx][Beginy] = 8;
	v1[Beginx][Beginy] = 8;

	DFS(Beginx, Beginy, 0);


	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << map[key][i][j] << ' ';
		}
		cout << endl;
	}
	return;
}

//-------------------------------游戏初始化函数----------------------------------------
void Start()
{
	initgraph(width, deepth);
	setbkcolor(RGB(122, 122, 122));
	cleardevice();
	BeginBatchDraw();//开始批量绘制
	if (key == 0){
		bound = 21;
		score = 200;
		item = 0;
	}
	else if (key == 1){
		bound = 21;
		score = 300;
		item = 0;
	}
	else if (key == 2){
		bound = 21;
		score = 300;
		item = 0;
	}
	for(int i=0;i<bound;i++){
		for(int j=0;j<bound;j++){
			if (map[key][i][j] == 9)
			{
				player.i = i;
				player.j = j;
				map[key][i][j] = 1;//将初始位置覆盖
			}
			if (map[key][i][j] == 4)
			{//放置粮仓
				granarys.i = i;
				granarys.j = j;
				putimagePng(j * imSize, i * imSize, &granary_Png);
			}
		}
	}
	mciSendString(_T("open 001.mp3 alias bkmusic"), NULL, 0, NULL);//播放音乐
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//循环播放
}

//-------------------------------游戏界面绘制函数--------------------------------------
void Show()
{
	int i, j;
	cleardevice();
	for(i=0;i<bound;i++){
		for(j=0;j<bound;j++){
			if (map[key][i][j] == 0)//绘制墙体1
				putimagePng(j * imSize, i * imSize, &wall);
			if (map[key][i][j] == 3)//绘制墙体2
				putimagePng(j * imSize, i * imSize, &wall_2);
			if (map[key][i][j] == 4)//绘制粮仓
				putimagePng(j * imSize, i * imSize, &granary_Png);
			if (map[key][i][j] == 7)//显示全部路径
			{
				setfillcolor(GREEN);
				fillrectangle(j * imSize, i * imSize, (j + 1) * imSize, (i + 1) * imSize);
			}
			if (map[key][i][j] == 8)//显示最短路径
			{
				setfillcolor(RED);
				fillrectangle(j * imSize, i * imSize, (j + 1) * imSize, (i + 1) * imSize);
			}
			if (map[key][i][j] == 1)
				//通道
				if (map[key][i][j] == 9)
				{
					if (direction == 4){
						putimage(j * imSize, i * imSize, &mouse_down);
					}
					else if (direction == 3){
						putimage(j * imSize, i * imSize, &mouse_right);
					}
					else if (direction == 2){
						putimage(j * imSize, i * imSize, &mouse_up);
					}
					else if (direction == 1){
						putimage(j * imSize, i * imSize, &mouse_left);
					}
				}
			if (player.i == granarys.i && player.j == granarys.j)//到达终点
			{
				Texttip();
				key++;
				closegraph();
				if (key != 3)
					Start();
				else
				{
					Texttip2();
					closegraph();
					return;
				}
			}
			if (item == 3)//绘制编辑网格（绿色的小网格）
			{
				setlinecolor(GREEN);
				rectangle(j * imSize, i * imSize, (j + 1) * imSize, (i + 1) * imSize);
			}
		}
	}
	//绘制玩家图像
	i = player.i;
	j = player.j;
	if (direction == 4){
		putimagePng(j * imSize, i * imSize, &mouse_down_Png);
	}
	else if (direction == 3){
		putimagePng(j * imSize, i * imSize, &mouse_right_Png);
	}
	else if (direction == 2){
		putimagePng(j * imSize, i * imSize, &mouse_up_Png);
	}
	else if (direction == 1){
		putimagePng(j * imSize, i * imSize, &mouse_left_Png);
	}
	Texttip3();
	FlushBatchDraw();
}

//-------------------------------鼠标交互函数------------------------------------------
void Change()
{
	Frame2();//编辑格子
	Show();
	while (true) {
		ExMessage m;//定义一个消息变量
		m = getmessage(EM_MOUSE);//获取鼠标消息
		switch (m.message)
		{
		case WM_MOUSEMOVE:
			// 鼠标移动的时候画红色的小点
			putpixel(m.x, m.y, RED);
			break;

		case WM_LBUTTONDOWN:
		{
			if (m.x <= 790 && m.x >= 640 && m.y <= 210 && m.y >= 180)//显示所有路径
			{
				item = 4;//取消显示所有路径
				for (int i = 0; i < bound; i++)//恢复原来的迷宫样貌
				{
					for (int j = 0; j < bound; j++)
					{
						map[key][i][j] = copyMap[i][j];
					}
				}
			}

			if (m.x <= 790 && m.x >= 640 && m.y <= 260 && m.y >= 230)//显示最短路径
			{
				item = 4;//取消显示最短路径
				for (int i = 0; i < bound; i++)//恢复原来的迷宫样貌
				{
					for (int j = 0; j < bound; j++)
					{
						map[key][i][j] = copyMap[i][j];
					}
				}
			}

			if (m.x <= 790 && m.x >= 640 && m.y <= 380 && m.y >= 350)
			{
				item = 4;//取消编辑，完成修改
				return;
			}
			if (m.x <= 790 && m.x >= 640 && m.y <= 615 && m.y >= 585)//保存并退出
			{
				Texttip5();
				key = 3;
				return;
			}
			//通过鼠标位置计算出点击的小方块在二维数组中的下标
			int clicked_i = int(m.y) / imSize;
			int clicked_j = int(m.x) / imSize;
			//点击放墙
			if (map[key][clicked_i][clicked_j] == 1)
				map[key][clicked_i][clicked_j] = 0;
			Show();
		}
		break;
		case WM_RBUTTONUP:
		{//通过鼠标位置计算出点击的小方块在二维数组中的下标
			int clicked_i = int(m.y) / imSize;
			int clicked_j = int(m.x) / imSize;
			//点击放路
			if (map[key][clicked_i][clicked_j] == 0)
				map[key][clicked_i][clicked_j] = 1;
			Show();
		}
		break;
		case WM_MBUTTONDOWN://中键按下
		{
			int clicked_i = int(m.y) / imSize;
			int clicked_j = int(m.x) / imSize;
			//点击放路
			if (map[key][clicked_i][clicked_j] == 4)
				map[key][clicked_i][clicked_j] = 1;
			Show();
		}
		break;
		case WM_MBUTTONUP://中键弹起
		{
			int clicked_i = int(m.y) / imSize;
			int clicked_j = int(m.x) / imSize;
			//移动终点
			granarys.i = clicked_i;
			granarys.j = clicked_j;
			if (map[key][clicked_i][clicked_j] == 1)
				map[key][clicked_i][clicked_j] = 4;
			Show();
		}
		break;
		}
	}
}

//-------------------------------关卡选择函数-----------------------------------------
void Select2()//选关界面
{
	putimage(0, 0, &cover5);
	setlinecolor(GREEN);
	setlinestyle(30);
	//鼠标操作
	while (true) {
		ExMessage m;//定义一个消息变量
		m = getmessage(EM_MOUSE);//获取鼠标消息
		switch (m.message)
		{
		case WM_MOUSEMOVE:
			// 鼠标移动的时候画红色的小点
			putpixel(m.x, m.y, RED);
			break;

		case WM_LBUTTONDOWN:
		{
			if (m.x <= 220 && m.x >= 135 && m.y <= 230 && m.y >= 140)//1
			{
				key = 0;
				return;
			}
			if (m.x <= 385 && m.x >= 305 && m.y <= 230 && m.y >= 140)//2
			{
				key = 1;
				return;
			}
			if (m.x <= 530 && m.x >= 450 && m.y <= 230 && m.y >= 140)//3
			{
				key = 2;
				return;
			}
		}
		break;
		}
	}
	key = 2;//0,1,2表示关卡数
	_getch();
	return;
}

//-------------------------------登录界面函数-----------------------------------------
void Select()//登录界面
{
	initgraph(width, deepth);
	putimage(0, 0, &cover4);//登录界面
	setlinecolor(GREEN);
	setlinestyle(30);
	while (true) {
		ExMessage m;//定义一个消息变量
		m = getmessage(EM_MOUSE);//获取鼠标消息
		switch (m.message)
		{
		case WM_MOUSEMOVE:
			// 鼠标移动的时候画红色的小点
			putpixel(m.x, m.y, RED);
			break;

		case WM_LBUTTONDOWN:
		{
			if (m.x <= 570 && m.x >= 250 && m.y <= 280 && m.y >= 160)return;//Play区域
			if (m.x <= 570 && m.x >= 250 && m.y <= 400 && m.y >= 280)//Select区域
			{
				Select2();
				return;
			}
			if (m.x <= 570 && m.x >= 250 && m.y <= 530 && m.y >= 420)//Exit区域
			{
				key = 3;
				return;
			}
		}
		break;
		}
	}
}

//-------------------------------播放开头动画函数-------------------------------------
void Animator()//播放动画
{
	putimage(0, 0, &cover7);
	char input;
	input = _getch();
	if (input == 'v')//按v播放动画
	{
		initgraph(width, deepth);
		putimage(0, 0, &cover1);
		Sleep(5000);
		putimage(0, 0, &cover2);
		Sleep(5000);
		putimage(0, 0, &cover3);
		Sleep(5000);
	}
	if (input == ' ')return;//空格跳过动画
}

//-------------------------------非手动更新函数---------------------------------------
void WithOutInput()
{
	if (item == 3)Change();
}

//-------------------------------玩家手动更新函数-------------------------------------
void Input()
{
	if (score <= 0) {
		Texttip4();
		key = 3;
		return;
	}
	char input = _getch();
	if (input == 'a' || input == 's' || input == 'd' || input == 'w' || input == 'c' || input == 'i' || input == 'o')
	{//有效按键
		int goal_i = player.i;
		int goal_j = player.j;
		int goalNext_i = goal_i;
		int goalNext_j = goal_j;

		if (input == 'c') {//按c编辑迷宫
			item = 3;
			Change();
		}
		if (input == 'i') {//按i显示所有路径
			item = 5;
			if (item == 5)
				FindAllPath();
		}
		if (input == 'o') {//按o显示最短路径
			item = 6;
			if (item == 6)FindShortPath();
		}
		if (input == 'a') {
			goal_j = player.j - 1;
			goalNext_j = player.j - 1;//坐标变化
			direction = 1;//向左走
			score -= 1;
		}
		else if (input == 'd') {
			goal_j = player.j + 1;
			goalNext_j = player.j + 1;//坐标变化
			direction = 3;//向右走
			score -= 1;
		}
		else if (input == 'w') {
			goal_i = player.i - 1;
			goalNext_i = player.i - 1;//坐标变化
			direction = 2;//向上走
			score -= 1;
		}
		else if (input == 's') {
			goal_i = player.i + 1;
			goalNext_i = player.i + 1;//坐标变化
			direction = 4;//向下走
			score -= 1;
		}

		if (map[key][goal_i][goal_j] == 1 || map[key][goal_i][goal_j] == 7 || map[key][goal_i][goal_j] == 8
			|| map[key][goalNext_i][goalNext_j] == 1 || map[key][goal_i][goal_j] == 7 || map[key][goal_i][goal_j] == 8)
		{
			player.i = goal_i;
			player.j = goal_j;
		}
		if (map[key][goal_i][goal_j] == 4)
		{
			player.i = goal_i;
			player.j = goal_j;
		}
	}
	else return;//其他情况不予考虑
}

//-------------------------------进度条加载函数---------------------------------------
void Jindutiao()
{
	LoadImage();
	initgraph(width, deepth);
	setbkcolor(RGB(122, 122, 122));
	cleardevice();
	clock_t start, now;
	start = clock();
	float initTime = 0;
	float remainTime = initTime;
	float lineSize = 5;
	while (remainTime <= lineSize) {
		now = clock();
		double duration = (double(now - start) / CLOCKS_PER_SEC);
		remainTime = initTime + duration;
		cleardevice();
		setlinecolor(RGB(255, 0, 0));
		setfillcolor(RGB(255, 0, 0));
		putimage(0, 0, &cover);
		fillrectangle(0, 590, remainTime * width / lineSize, 600);
		putimagePng(remainTime * width / lineSize, 600 - imSize, &mouse_right_Png);
		putimagePng(width - imSize, deepth - 2 * imSize, &granary2_Png);
		Sleep(20);
	}
	FlushBatchDraw();
	Select();//登录界面
	Animator();
}


int main()
{
	Jindutiao();
	Start();
	while (1) {
		Show();
		Input();
		if (key == 3) break;
	}
	return 0;
}
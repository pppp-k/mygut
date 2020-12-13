#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>


int high,width; // 游戏画面大小
int bird_x,bird_y; // 小鸟的坐标
int bar1_y,bar1_xDown,bar1_xTop; // 障碍物1的相关坐标
int score; // 得分，经过障碍物的个数

void gotoxy(int x,int y)//类似于清屏函数
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void HideCursor() //隐藏光标 
{
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO cci;
GetConsoleCursorInfo(hOut, &cci);
cci.bVisible = FALSE;
SetConsoleCursorInfo(hOut, &cci);
}

void startup()  // 初始化
{
	high = 20;
	width = 20;
	bird_x = high/2;
	bird_y = 3;
	bar1_y = width;
	bar1_xDown = high/3;
	bar1_xTop = high/2;
	score = 0;
}

void show()  // 显示画面
{
	gotoxy(0,0);  // 清屏	
	int i,j;
	
	for (i=0;i<high;i++)
	{
		for (j=0;j<width;j++)
		{
			if ((i==bird_x) && (j==bird_y))
				printf("@");  //   小鸟
			else if ((j==bar1_y) && ((i<bar1_xDown)||(i>bar1_xTop)) )
				printf("*");  //   墙壁
			else
				printf(" ");  //   空格
		}
		printf("\n");
	}
	printf("得分：%d\n",score);
}	

void update1()  // 循环 
{
	bird_x ++;
	bar1_y --;
	if (bird_y==bar1_y)
	{
		if ((bird_x>=bar1_xDown)&&(bird_x<=bar1_xTop))
			score++;
		else
		{
			printf("游戏失败\n");
			system("pause");
			exit(0);
		}
	}
	if (bar1_y<=0)  // 再新生成一个障碍物
	{
		bar1_y = width;
		int temp = rand()%int(high*0.8);
		bar1_xDown = temp - high/10;
		bar1_xTop = temp + high/10;
	}

	Sleep(150);
}

void update2()  // 输入 
{	
	char input;
	if(kbhit())  // 判断是否有输入
	{
		input = getch();  // 根据用户的不同输入来移动，不必输入回车
		if (input == 'w')  
		{
			bird_x = bird_x - 2;
		}

	}
}

int main()
{
	startup();  // 数据初始化	
	while (1)  //  循环执行
	{
		show();  // 显示画面
		 HideCursor();
		update1();  
		update2();     
	}
}

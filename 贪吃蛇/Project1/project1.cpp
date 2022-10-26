#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define MAX_SNAKE 100
/*枚举定义*/enum DIR//蛇的方向
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
struct Snake_tlg//蛇的结构体
{
	int num;//节数
	int dir;//方向
	int score;//分数
	int size;//蛇的宽度和高度
	POINT coor[MAX_SNAKE];//位置
}snake;
struct Food_tlg
{
	POINT fd;
	int flag;
}food;
void GameInit()
{
	srand(GetTickCount());//随机数种子；
	snake.num = 3;
	snake.dir = RIGHT;
	snake.score = 0;
	snake.size = 5;
	snake.coor[2].x = 10;
	snake.coor[2].y = 10;
	snake.coor[1].x = 10+snake.size;
	snake.coor[1].y = 10 ;
	snake.coor[0].x = 10 + snake.size + snake.size;
	snake.coor[0].y = 10;
	//食物
	food.fd.x = rand() % WIN_WIDTH;
	food.fd.y = rand() % WIN_HEIGHT;
	food.flag = 1;
	//DWORD color;
}//初始化
void GameDraw()//界面模型绘制
{
	int i;
	setbkcolor(BROWN);//界面颜色设置
	cleardevice();//界面初始化
	//画蛇
	for (i = 0; i < snake.num; i++)
	{
		setfillcolor(RGB(55, 182, 217));//设置蛇的颜色
		setlinecolor(BLACK);//蛇的描边颜色
		solidcircle(snake.coor[i].x, snake.coor[i].y, snake.size);//初始化蛇的位置

	}
	//画食物
	if (food.flag == 1)
	{
		setfillcolor(GREEN);
		solidcircle(food.fd.x, food.fd.y, 5);
	}
	//分数显示；
	char temp[20] = "";
	sprintf(temp, "分数：%d", snake.score); //把格式化的数据写入某个字符串缓冲区。
	setbkmode(TRANSPARENT);
	outtextxy(1,1,temp);

}
void EatFood()
{
	if (snake.coor[0].x <= food.fd.x + 5 && snake.coor[0].x >= food.fd.x - 5 && snake.coor[0].y >= food.fd.y - 5 && snake.coor[0].y <= food.fd.y + 5&&food.flag==1)
	{
		snake.num+=1;
		snake.score += 10;
		food.flag = 0;
	}
	if (food.flag == 0)
	{
		food.fd.x = rand() % WIN_WIDTH;
		food.fd.y = rand() % WIN_HEIGHT;
		food.flag = 1;
	}
}
void SnakeMove()
{
	int i;
	for (i = snake.num-1; i >0; i--)
	{
		snake.coor[i].x = snake.coor[i-1].x;
		snake.coor[i].y = snake.coor[i - 1].y;
	}
	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y -= 5;
		if (snake.coor[0].y <= 0)
		{
			snake.coor[0].y = WIN_HEIGHT;
		}
		break;
	case DOWN:
		snake.coor[0].y += 5;
		if (snake.coor[0].y >= WIN_HEIGHT)
		{
			snake.coor[0].y = 0;
		}
		break;
	case LEFT:
		snake.coor[0].x -= 5;
		if (snake.coor[0].x <= 0)
		{
			snake.coor[0].x = WIN_WIDTH;
		}
		break;
	case RIGHT:
		snake.coor[0].x += 5;
		if (snake.coor[0].x >= WIN_WIDTH)
		{
			snake.coor[0].x = 0;
		}
		break;
	}
}
void KeyBoard()
{
	//使用win32API获取键盘消息
	if (GetAsyncKeyState(VK_UP)&&snake.dir!=DOWN)
	{
		snake.dir = UP;
	}
	if (GetAsyncKeyState(VK_DOWN) && snake.dir != UP)
	{
		snake.dir = DOWN;
	}
	if (GetAsyncKeyState(VK_LEFT) && snake.dir != RIGHT)
	{
		snake.dir = LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT) && snake.dir != LEFT)
	{
		snake.dir = RIGHT;
	}
}
void GameOver()//游戏结束
{
	for (int i = 4; i < snake.num; i++)
	{
		if (snake.coor[0].x <=snake.coor[i].x+5 && snake.coor[0].y <=snake.coor[i].y+5&& snake.coor[0].x >= snake.coor[i].x - 5 && snake.coor[0].y >= snake.coor[i].y - 5)
		{
			outtextxy(200, 200, "GAME OVER!");
			//_getch();
			Sleep(1000);
			exit(0);
		}
	}
}
int main()
{
	initgraph(WIN_WIDTH, WIN_HEIGHT);//初始化图形窗口
	GameInit();
	DWORD t1, t2;
	t1 = t2 = GetTickCount();//返回（retrieve）从操作系统启动到现在所经过（elapsed）的毫秒数，它的返回值是DWORD
	while (1)
	{
		if (t2 - t1 > 50)
		{
			SnakeMove();
			t1 = t2;
		}
		t2 = GetTickCount();
		GameDraw();
		FlushBatchDraw();//双缓冲防止卡顿；这个函数用于执行未完成的绘制任务。
		EatFood();
		KeyBoard();
		GameOver();
	}
	
	closegraph();
	return 0;

}
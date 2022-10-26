#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define MAX_SNAKE 100
/*ö�ٶ���*/enum DIR//�ߵķ���
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
struct Snake_tlg//�ߵĽṹ��
{
	int num;//����
	int dir;//����
	int score;//����
	int size;//�ߵĿ�Ⱥ͸߶�
	POINT coor[MAX_SNAKE];//λ��
}snake;
struct Food_tlg
{
	POINT fd;
	int flag;
}food;
void GameInit()
{
	srand(GetTickCount());//��������ӣ�
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
	//ʳ��
	food.fd.x = rand() % WIN_WIDTH;
	food.fd.y = rand() % WIN_HEIGHT;
	food.flag = 1;
	//DWORD color;
}//��ʼ��
void GameDraw()//����ģ�ͻ���
{
	int i;
	setbkcolor(BROWN);//������ɫ����
	cleardevice();//�����ʼ��
	//����
	for (i = 0; i < snake.num; i++)
	{
		setfillcolor(RGB(55, 182, 217));//�����ߵ���ɫ
		setlinecolor(BLACK);//�ߵ������ɫ
		solidcircle(snake.coor[i].x, snake.coor[i].y, snake.size);//��ʼ���ߵ�λ��

	}
	//��ʳ��
	if (food.flag == 1)
	{
		setfillcolor(GREEN);
		solidcircle(food.fd.x, food.fd.y, 5);
	}
	//������ʾ��
	char temp[20] = "";
	sprintf(temp, "������%d", snake.score); //�Ѹ�ʽ��������д��ĳ���ַ�����������
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
	//ʹ��win32API��ȡ������Ϣ
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
void GameOver()//��Ϸ����
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
	initgraph(WIN_WIDTH, WIN_HEIGHT);//��ʼ��ͼ�δ���
	GameInit();
	DWORD t1, t2;
	t1 = t2 = GetTickCount();//���أ�retrieve���Ӳ���ϵͳ������������������elapsed���ĺ����������ķ���ֵ��DWORD
	while (1)
	{
		if (t2 - t1 > 50)
		{
			SnakeMove();
			t1 = t2;
		}
		t2 = GetTickCount();
		GameDraw();
		FlushBatchDraw();//˫�����ֹ���٣������������ִ��δ��ɵĻ�������
		EatFood();
		KeyBoard();
		GameOver();
	}
	
	closegraph();
	return 0;

}
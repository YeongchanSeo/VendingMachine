#include "mouseClick.h"
#include "Linkedlist.h"
#include "beverage.h"
#include <time.h>

struct time
{
	unsigned int hour;
	unsigned int min;
	unsigned int sec;
};

int timer(struct time *p);

int mouseClick2()
{
	int length = 16;
	int maxnum = 100; /*����� �ִ� ����*/
	int res = 0;
	int sx = 14, sy = 5;
	int x, y;
	int button;
	HANDLE hIn;
	DWORD defaultMode; // ���� ��� ���庯��
	int buttonWidth = 8, buttonHeight = 2;
	int boxlength = 12;
	int boxheight = 3;
	struct time time;
	// �⺻ ��� ����
	hIn = GetStdHandle(STD_INPUT_HANDLE); // �������� �ܼ��� �ڵ��� ����
	GetConsoleMode(hIn, &defaultMode); // �ܼ�â�� ���� ����(text�Է� or mouse�Է�)�� �����ؿ�

	// ���콺 �̺�Ʈ �׽�Ʈ
	hIn = mouseMode();  // �ܼ�â�� ���¸� MOUSE MODE�� ����
	while (1)
	{
		timer(&time);
		gotoxy(84, 1);
		if (time.hour > 12){ time.hour -= 12; printf("����"); }
		else{ printf("����"); }
		printf(" %u:%u:%u\n", time.hour, time.min, time.sec);
		mousePosCheck(hIn, &x, &y, &button); // Moude ��ġ �� ���� �˻�
		gotoxy(x, y);
		if (button == MOUSELEFTCLICK) // ���콺 ������ư click
		{
			for (int res = 1; res <= 10; res++)
			{
				if (x >= sx + 2 && x < sx + 2 + length * 3)
				{
					if (y == sy + 2 * res + 1)
					{
						textMode(hIn, defaultMode);
						return res;
					}
				}
				if (x >= 80 && x < 80 + boxlength)
				{
					if (y >= 32 && y < 32 + boxheight)
					{
						return 13;
					}
					else if (y >= 36 && y < 36 + boxheight)
					{
						return 14;
					}
				}
			}
		}
		if (button == MOUSECENTER) // ���콺 ������ư click
		{
			return 0;
		}
	}

	// �ؽ�Ʈ �����ȯ

	return 0;
}


int timer(struct time *p)
{
	char temp[10];
	char* token;

	_strtime(temp);
	token = strtok(temp, ":");
	p->hour = atoi(token);
	token = strtok(NULL, ":");
	p->min = atoi(token);
	token = strtok(NULL, ":");
	if (p->sec == atoi(token))
	{
		return 1;
	}
	else
	{
		p->sec = atoi(token);
		return 0;
	}
}
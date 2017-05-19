#include "mouseClick.h"
#include "Linkedlist.h"
#include "beverage.h"

int mouseClick(Linkedlist *lp)
{
	int res = 0;
	int x, y;
	int button;
	HANDLE hIn;
	DWORD defaultMode; // ���� ��� ���庯��
	int buttonWidth = 8, buttonHeight = 2;

	// �⺻ ��� ����
	hIn = GetStdHandle(STD_INPUT_HANDLE); // �������� �ܼ��� �ڵ��� ����
	GetConsoleMode(hIn, &defaultMode); // �ܼ�â�� ���� ����(text�Է� or mouse�Է�)�� �����ؿ�

	// ���콺 �̺�Ʈ �׽�Ʈ
	hIn = mouseMode();  // �ܼ�â�� ���¸� MOUSE MODE�� ����

	while (1)
	{
		mousePosCheck(hIn, &x, &y, &button); // Moude ��ġ �� ���� �˻�
		gotoxy(x, y);
		lp->curp = lp->headp->next;
		if (button == MOUSELEFTCLICK) // ���콺 ������ư click
		{
			for (int res = 1; res <= 10; res++)
			{
				if (x >= ((Beverage*)(lp->curp + 1))->x + 2 && x <= ((Beverage*)(lp->curp + 1))->x + 2 + buttonWidth)
				{
					if (y >= ((Beverage*)(lp->curp + 1))->y + 2 && y <= ((Beverage*)(lp->curp + 1))->y + 2 + buttonWidth)
					{
						return res;
					}
					else
					{
						lp->curp = lp->curp->next;
					}
				}
				else if (x >= 80 && x <= 88)
				{
					if (y >= 3 && y <= 5)
					{
						return 11;
					}
					else if (y >= 7 && y <= 9)
					{
						return 12;
					}
					else if (y >= 11 && y <= 13)
					{
						return 13;
					}
				}
				else if (x >= 62 && x <= 66)
				{
					if (y >= 25 && y <= 27)
					{
						return -1;
					}
				}
				else if (x >= 31 && x <= 37)
				{
					if (y >= 32 && y <= 33)
					{
						return -2;
					}
				}
				else if (x >= 62 && x <= 74 && y >= 24 && y <= 28)
				{
					return -3;
				}
				else
				{
					lp->curp = lp->curp->next;
				}
			}
		}
		else if (button == MOUSECENTER) // ���콺 �����ư click
		{
			return 0;
		}
	}

	// �ؽ�Ʈ �����ȯ
	textMode(hIn, defaultMode);

	return 0;
}


HANDLE mouseMode()
{
	HANDLE hIn;

	hIn = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	return hIn;
}

void textMode(HANDLE hIn, DWORD defaultMode)
{
	SetConsoleMode(hIn, defaultMode);  // mouse���� ���¸� �����ϰ� ��������(text����)�� ���ư�
}
void mousePosCheck(HANDLE hIn, int *x, int *y, int * button)
{
	DWORD  dwNOER;
	INPUT_RECORD rec;
	ReadConsoleInput(hIn, &rec, 1, &dwNOER);

	if (rec.EventType == MOUSE_EVENT)
	{
		*x = rec.Event.MouseEvent.dwMousePosition.X;
		*y = rec.Event.MouseEvent.dwMousePosition.Y;
		*button = rec.Event.MouseEvent.dwButtonState;
		return;
	}

}
void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void textcolor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
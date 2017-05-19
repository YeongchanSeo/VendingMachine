#include "mouseClick.h"
#include "Linkedlist.h"
#include "beverage.h"

int mouseClick(Linkedlist *lp)
{
	int res = 0;
	int x, y;
	int button;
	HANDLE hIn;
	DWORD defaultMode; // 현재 모드 저장변수
	int buttonWidth = 8, buttonHeight = 2;

	// 기본 모드 저장
	hIn = GetStdHandle(STD_INPUT_HANDLE); // 수행중인 콘솔의 핸들을 얻어옴
	GetConsoleMode(hIn, &defaultMode); // 콘솔창의 현재 상태(text입력 or mouse입력)를 저장해옴

	// 마우스 이벤트 테스트
	hIn = mouseMode();  // 콘솔창의 상태를 MOUSE MODE로 설정

	while (1)
	{
		mousePosCheck(hIn, &x, &y, &button); // Moude 위치 및 상태 검사
		gotoxy(x, y);
		lp->curp = lp->headp->next;
		if (button == MOUSELEFTCLICK) // 마우스 좌측버튼 click
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
		else if (button == MOUSECENTER) // 마우스 가운데버튼 click
		{
			return 0;
		}
	}

	// 텍스트 모드전환
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
	SetConsoleMode(hIn, defaultMode);  // mouse제어 상태를 종료하고 이전상태(text상태)로 돌아감
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
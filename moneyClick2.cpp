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
	int maxnum = 100; /*음료수 최대 개수*/
	int res = 0;
	int sx = 14, sy = 5;
	int x, y;
	int button;
	HANDLE hIn;
	DWORD defaultMode; // 현재 모드 저장변수
	int buttonWidth = 8, buttonHeight = 2;
	int boxlength = 12;
	int boxheight = 3;
	struct time time;
	// 기본 모드 저장
	hIn = GetStdHandle(STD_INPUT_HANDLE); // 수행중인 콘솔의 핸들을 얻어옴
	GetConsoleMode(hIn, &defaultMode); // 콘솔창의 현재 상태(text입력 or mouse입력)를 저장해옴

	// 마우스 이벤트 테스트
	hIn = mouseMode();  // 콘솔창의 상태를 MOUSE MODE로 설정
	while (1)
	{
		timer(&time);
		gotoxy(84, 1);
		if (time.hour > 12){ time.hour -= 12; printf("오후"); }
		else{ printf("오전"); }
		printf(" %u:%u:%u\n", time.hour, time.min, time.sec);
		mousePosCheck(hIn, &x, &y, &button); // Moude 위치 및 상태 검사
		gotoxy(x, y);
		if (button == MOUSELEFTCLICK) // 마우스 좌측버튼 click
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
		if (button == MOUSECENTER) // 마우스 우측버튼 click
		{
			return 0;
		}
	}

	// 텍스트 모드전환

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
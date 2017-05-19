#include "main.h"


int main()
{
	Linkedlist list;
	Money saveM, changeM, initM;
	char menuList[3][10] = { "판매모드", "관리모드", "종    료" };
	int res, menuCnt;
	menuCnt = sizeof(menuList) / sizeof(menuList[0]);
	init(&list, &saveM, &changeM, &initM);//음료구조체를 링크드 리스트로 만든다.

	while (1)
	{
		res = menu(menuList, menuCnt);//메뉴 선택하는 함수를 불러옴
		if (res == 1)
		{
			sellMode(&saveM, &changeM, &list);//판매모드를 선택했을경우
		}
		else if (res == 2)
		{
			manageMode(&saveM, &changeM, &initM, &list);//관리모드를 선택했을경우
		}
		else
		{
			save(&list, &saveM, &changeM);//저장 후 종료
			return 0;
		}
	}

	return 0;
}

int menu(char(*p)[10], int menuCnt)
{
	int i, point = 0, sx = 21, sy = 10, kFlag;
	char ch, ascii;

	system("mode con lines=25 cols=80");
	for (i = 0; i < 25; ++i)
	{
		textcolor(BLACK, WHITE);
		printf("                                                                                ");//화면을 흰색창으로
	}
	gotoxy(0, 0);

	while (1)
	{
		for (i = 0; i < menuCnt; i++)
		{
			if (point == i)
			{
				textcolor(WHITE, BLACK);//가리키는 곳 반전
			}
			else
			{
				textcolor(BLACK, WHITE);
			}

			gotoxy(sx + 15 * i, sy);
			printf("%s", p[i]);
		}
		ascii = getch();
		ch = inKey(&kFlag, ascii);
		if (kFlag == COMMON_KEY)
		{
			if (ch == '\r'){ textcolor(BLACK, WHITE); break; }//엔터를 누르면 원래대로
		}
		else
		{
			switch (ch)
			{
			case LEFT_ARROW: point--; break;
			case RIGHT_ARROW: point++; break;
			}
		}
		if (point < 0){ point = 0; }
		else if (point >= menuCnt){ point = menuCnt - 1; }
	}

	return point + 1;
}

char inKey(int *keyFlag, char ascii)
{
	char scan;

	if (ascii == -32 || ascii == 0){
		scan = getch();
		*keyFlag = SPECIAL_KEY;
		return (scan);
	}
	else {
		*keyFlag = COMMON_KEY;
		return (ascii);
	}
}

void save(Linkedlist *lp, Money *saveM, Money *changeM)
{
	FILE *fp;
	fp = fopen("c:\\data\\Beverage_init.txt", "w");
	lp->curp = lp->headp->next;
	while (lp->curp != lp->tailp)
	{
		fprintf(fp, "%s", ((Beverage *)(lp->curp + 1))->name);
		fprintf(fp, "%d\n", ((Beverage *)(lp->curp + 1))->quantity);
		fprintf(fp, "%d\n", ((Beverage *)(lp->curp + 1))->pick);
		fprintf(fp, "%d\n", ((Beverage *)(lp->curp + 1))->price);
		fprintf(fp, "%d\n", ((Beverage *)(lp->curp + 1))->color);
		fprintf(fp, "%d\n", ((Beverage *)(lp->curp + 1))->x);
		fprintf(fp, "%d\n", ((Beverage *)(lp->curp + 1))->y);
		fprintf(fp, "%d\n", ((Beverage *)(lp->curp + 1))->cancolor);
		lp->curp = lp->curp->next;
	}
	fclose(fp);
	fp = fopen("c:\\data\\Money_input.txt.", "w");
	fprintf(fp, "%d\n", saveM->m1000);
	fprintf(fp, "%d\n", saveM->m500);
	fprintf(fp, "%d\n", saveM->m100);
	fclose(fp);

	fp = fopen("c:\\data\\Money_change.txt", "w");
	fprintf(fp, "%d\n", changeM->m1000);
	fprintf(fp, "%d\n", changeM->m500);
	fprintf(fp, "%d\n", changeM->m100);
	fclose(fp);

	return;
}

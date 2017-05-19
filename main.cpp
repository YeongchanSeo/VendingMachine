#include "main.h"


int main()
{
	Linkedlist list;
	Money saveM, changeM, initM;
	char menuList[3][10] = { "�ǸŸ��", "�������", "��    ��" };
	int res, menuCnt;
	menuCnt = sizeof(menuList) / sizeof(menuList[0]);
	init(&list, &saveM, &changeM, &initM);//���ᱸ��ü�� ��ũ�� ����Ʈ�� �����.

	while (1)
	{
		res = menu(menuList, menuCnt);//�޴� �����ϴ� �Լ��� �ҷ���
		if (res == 1)
		{
			sellMode(&saveM, &changeM, &list);//�ǸŸ�带 �����������
		}
		else if (res == 2)
		{
			manageMode(&saveM, &changeM, &initM, &list);//������带 �����������
		}
		else
		{
			save(&list, &saveM, &changeM);//���� �� ����
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
		printf("                                                                                ");//ȭ���� ���â����
	}
	gotoxy(0, 0);

	while (1)
	{
		for (i = 0; i < menuCnt; i++)
		{
			if (point == i)
			{
				textcolor(WHITE, BLACK);//����Ű�� �� ����
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
			if (ch == '\r'){ textcolor(BLACK, WHITE); break; }//���͸� ������ �������
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

#define D1 "��" 
#define D2 "��" 
#define D3 "��" 
#define D4 "��" 
#define D9 "��" 
#define D10 "��" 

#include"Linkedlist.h"
#include"beverage.h"
#include<Windows.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>

void clrscr(int, int, int, int);
void gotoxy(int x, int y);

void modifyStock(Linkedlist *lp, int res)
{
	int tquantity;
	int tprice;
	char tname[20];
	int sx = 20, sy = 15;
	int length = 50;
	int height = 9;
	int i;

	clrscr(sx, sy, sx + length, sy + height); /*�Է� ���� ȭ���� ����� �κ��� �����*/

	/*�Է� ���� ȭ���� �ڽ��� ����Ѵ�*/
	gotoxy(sx, sy);
	printf("%s", D1);
	gotoxy(sx + length, sy);
	printf("%s", D3);
	gotoxy(sx, sy + height);
	printf("%s", D2);
	gotoxy(sx + length, sy + height);
	printf("%s", D4);

	for (i = sx + 2; i<sx + length; i += 2)
	{
		gotoxy(i, sy);
		printf("%s", D10);
		gotoxy(i, sy + height);
		printf("%s", D10);
	}
	for (i = sy + 1; i<sy + height; i++)
	{
		gotoxy(sx, i);
		printf("%s", D9);
		gotoxy(sx + length, i);
		printf("%s", D9);
	}
	gotoxy(sx + 2, sy + height / 2 - 1);
	printf("������ ����� �̸��� �Է��Ͻÿ� :");
	fflush(stdin);
	fgets(tname, sizeof(tname), stdin);
	//gets(tname);
	//tname[strlen(tname)] = '\n';
	//tname[strlen(tname) + 1] = '\0';
	gotoxy(sx + 2, sy + height / 2 + 1);
	printf("ä�� ��� ������ �Է��Ͻÿ� :");
	scanf("%d", &tquantity);
	if (tquantity>100)
	{
		tquantity = 100;
	}
	gotoxy(sx + 2, sy + height / 2 + 3);
	printf("������ ������ �Է��Ͻÿ� :");
	scanf("%d", &tprice);

	/*�ش� ������ ����ü�� �����Ѵ�*/
	lp->curp = lp->headp->next;
	for (i = 1; i<res; i++)
	{
		lp->curp = lp->curp->next;
	}
	/*�ش� ������ �̸��� ��� ���� ������ �����Ѵ�*/
	if (strcmp(((Beverage *)(lp->curp + 1))->name, tname) == 0)
	{
		((Beverage *)(lp->curp + 1))->quantity = tquantity;
		((Beverage *)(lp->curp + 1))->price = tprice;
	}
	else
	{
		strcpy(((Beverage *)(lp->curp + 1))->name, tname);
		((Beverage *)(lp->curp + 1))->quantity = tquantity;
		((Beverage *)(lp->curp + 1))->price = tprice;
		((Beverage *)(lp->curp + 1))->pick = 0;
	}
}

void clrscr(int startX, int startY, int endX, int endY)
{
	int i, j;
	for (i = startY; i <= endY; i++){
		for (j = startX; j <= endX; j++){
			gotoxy(j, i);
			putch(' ');
		}
	}
}
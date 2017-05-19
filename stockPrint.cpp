//�ڽ� ����
#define D1 "��" 
#define D2 "��" 
#define D3 "��" 
#define D4 "��" 
#define D5 "��" 
#define D6 "��" 
#define D7 "��" 
#define D8 "��" 
#define D9 "��" 
#define D10 "��" 
#define D11 "��" 

#define BLACK 0 
#define BROWN 6 
#define LIGHTGRAY 7 
#define YELLOW 14 
#define WHITE 15 

#include<stdio.h>
#include <conio.h> 
#include<windows.h> 
#include<string.h>
#include<time.h>
#include"money.h"
#include"beverage.h"
#include"Linkedlist.h"

void gotoxy(int x, int y);
void textcolor(int foreground, int background);;
void makebox(int sx, int sy, char *message);
void stockPrint(Linkedlist *lp, Money * changeM, Money * saveM);
void printMoney(Money *saveM, Money* changeM, int sx, int sy, int col, int row);
void printBeverage(Linkedlist *lp, int sx, int sy, int col, int first, int second, int third);
void culranking(Linkedlist *lp, int *first, int *second, int *third);


void stockPrint(Linkedlist *lp, Money * changeM, Money * saveM)
{
	int sx = 14, sy = 5;
	int first, second, third;
	system("mode con lines=43 cols=100");

	culranking(lp, &first, &second, &third);
	gotoxy(sx + 1, sy - 2);
	printf("# ����� ���");
	printBeverage(lp, sx, sy, 4, first, second, third);
	sy = sy + 24;
	gotoxy(sx + 1, sy);
	printf("# �ݾ� ��Ȳ");
	printMoney(saveM, changeM, sx, sy + 2, 4, 4);

	makebox(80, 32, "�����ϱ�");
	makebox(80, 36, "�ܵ�ä���");
}

void culranking(Linkedlist *lp, int *first, int *second, int *third) /*1,2,3�� ���� ã��*/
{
	int pary[10];
	int size;
	int temp;
	int i = 0, j, num = 1;

	lp->curp = lp->headp->next;
	while (lp->curp != lp->tailp) /*pary �迭�� ���� ���� �����ϱ�*/
	{
		pary[i] = ((Beverage *)(lp->curp + 1))->pick;
		lp->curp = lp->curp->next;
		i++;
	}
	size = i;
	for (i = 0; i<size - 1; i++) /*linkedlist ������ ���� pary�� ������������ sort*/
	{
		for (j = i + 1; j<size; j++)
		{
			if (pary[i] <= pary[j])
			{
				temp = pary[i];
				pary[i] = pary[j];
				pary[j] = temp;
			}
		}
	}
	*first = pary[0]; /*1,2,3�� ���� ����*/
	for (i = 1; i<size; i++)
	{
		if (pary[i] == *first)
		{
			num++;
		}
		else if (num == 1)
		{
			*second = pary[i];
			temp = i;
			num++;
			break;
		}
		else if (num == 2)
		{
			*third = pary[i];
			temp = size;
			break;
		}
	}
	for (i = temp + 1; i<size; i++)
	{
		if (pary[i] == *second)
		{
			num++;
		}
		else if (num == 2)
		{
			*third = pary[i];
			break;
		}
	}
}

void printMoney(Money *saveM, Money* changeM, int sx, int sy, int col, int row) /*�ݾ� ���� ȭ�� ���*/
{
	int length = 16; /*�� ĭ�� ���α���*/
	int totalM1 = 0, totalM2 = 0; /*�Ѿ� �����ϴ� ����*/
	int i, j;

	totalM1 += saveM->m1000 * 1000;
	totalM1 += saveM->m500 * 500;
	totalM1 += saveM->m100 * 100;

	totalM2 += changeM->m1000 * 1000;
	totalM2 += changeM->m500 * 500;
	totalM2 += changeM->m100 * 100;

	for (j = 0; j<row + 1; j++)
	{
		for (i = 0; i<length*col; i += 2)
		{
			gotoxy(sx + i, sy + 2 * j);
			printf("%s", D10);
		}
		gotoxy(sx + 1, sy + 2 * j + 1);
		switch (j)
		{
		case 0: printf("*  �Աݵȱݾ�");
			gotoxy(sx + 2 + length, sy + 2 * j + 1); printf("1000��");
			gotoxy(sx + 2 + length * 2, sy + 2 * j + 1); printf("500��");
			gotoxy(sx + 2 + length * 3, sy + 2 * j + 1); printf("100��"); break;
		case 1: printf("    %d", totalM1);  /*���� ���*/
			gotoxy(sx + 2 + length, sy + 2 * j + 1); printf("  %d", saveM->m1000);
			gotoxy(sx + 2 + length * 2, sy + 2 * j + 1); printf("  %d", saveM->m500);
			gotoxy(sx + 2 + length * 3, sy + 2 * j + 1); printf("  %d", saveM->m100); break;
		case 2: printf("*   �ܵ�");
			gotoxy(sx + 2 + length, sy + 2 * j + 1); printf("1000��");
			gotoxy(sx + 2 + length * 2, sy + 2 * j + 1); printf("500��");
			gotoxy(sx + 2 + length * 3, sy + 2 * j + 1); printf("100��"); break;
		case 3: printf("    %d", totalM2);  /*�ܵ� ���*/
			gotoxy(sx + 2 + length, sy + 2 * j + 1); printf("  %d", changeM->m1000);
			gotoxy(sx + 2 + length * 2, sy + 2 * j + 1); printf("  %d", changeM->m500);
			gotoxy(sx + 2 + length * 3, sy + 2 * j + 1); printf("  %d", changeM->m100); break;
		}
	}
}

void printBeverage(Linkedlist *lp, int sx, int sy, int col, int first, int second, int third) /*���� ��� ���*/
{
	int length = 16;
	int maxnum = 100; /*����� �ִ� ����*/
	int i, j = 0;

	lp->curp = lp->headp->next;

	while (lp->curp != lp->tailp)
	{
		for (i = 0; i<length*col; i += 2) /*���ζ��� ���*/
		{
			gotoxy(sx + i, sy + 2 * j);
			printf("%s", D10);
		}
		gotoxy(sx + 1, sy + 2 * j + 1);
		if (j == 0) /*ǥ�� ó���κ� ���*/
		{
			printf("*   ǰ��");
			gotoxy(sx + 2 + length, sy + 2 * j + 1); printf("���(�ִ밳��)");
			gotoxy(sx + 2 + length * 2, sy + 2 * j + 1); printf("  ����");
			gotoxy(sx + 2 + length * 3, sy + 2 * j + 1); printf("�ǸŰ���");
		}
		else /*����� ���� ���*/
		{
			if (((Beverage *)(lp->curp + 1))->pick == first) /*����� �´� �� ���*/
			{
				textcolor(14, 15);
				printf("��");
				textcolor(0, 15);
			}
			else if (((Beverage *)(lp->curp + 1))->pick == second)
			{
				textcolor(7, 15);
				printf("��");
				textcolor(0, 15);
			}
			else if (((Beverage *)(lp->curp + 1))->pick == third)
			{
				textcolor(6, 15);
				printf("��");
				textcolor(0, 15);
			}
			else
			{
				printf("* ");
			}
			printf(" %s", ((Beverage *)(lp->curp + 1))->name); /*����� ���� ���*/
			gotoxy(sx + 2 + length, sy + 2 * j + 1); printf("  %d(%d)", ((Beverage *)(lp->curp + 1))->quantity, maxnum);
			gotoxy(sx + 2 + length * 2, sy + 2 * j + 1); printf("  %d", ((Beverage *)(lp->curp + 1))->price);
			gotoxy(sx + 2 + length * 3, sy + 2 * j + 1); printf("  %d", ((Beverage *)(lp->curp + 1))->pick);

			lp->curp = lp->curp->next;
		}
		j++;
	}
	for (i = 0; i<length*col; i += 2) /*������ ���� ���*/
	{
		gotoxy(sx + i, sy + 2 * j);
		printf("%s", D10);
	}
	gotoxy(sx + 1, sy + 2 * j + 1);
}

void makebox(int sx, int sy, char* message) /*�����ϱ�, �ܵ�ä��� ��ư ���*/
{
	int length = 12;
	int height = 3;
	int i;

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
	gotoxy(sx + 2, sy + height / 2 + 1);
	printf("%s", message);
}

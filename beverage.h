#pragma once
#include "Linkedlist.h"
#include "Money.h"

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

typedef struct beverage
{
	char name[20]; /* ����� */
	int quantity;/* ��� */
	int pick; /* ���õ� Ƚ�� */
	int price; /* ����� ���� */
	int color; /* �Ǹ� ����, �Ұ��� ǥ�� */
	int x;/* ������ ��ǥ��*/
	int y;/* ������ ��ǥ��*/
	int cancolor;/*����� ��*/
}Beverage;
void init(Linkedlist *lp, Money *saveM, Money *changeM, Money *initM);
void beverageCpy(void *p1, void *p2);
void beverageNamePrint(void *p, int sx, int sy);
void beveragePricePrint(void *p);

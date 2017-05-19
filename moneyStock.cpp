#include"Linkedlist.h"
#include"money.h"
#include"beverage.h"
#include<stdio.h>

void stockPrint(Linkedlist *lp, Money * changeM, Money * saveM);
void modifyStock(Linkedlist *lp, int res);
void collectMoney(Money * saveM);
void fillChange(Money * changeM);
int mouseClick2();
void gotoxy(int x, int y);;

void moneyStock(Money *saveM, Money *changeM, Money *initM, Linkedlist *lp)
{
	int res; /*마우스 res값을 받을 변수*/
	int inichange = 1000 * initM->m1000 + 500 * initM->m500 + 100 * initM->m100;
	int sumsaveM = 0;
	int sumchangeM = 0;
	int mymoney = 0;

	sumsaveM = saveM->m1000 * 1000 + saveM->m500 * 500 + saveM->m100 * 100;
	sumchangeM = changeM->m1000 * 1000 + changeM->m500 * 500 + changeM->m100 * 100;
	mymoney = sumsaveM + sumchangeM - inichange;

	while (1)
	{
		stockPrint(lp, changeM, saveM);
		gotoxy(60, 30);
		printf("현재 수익 : %d", mymoney);
		res = mouseClick2();
		if (res >= 1 && res <= 10)
		{
			modifyStock(lp, res);
			res = 0;
		}
		else if (res == 13)
		{
			collectMoney(saveM);
		}
		else if (res == 14)
		{
			fillChange(changeM);
		}
		else if (res == 0)
		{
			break;
		}
	}

}

void collectMoney(Money * saveM)
{
	saveM->m1000 = 0;
	saveM->m500 = 0;
	saveM->m100 = 0;
}

void fillChange(Money * changeM)
{
	changeM->m1000 = 1000;
	changeM->m500 = 1000;
	changeM->m100 = 1000;
}
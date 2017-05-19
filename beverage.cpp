#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include "money.h"
#include "beverage.h"
#include "mouseClick.h"

void init(Linkedlist *lp, Money *saveM, Money *changeM, Money *initM)
{
	Beverage beverage;
	FILE *fp;
	char temp[20];//음료명 들어올 변수
	fp = fopen("C:\\data\\Beverage_init.txt", "r");
	create(lp);
	while (fgets(temp, sizeof(temp), fp) != NULL)
	{
		strcpy(beverage.name, temp);
		fscanf(fp, "%d\n", &beverage.quantity);
		fscanf(fp, "%d\n", &beverage.pick);
		fscanf(fp, "%d\n", &beverage.price);
		fscanf(fp, "%d\n", &beverage.color);
		fscanf(fp, "%d\n", &beverage.x);
		fscanf(fp, "%d\n", &beverage.y);
		fscanf(fp, "%d\n", &beverage.cancolor);
		appendFromTail(lp, &beverage, sizeof(Beverage), beverageCpy);
	}
	fclose(fp);
	fp = fopen("c:\\data\\Money_input.txt", "r");
	while (fscanf(fp, "%d\n", &saveM->m1000) != EOF)
	{
		fscanf(fp, "%d\n", &saveM->m500);
		fscanf(fp, "%d\n", &saveM->m100);
	}
	fclose(fp);
	fp = fopen("c:\\data\\Money_change.txt", "r");
	while (fscanf(fp, "%d\n", &changeM->m1000) != EOF)
	{
		fscanf(fp, "%d\n", &changeM->m500);
		fscanf(fp, "%d\n", &changeM->m100);
	}
	fclose(fp);
	initM->m1000 = changeM->m1000;
	initM->m500 = changeM->m500;
	initM->m100 = changeM->m100;

	return;
}


void beverageCpy(void *p1, void *p2)
{
	strcpy(((Beverage *)p1)->name, ((Beverage *)p2)->name);
	((Beverage *)p1)->quantity = ((Beverage *)p2)->quantity;
	((Beverage *)p1)->pick = ((Beverage *)p2)->pick;
	((Beverage *)p1)->price = ((Beverage *)p2)->price;
	((Beverage *)p1)->color = ((Beverage *)p2)->color;
	((Beverage *)p1)->x = ((Beverage *)p2)->x;
	((Beverage *)p1)->y = ((Beverage *)p2)->y;
	((Beverage *)p1)->cancolor = ((Beverage *)p2)->cancolor;
	return;
}

void beveragePricePrint(void *p)
{
	int letterColor, backColor;

	if (((Beverage *)p)->color == 1)
	{
		letterColor = LIGHTGREEN;
		backColor = GREEN;
	}
	else if (((Beverage *)p)->color == 0)
	{
		letterColor = LIGHTRED;
		backColor = RED;
	}
	else if (((Beverage *)p)->color == -1)
	{
		letterColor = BLACK;
		backColor = DARKGRAY;
	}
	else
	{
		letterColor = BROWN;
		backColor = YELLOW;
	}

	textcolor(letterColor, backColor);
	printf("●");
	textcolor(BLACK, backColor);
	printf("%4d", ((Beverage*)p)->price);
	//textcolor원래대로 
}

void beverageNamePrint(void *p, int x, int y)
{
	int i, len;
	len = strlen(((Beverage*)p)->name);
	for (i = 0; i != len; i++)
	{
		if (((Beverage*)p)->name[i] == ' '){ y++; x -= i + 1; }
		else
		{
			gotoxy(x + i, y);
			printf("%c", ((Beverage*)p)->name[i]);
		}
	}
}
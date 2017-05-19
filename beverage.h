#pragma once
#include "Linkedlist.h"
#include "Money.h"

#define D1 "┏" 
#define D2 "┗" 
#define D3 "┓" 
#define D4 "┛" 
#define D5 "┳" 
#define D6 "┻" 
#define D7 "┫" 
#define D8 "┣" 
#define D9 "┃" 
#define D10 "━" 
#define D11 "╋" 

typedef struct beverage
{
	char name[20]; /* 음료수 */
	int quantity;/* 재고량 */
	int pick; /* 선택된 횟수 */
	int price; /* 음료수 가격 */
	int color; /* 판매 가능, 불가능 표시 */
	int x;/* 음료의 좌표값*/
	int y;/* 음료의 좌표값*/
	int cancolor;/*음료수 색*/
}Beverage;
void init(Linkedlist *lp, Money *saveM, Money *changeM, Money *initM);
void beverageCpy(void *p1, void *p2);
void beverageNamePrint(void *p, int sx, int sy);
void beveragePricePrint(void *p);

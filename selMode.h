#include "main.h"

void makeBox(int, int, int, int);
void print(Linkedlist *lp);
void showLeftMoney(int totalM, Linkedlist *lp);
int inputMoney(Linkedlist *lp, int res, Money *inputM, Money *saveM, Money* changeM);
void beveragePrint(Linkedlist *lp);
int selectBeverage(Money *inputM, Linkedlist *lp, Money *saveM, int res, Money *changeM);
void gotoxy(int x, int y);
void cancle(Money *inputM, Linkedlist *lp, Money* changeM);
void canPrint(Linkedlist *lp);
void moneyPrint(int);
void coinPrint();
void giveMoneyPrint();
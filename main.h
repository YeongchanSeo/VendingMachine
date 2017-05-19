#include <stdio.h>
#include <conio.h>
#include "beverage.h"
#include "mouseClick.h"
#include "Linkedlist.h"
#include "money.h"

#define COMMON_KEY 1 
#define SPECIAL_KEY 0 
#define F1 59 
#define F2 60 
#define F3 61 
#define F4 62 
#define F5 63 
#define F6 64 
#define F7 65 
#define F8 66 
#define F9 67 
#define F10 68 
#define UP_ARROW 72 
#define DOWN_ARROW 80 
#define LEFT_ARROW 75 
#define RIGHT_ARROW 77 
#define PAGEUP 73 
#define PAGEDOWN 81 
#define ENTER 13 
#define ESC 27 

char inKey(int *keyFlag, char);
int inputCh(int*, char, int);
int menu(char(*p)[10], int menuCnt);
void sellMode(Money *saveM, Money *changeM, Linkedlist *lp);
void manageMode(Money * saveM, Money * changeM, Money* initM, Linkedlist *lp);
void textcolor(int foreground, int background);
void gotoxy(int x, int y);
void save(Linkedlist *lp, Money *saveM, Money *changeM);
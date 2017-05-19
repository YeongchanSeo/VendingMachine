#pragma once
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "Linkedlist.h"

enum { MOUSEMOVE, MOUSELEFTCLICK, MOUSERIGHTCLICK, MOUSELEFTRIGHT, MOUSECENTER };
enum {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY, LIGHTBLUE,
	LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
};
HANDLE mouseMode();
int mouseClick(Linkedlist *lp);
void gotoxy(int x, int y);
void textcolor(int foreground, int background);
void mousePosCheck(HANDLE hIn, int *x, int *y, int * button);
void textMode(HANDLE hIn, DWORD defaultMode);
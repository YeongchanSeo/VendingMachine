#include <stdio.h>
#include<Windows.h>
#include "beverage.h"
#include "Linkedlist.h"
#include "money.h"

int login();
void moneyStock(Money *saveM, Money *changeM, Money *initM, Linkedlist *lp);;
void gotoxy(int x, int y);;

void manageMode(Money *saveM, Money *changeM, Money* initM, Linkedlist *lp)
{
	int res;

	res = login();
	switch (res)
	{
	case 1: moneyStock(saveM, changeM, initM, lp); break;
	case 0: return;
	}

}


int login()
{
	system("mode con lines=36 cols=93");
	FILE * fp; /*파일 포인터*/
	int cnt = 5; /*횟수 저장 변수*/
	char ID[1000]; /*아이디 저장 배열*/
	char inputID[1000]; /* 아이디를 입력받을 배열*/
	char password[1000]; /* 패스워드 저장배열*/
	char inputPassword[1000]; /*패스워드를 입력받을 배열*/
	char ch; /*패스워드 한자리 저장 변수*/
	int sx = 20, sy = 13;
	int length = 50;
	int height = 9;
	int i, j = 0, k;

	fp = fopen("c:\\data\\Login.txt", "r"); //Login.txt 파일 열기
	assert(fp != NULL);

	if (fgets(ID, sizeof(ID), fp) == NULL) { return 0; } // 파일에서 ID 읽어오기
	if (ID[strlen(ID) - 1] == '\n')
	{
		ID[strlen(ID) - 1] = '\0';
	}

	if (fgets(password, sizeof(password), fp) == NULL) { return 0; } //파일에서 password 읽어오기
	if (password[strlen(password) - 1] == '\n')
	{
		password[strlen(password) - 1] = '\0';
	}

	fclose(fp);


	for (i = 0; i<cnt; i++) //cnt 만큼 반복문 돌리기
	{
		system("cls");
		/*입력 받을 화면의 박스를 출력한다*/
		gotoxy(sx, sy);
		printf("%s", D1);
		gotoxy(sx + length, sy);
		printf("%s", D3);
		gotoxy(sx, sy + height);
		printf("%s", D2);
		gotoxy(sx + length, sy + height);
		printf("%s", D4);
		for (k = sx + 2; k<sx + length; k += 2)
		{
			gotoxy(k, sy);
			printf("%s", D10);
			gotoxy(k, sy + height);
			printf("%s", D10);
		}
		for (k = sy + 1; k<sy + height; k++)
		{
			gotoxy(sx, k);
			printf("%s", D9);
			gotoxy(sx + length, k);
			printf("%s", D9);
		}

		gotoxy(sx + 2, sy + height / 2);
		printf("ID를 입력하시오 : ");
		scanf("%s", inputID);
		gotoxy(sx + 2, sy + height / 2 + 2);
		printf("password를 입력하시오 : ");
		while (1)
		{
			ch = getch();
			if (ch == '\r')
			{
				break;
			}
			else if (ch == 8)
			{
				if (j <= 0)
				{
					j = 0;
				}
				else
				{
					j--;
					inputPassword[j] = '\0';
					printf("\b \b");
				}
			}
			else
			{
				printf("*");
				inputPassword[j] = ch;
				j++;
			}
		}
		inputPassword[j] = '\0';
		j = 0;
		if (strcmp(ID, inputID) == 0)
		{
			if (strcmp(password, inputPassword) == 0)
			{
				return 1;
			}
		}
	}

	return 0;
}
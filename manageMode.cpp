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
	FILE * fp; /*���� ������*/
	int cnt = 5; /*Ƚ�� ���� ����*/
	char ID[1000]; /*���̵� ���� �迭*/
	char inputID[1000]; /* ���̵� �Է¹��� �迭*/
	char password[1000]; /* �н����� ����迭*/
	char inputPassword[1000]; /*�н����带 �Է¹��� �迭*/
	char ch; /*�н����� ���ڸ� ���� ����*/
	int sx = 20, sy = 13;
	int length = 50;
	int height = 9;
	int i, j = 0, k;

	fp = fopen("c:\\data\\Login.txt", "r"); //Login.txt ���� ����
	assert(fp != NULL);

	if (fgets(ID, sizeof(ID), fp) == NULL) { return 0; } // ���Ͽ��� ID �о����
	if (ID[strlen(ID) - 1] == '\n')
	{
		ID[strlen(ID) - 1] = '\0';
	}

	if (fgets(password, sizeof(password), fp) == NULL) { return 0; } //���Ͽ��� password �о����
	if (password[strlen(password) - 1] == '\n')
	{
		password[strlen(password) - 1] = '\0';
	}

	fclose(fp);


	for (i = 0; i<cnt; i++) //cnt ��ŭ �ݺ��� ������
	{
		system("cls");
		/*�Է� ���� ȭ���� �ڽ��� ����Ѵ�*/
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
		printf("ID�� �Է��Ͻÿ� : ");
		scanf("%s", inputID);
		gotoxy(sx + 2, sy + height / 2 + 2);
		printf("password�� �Է��Ͻÿ� : ");
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
#include<stdio.h>
#include<Windows.h>
#include"Linkedlist.h"
#include"money.h"
#include"beverage.h"
//1. ����
//2. �޴���ȣ�� ������ menuNum�� �����Ѵ�.
//3. menu��ȣ�� menuNum�� �Է��Ѵ�.
//4. switch������ menuNum�� �˻��Ѵ�.
//4-1) 1�̸� moneyStock�Լ��� ȣ���Ѵ�.
//4-2) 2�� calculateMoney�� ȣ���Ѵ�.
//5. ��

void moneyStock(Money *saveM, Money *changeM, Money* initM, Linkedlist *lp);

void manage(Money * saveM, Money * changeM, Money *initM, Linkedlist *lp)
{
	int menuNum, i;
	system("cls");
	char *list[] = { "1. ���&�ݾ� ����\n", "2. ���� ����\n" };
	int size = sizeof(list) / sizeof(list[0]);
	while (1)
	{
		for (i = 0; i < size; i++)
		{
			printf("%s", list[i]);
		}
		printf("������ ��� ���� : ");
		scanf("%d", &menuNum);
		if (getchar() == '\n' && menuNum >0 && menuNum <3)
		{
			break;
		}
		fflush(stdin);
		system("cls");
	}
	switch (menuNum)
	{
	case 1: moneyStock(saveM, changeM, initM, lp); break;
	case 2: /*calculateMoney(lp);*/ break;
	}
}

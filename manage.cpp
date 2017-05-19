#include<stdio.h>
#include<Windows.h>
#include"Linkedlist.h"
#include"money.h"
#include"beverage.h"
//1. 시작
//2. 메뉴번호를 저장할 menuNum을 선언한다.
//3. menu번호를 menuNum에 입력한다.
//4. switch문으로 menuNum을 검사한다.
//4-1) 1이면 moneyStock함수를 호출한다.
//4-2) 2면 calculateMoney를 호출한다.
//5. 끝

void moneyStock(Money *saveM, Money *changeM, Money* initM, Linkedlist *lp);

void manage(Money * saveM, Money * changeM, Money *initM, Linkedlist *lp)
{
	int menuNum, i;
	system("cls");
	char *list[] = { "1. 재고&금액 관리\n", "2. 정산 관리\n" };
	int size = sizeof(list) / sizeof(list[0]);
	while (1)
	{
		for (i = 0; i < size; i++)
		{
			printf("%s", list[i]);
		}
		printf("실행할 모드 선택 : ");
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

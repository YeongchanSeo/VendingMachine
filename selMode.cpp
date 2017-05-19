#include "selMode.h"
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")

void sellMode(Money *saveM, Money *changeM, Linkedlist *lp)
{
	Money inputM = { 0, 0, 0 };//판매모드에서 입금용 Money 구조체 선언
	int res, totalM;
	lp->curp = lp->headp->next;
	while (lp->curp != lp->tailp)
	{
		((Beverage*)(lp->curp + 1))->color = -1;//색깔 초기화
		lp->curp = lp->curp->next;
	}
	print(lp);//음료구조체를 이용해 화면을 찍는다.
	while (1)
	{
		if (changeM->m1000 < 10 && changeM->m500 < 10 && changeM->m100 < 10)
		{
			textcolor(LIGHTRED, BLACK);
			makeBox(36, 2, 11, 22);
			gotoxy(14, 23);
			printf("잔돈 부족으로 판매를 중지합니다.");
			Sleep(2000);
			textcolor(LIGHTGRAY, BLACK);
			break;
		}
		res = mouseClick(lp);
		Sleep(50);//클릭이 두번 동시에 겹쳐 들어가는것 방지
		if (res > 0 && res < 11)
		{
			totalM = selectBeverage(&inputM, lp, saveM, res, changeM);
			if (totalM != -1)
			{
				showLeftMoney(totalM, lp);
				beveragePrint(lp);
				while (mouseClick(lp) != -2){}
				sndPlaySoundA("C:\\data\\1up.wav", SND_ASYNC | SND_NODEFAULT);
				Sleep(500);
				textcolor(YELLOW, BROWN);
				makeBox(40, 4, 14, 29);//음료수 나오는곳
				textcolor(LIGHTGRAY, BLACK);
			}
		}
		else if (res>10 && res < 14)
		{
			totalM = inputMoney(lp, res, &inputM, saveM, changeM);
			Sleep(300);
			showLeftMoney(totalM, lp);
			beveragePrint(lp);
		}
		else if (res == -1)
		{
			cancle(&inputM, lp, changeM);//취소버튼 클릭
		}
		else if (res == 0)
		{
			system("cls");
			break;
		}
	}
	return;
}

int inputMoney(Linkedlist *lp, int res, Money *inputM, Money* saveM, Money* changeM)//금액 버튼을 누르면 해당금액버튼에 맞는 inputM의 값을 증가시켜준다.
{
	int totalM;//오토변수 totalM 생성

	if (res == 11)//1000원 클릭시
	{
		inputM->m1000++;
		saveM->m1000++;
		sndPlaySoundA("C:\\data\\PipeWarp.wav", SND_ASYNC | SND_NODEFAULT);
	}
	else if (res == 12)//500원 클릭시
	{
		inputM->m500++;
		saveM->m500++;
		sndPlaySoundA("C:\\data\\Coin.wav", SND_ASYNC | SND_NODEFAULT);
	}
	else if (res == 13)//100원 클릭시
	{
		inputM->m100++;
		saveM->m100++;
		sndPlaySoundA("C:\\data\\Coin.wav", SND_ASYNC | SND_NODEFAULT);
	}
	totalM = inputM->m1000 * 1000 + inputM->m500 * 500 + inputM->m100 * 100;//값을 금액으로 바꾼다.
	if (totalM > 9900)//들어온 총 금액이 9900원 이상일 경우
	{
		if (res == 11)
		{
			inputM->m1000--;
			saveM->m1000--;
		}
		else if (res == 12)
		{
			inputM->m500--;
			saveM->m500--;
		}
		else if (res == 13)
		{
			inputM->m100--;
			saveM->m100--;
		}
	}

	totalM = inputM->m1000 * 1000 + inputM->m500 * 500 + inputM->m100 * 100;//값을 금액으로 바꾼다.
	if (res == 11)
	{
		moneyPrint(totalM);
		if (totalM + 1000>9900)
		{
			Sleep(500);
			sndPlaySoundA("C:\\data\\PipeWarp.wav", SND_ASYNC | SND_NODEFAULT);
			giveMoneyPrint();
			while (mouseClick(lp) != -3){}
			textcolor(LIGHTMAGENTA, LIGHTMAGENTA);//자판기 바탕색
			makeBox(12, 4, 62, 24);
			textcolor(LIGHTGRAY, BLACK);//금액표시판 색
			makeBox(6, 2, 68, 25);//현재 금액 출력 위치
			gotoxy(70, 26);
			printf("%d", totalM);
			textcolor(LIGHTRED, RED);
			makeBox(4, 2, 62, 25);//취소 버튼 위치
			gotoxy(63, 26);
			printf("취소");
			textcolor(LIGHTGRAY, BLACK);
		}
	}
	else
	{
		coinPrint();
	}

	return totalM;
}
void showLeftMoney(int totalM, Linkedlist *lp)//현재금액을 출력하고 음료구조체의 color값을 바꾼다.
{
	gotoxy(70, 26);//현재 금액이 출력되는 부분으로 가서 출력 x,y대신 숫자를 넣는다.
	printf("    ");//앞의 숫자를 지워준다.
	gotoxy(70, 26);
	printf("%d", totalM);//현재 금액을 출력한다
	if (!totalM)//totalM이 0이면
	{
		Sleep(300);//0을 잠시 출력후
		gotoxy(70, 26);
		printf("    ");// 아무것도 출력하지 않는다.
	}
	lp->curp = lp->headp->next;
	while (lp->curp != lp->tailp)
	{
		if (totalM >= ((Beverage *)(lp->curp + 1))->price && ((Beverage *)(lp->curp + 1))->quantity != 0)//살 수 있는 음료
		{
			((Beverage *)(lp->curp + 1))->color = 1;//녹색 출력
		}
		else//못사는 음료
		{
			if (totalM)
			{
				((Beverage *)(lp->curp + 1))->color = 0;//빨간색 출력
			}
			else
			{
				((Beverage *)(lp->curp + 1))->color = -1;//돈이 들어오지 않았으면 회색 출력
			}
		}
		lp->curp = lp->curp->next;
	}

	return;
}
void beveragePrint(Linkedlist *lp)//음료버튼과 가격 색깔 바꿔서 출력
{
	int x, y;
	int buttonWidth = 8, buttonHeight = 2;
	lp->curp = lp->headp->next;
	while (lp->curp != lp->tailp)
	{
		if (((Beverage *)(lp->curp + 1))->color == 1)
		{
			textcolor(BLACK, GREEN);//textcolor 텍스트 칼라 녹색으로 설정
		}
		else if (((Beverage *)(lp->curp + 1))->color == 0)
		{
			if (((Beverage*)(lp->curp + 1))->quantity == 0)
			{
				textcolor(LIGHTRED, MAGENTA);
				gotoxy(((Beverage*)(lp->curp + 1))->x + 6, ((Beverage*)(lp->curp + 1))->y + 2);
				printf("품절");
			}
			textcolor(BLACK, RED);//textcolor 텍스트 칼라 빨간색으로 설정
		}
		else
		{
			textcolor(BLACK, DARKGRAY);
		}
		//해당 구조체의 음료버튼을 출력
		x = ((Beverage *)(lp->curp + 1))->x;
		y = ((Beverage *)(lp->curp + 1))->y;
		makeBox(buttonWidth, buttonHeight, ((Beverage*)(lp->curp + 1))->x + 2, ((Beverage*)(lp->curp + 1))->y + 5);//음료선택버튼출력
		gotoxy(x + 4, y + 6);
		beveragePricePrint(lp->curp + 1);//음료 가격 출력
		textcolor(LIGHTGRAY, BLACK);//textcolor원래대로 
		lp->curp = lp->curp->next;
	}
	return;
}

int selectBeverage(Money *inputM, Linkedlist *lp, Money *saveM, int res, Money *changeM)
{
	int temp, i, x, y;
	int pric;
	int buttonWidth = 8, buttonHeight = 2;

	lp->curp = lp->headp->next;
	for (i = 1; i < res; i++)//내가 선택한 음료 구조체가 있는 곳으로 이동해 재고 감소시키고 가격을 pric에 저장한다.
	{
		lp->curp = lp->curp->next;
	}

	if (((Beverage *)(lp->curp + 1))->quantity != 0 && ((Beverage *)(lp->curp + 1))->color == 1)
	{
		((Beverage *)(lp->curp + 1))->quantity--;
		((Beverage *)(lp->curp + 1))->pick++;
		pric = ((Beverage *)(lp->curp + 1))->price;
		x = ((Beverage *)(lp->curp + 1))->x;
		y = ((Beverage *)(lp->curp + 1))->y;
		textcolor(BLACK, YELLOW);//textcolor 텍스트 칼라 녹색으로 설정
		makeBox(buttonWidth, buttonHeight, ((Beverage*)(lp->curp + 1))->x + 2, ((Beverage*)(lp->curp + 1))->y + 5);
		((Beverage *)(lp->curp + 1))->color = -2;

		sndPlaySoundA("C:\\data\\Jump.wav", SND_ASYNC | SND_NODEFAULT);

		gotoxy(x + 4, y + 6);
		beveragePricePrint(lp->curp + 1);//음료 가격 출력
		Sleep(300);
		textcolor(LIGHTGRAY, BLACK);
	}
	else
	{
		return -1;
	}
	if (inputM->m1000 != 0 || inputM->m500 != 0 || inputM->m100 != 0)
	{
		temp = (inputM->m1000 * 1000 + inputM->m500 * 500 + inputM->m100 * 100) - pric;
		inputM->m1000 = temp / 1000;
		inputM->m500 = (temp - 1000 * inputM->m1000) / 500;
		inputM->m100 = (temp - 1000 * inputM->m1000 - 500 * inputM->m500) / 100;
		canPrint(lp);
		return temp;
	}

	return -1;
}
void cancle(Money *inputM, Linkedlist *lp, Money *changeM)
{
	int totalM = inputM->m1000 + inputM->m500 + inputM->m100;
	changeM->m1000 -= inputM->m1000;
	changeM->m500 -= inputM->m500;
	changeM->m100 -= inputM->m100;
	inputM->m1000 = 0;
	inputM->m500 = 0;
	inputM->m100 = 0;
	sndPlaySoundA("C:\\data\\AlertDC.wav", SND_ASYNC | SND_NODEFAULT);
	if (totalM)
	{
		textcolor(LIGHTGRAY, MAGENTA);
		gotoxy(68, 30);
		printf("●");
		Sleep(100);
		gotoxy(68, 30);
		printf(" ");
		textcolor(DARKGRAY, MAGENTA);
		gotoxy(68, 31);
		printf("●");
		Sleep(100);
		gotoxy(68, 31);
		printf(" ");
		textcolor(BLACK, MAGENTA);
		gotoxy(68, 32);
		printf("●");
		Sleep(300);
		gotoxy(68, 32);
		printf(" ");
		textcolor(LIGHTGRAY, BLACK);
	}
	showLeftMoney(0, lp);//처음부터 끝까지 다 빨간색으로 출력해야해서
}

void makeBox(int width, int height, int sx, int sy)
{
	int i, j;
	gotoxy(sx, sy);
	printf("%s", D1);
	for (i = 2; i < width; i += 2)
	{
		gotoxy(sx + i, sy);
		printf("%s", D10);
	}
	gotoxy(sx + width, sy);
	printf("%s", D3);
	for (i = 1; i < height; ++i)
	{
		for (j = 0; j < 2; ++j)
		{
			gotoxy(sx + j*width, sy + i);
			printf("%s", D9);
		}
	}

	gotoxy(sx, sy + height);
	printf("%s", D2);
	for (i = 2; i < width; i += 2)
	{
		gotoxy(sx + i, sy + height);
		printf("%s", D10);
	}
	gotoxy(sx + width, sy + height);
	printf("%s", D4);
	for (i = 2; i < width; i += 2)
	{
		for (j = 1; j < height; ++j)
		{
			gotoxy(sx + i, sy + j);
			printf("  ");
		}
	}
}

void print(Linkedlist* lp)
{
	system("mode con lines=36 cols=93");
	int totalWidth = 74, totalHeight = 33, boxWidth = 12, boxHeight = 8;
	int buttonWidth = 8, buttonHeight = 2, beverageWidth = 2, beverageHeight = 3;
	int moneyWidth = 8, moneyHeight = 2, mx = 80, my = 3;

	textcolor(WHITE, LIGHTMAGENTA);
	makeBox(totalWidth, totalHeight, 2, 1);//자판기 테두리 출력
	lp->curp = lp->headp->next;
	textcolor(WHITE, LIGHTBLUE);
	makeBox(moneyWidth, moneyHeight, mx, my);//1000원 출력
	gotoxy(mx + 4, my + 1);
	printf("%4d", 1000);//1000원 출력
	textcolor(LIGHTGRAY, DARKGRAY);
	makeBox(moneyWidth, moneyHeight, mx, my += 4);//500원 출력
	gotoxy(mx + 4, my + 1);
	printf("%4d", 500);//500원 출력
	textcolor(LIGHTGRAY, DARKGRAY);
	makeBox(moneyWidth, moneyHeight, mx, my += 4);//100원 출력
	gotoxy(mx + 4, my + 1);
	printf("%4d", 100);//100원 출력
	textcolor(LIGHTGRAY, BLACK);

	lp->curp = lp->headp->next;

	while (lp->curp != lp->tailp)
	{
		textcolor(WHITE, MAGENTA);
		makeBox(boxWidth, boxHeight, ((Beverage*)(lp->curp + 1))->x, ((Beverage*)(lp->curp + 1))->y);//음료수 박스 하나 출력
		textcolor(BLACK, LIGHTGRAY);
		beverageNamePrint(lp->curp + 1, ((Beverage*)(lp->curp + 1))->x + 5, ((Beverage*)(lp->curp + 1))->y + 3);//음료 이름 출력
		textcolor(BLACK, ((Beverage*)(lp->curp + 1))->cancolor);
		makeBox(beverageWidth, beverageHeight, ((Beverage*)(lp->curp + 1))->x + 2, ((Beverage*)(lp->curp + 1))->y + 2);//음료수 모형 출력
		textcolor(BLACK, DARKGRAY);
		makeBox(buttonWidth, buttonHeight, ((Beverage*)(lp->curp + 1))->x + 2, ((Beverage*)(lp->curp + 1))->y + 5);//음료수 버튼 출력
		gotoxy(((Beverage*)(lp->curp + 1))->x + 4, ((Beverage*)(lp->curp + 1))->y + 6);
		beveragePricePrint(lp->curp + 1);//음료 가격 출력

		lp->curp = lp->curp->next;
	}

	textcolor(YELLOW, BROWN);
	makeBox(40, 4, 14, 29);//음료수 나오는곳
	textcolor(LIGHTCYAN, CYAN);
	makeBox(12, 2, 62, 21);//지폐투입구 위치
	gotoxy(64, 22);//지폐투입구 글씨 출력할 위치
	printf("지폐투입구");
	textcolor(LIGHTGRAY, DARKGRAY);
	makeBox(6, 3, 51, 21);//동전구멍 테두리
	gotoxy(54, 22);
	printf("│");
	gotoxy(54, 23);
	printf("│");//동전구멍
	textcolor(LIGHTGRAY, BLACK);
	makeBox(6, 2, 68, 25);//현재 금액 출력 위치
	textcolor(LIGHTRED, RED);
	makeBox(4, 2, 62, 25);//취소 버튼 위치
	gotoxy(63, 26);
	printf("취소");
	textcolor(LIGHTMAGENTA, MAGENTA);
	makeBox(12, 4, 62, 29);//거스름돈 나오는곳 위치
	textcolor(LIGHTGRAY, BLACK);
	return;
}

void canPrint(Linkedlist *lp)
{
	int beverageWidth = 2, beverageHeight = 3, i, y = 0;
	while (y<3)
	{
		textcolor(BLACK, ((Beverage*)(lp->curp + 1))->cancolor);
		makeBox(6, 1, 31, 29 + y);//음료수 모형 출력
		gotoxy(30, 29);
		textcolor(YELLOW, BROWN);
		for (i = 0; i < 5; i++)
		{
			printf("%s", D10);
		}
		Sleep(200);
		textcolor(BROWN, BROWN);
		makeBox(6, 1, 31, 29 + y++);
	}
	textcolor(BLACK, ((Beverage*)(lp->curp + 1))->cancolor);
	makeBox(6, 1, 31, 32);//음료수 모형 출력
	gotoxy(30, 33);
	textcolor(YELLOW, BROWN);
	for (i = 0; i < 5; i++)
	{
		printf("%s", D10);
	}
	textcolor(LIGHTGRAY, BLACK);
}

void moneyPrint(int totalM)
{
	int y = 5, ly = 27;
	while (y != 0)
	{
		textcolor(WHITE, LIGHTBLUE);
		makeBox(12, y--, 62, 23);//들어가는 돈 위치
		if (ly - 3 > 23)
		{
			gotoxy(66, ly - 3);
			printf("1   \\");
		}
		if (ly - 2 > 23)
		{
			gotoxy(66, ly - 2);
			printf("0");
		}
		if (ly - 1 > 23)
		{
			gotoxy(66, ly - 1);
			printf("0   천");
		}
		if (ly > 23)
		{
			gotoxy(66, ly--);
			printf("0   원");
		}
		textcolor(LIGHTCYAN, CYAN);
		makeBox(12, 2, 62, 21);//지폐투입구 위치
		gotoxy(64, 22);//지폐투입구 글씨 출력할 위치
		printf("지폐투입구");
		Sleep(150);
		textcolor(LIGHTMAGENTA, LIGHTMAGENTA);
		makeBox(12, 4, 62, 24);
		textcolor(LIGHTGRAY, BLACK);
		makeBox(6, 2, 68, 25);//현재 금액 출력 위치
		gotoxy(70, 26);
		if (totalM < 9000)
		{
			printf("%d", totalM - 1000);//현재 금액을 출력한다
		}
		else
		{
			printf("%d", totalM);//현재 금액을 출력한다
		}
		textcolor(LIGHTRED, RED);
		makeBox(4, 2, 62, 25);//취소 버튼 위치
		gotoxy(63, 26);
		printf("취소");
	}

	textcolor(LIGHTGRAY, BLACK);
	gotoxy(70, 26);
	printf("%d", totalM);//현재 금액을 출력한다
	return;
}

void giveMoneyPrint()
{
	int y = 0, ly = 22;
	while (y != 6)
	{
		textcolor(WHITE, LIGHTBLUE);
		makeBox(12, y++, 62, 23);//들어가는 돈 위치
		if (ly - 3 > 23)
		{
			gotoxy(66, ly - 3);
			printf("1   \\");
		}
		if (ly - 2 > 23)
		{
			gotoxy(66, ly - 2);
			printf("0");
		}
		if (ly - 1 > 23)
		{
			gotoxy(66, ly - 1);
			printf("0   천");
		}
		if (ly > 23)
		{
			gotoxy(66, ly);
			printf("0   원");
		}
		ly++;
		textcolor(LIGHTCYAN, CYAN);
		makeBox(12, 2, 62, 21);//지폐투입구 위치
		gotoxy(64, 22);//지폐투입구 글씨 출력할 위치
		printf("지폐투입구");
		Sleep(150);
	}

	textcolor(LIGHTGRAY, BLACK);
	return;
}

void coinPrint()
{
	int i = 0;
	while (i++ < 2)
	{
		textcolor(BLACK, DARKGRAY);
		gotoxy(54, 24 - i);
		printf("%s", D9);
		if (i == 1)
		{
			textcolor(BLACK, LIGHTMAGENTA);
			gotoxy(54, 26 - i);
			printf("%s", D9);
		}
		else
		{
			gotoxy(54, 25 - i);
			printf("%s", D9);
		}
		textcolor(LIGHTGRAY, BLACK);
		Sleep(100 + 300 * (i - 1));
		textcolor(LIGHTGRAY, DARKGRAY);
		makeBox(6, 3, 51, 21);//동전구멍 테두리
		gotoxy(54, 22);
		printf("│");
		gotoxy(54, 23);
		printf("│");//동전구멍
		textcolor(LIGHTMAGENTA, LIGHTMAGENTA);
		gotoxy(55, 25);
		printf("  ");
	}
	textcolor(BLACK, DARKGRAY);
	gotoxy(54, 23);
	printf("%s", D9);
	Sleep(700);
	gotoxy(54, 23);
	textcolor(LIGHTGRAY, DARKGRAY);
	makeBox(6, 3, 51, 21);//동전구멍 테두리
	gotoxy(54, 22);
	printf("│");
	gotoxy(54, 23);
	printf("│");//동전구멍
	textcolor(LIGHTGRAY, BLACK);
}
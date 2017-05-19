#include "selMode.h"
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")

void sellMode(Money *saveM, Money *changeM, Linkedlist *lp)
{
	Money inputM = { 0, 0, 0 };//�ǸŸ�忡�� �Աݿ� Money ����ü ����
	int res, totalM;
	lp->curp = lp->headp->next;
	while (lp->curp != lp->tailp)
	{
		((Beverage*)(lp->curp + 1))->color = -1;//���� �ʱ�ȭ
		lp->curp = lp->curp->next;
	}
	print(lp);//���ᱸ��ü�� �̿��� ȭ���� ��´�.
	while (1)
	{
		if (changeM->m1000 < 10 && changeM->m500 < 10 && changeM->m100 < 10)
		{
			textcolor(LIGHTRED, BLACK);
			makeBox(36, 2, 11, 22);
			gotoxy(14, 23);
			printf("�ܵ� �������� �ǸŸ� �����մϴ�.");
			Sleep(2000);
			textcolor(LIGHTGRAY, BLACK);
			break;
		}
		res = mouseClick(lp);
		Sleep(50);//Ŭ���� �ι� ���ÿ� ���� ���°� ����
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
				makeBox(40, 4, 14, 29);//����� �����°�
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
			cancle(&inputM, lp, changeM);//��ҹ�ư Ŭ��
		}
		else if (res == 0)
		{
			system("cls");
			break;
		}
	}
	return;
}

int inputMoney(Linkedlist *lp, int res, Money *inputM, Money* saveM, Money* changeM)//�ݾ� ��ư�� ������ �ش�ݾ׹�ư�� �´� inputM�� ���� ���������ش�.
{
	int totalM;//���亯�� totalM ����

	if (res == 11)//1000�� Ŭ����
	{
		inputM->m1000++;
		saveM->m1000++;
		sndPlaySoundA("C:\\data\\PipeWarp.wav", SND_ASYNC | SND_NODEFAULT);
	}
	else if (res == 12)//500�� Ŭ����
	{
		inputM->m500++;
		saveM->m500++;
		sndPlaySoundA("C:\\data\\Coin.wav", SND_ASYNC | SND_NODEFAULT);
	}
	else if (res == 13)//100�� Ŭ����
	{
		inputM->m100++;
		saveM->m100++;
		sndPlaySoundA("C:\\data\\Coin.wav", SND_ASYNC | SND_NODEFAULT);
	}
	totalM = inputM->m1000 * 1000 + inputM->m500 * 500 + inputM->m100 * 100;//���� �ݾ����� �ٲ۴�.
	if (totalM > 9900)//���� �� �ݾ��� 9900�� �̻��� ���
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

	totalM = inputM->m1000 * 1000 + inputM->m500 * 500 + inputM->m100 * 100;//���� �ݾ����� �ٲ۴�.
	if (res == 11)
	{
		moneyPrint(totalM);
		if (totalM + 1000>9900)
		{
			Sleep(500);
			sndPlaySoundA("C:\\data\\PipeWarp.wav", SND_ASYNC | SND_NODEFAULT);
			giveMoneyPrint();
			while (mouseClick(lp) != -3){}
			textcolor(LIGHTMAGENTA, LIGHTMAGENTA);//���Ǳ� ������
			makeBox(12, 4, 62, 24);
			textcolor(LIGHTGRAY, BLACK);//�ݾ�ǥ���� ��
			makeBox(6, 2, 68, 25);//���� �ݾ� ��� ��ġ
			gotoxy(70, 26);
			printf("%d", totalM);
			textcolor(LIGHTRED, RED);
			makeBox(4, 2, 62, 25);//��� ��ư ��ġ
			gotoxy(63, 26);
			printf("���");
			textcolor(LIGHTGRAY, BLACK);
		}
	}
	else
	{
		coinPrint();
	}

	return totalM;
}
void showLeftMoney(int totalM, Linkedlist *lp)//����ݾ��� ����ϰ� ���ᱸ��ü�� color���� �ٲ۴�.
{
	gotoxy(70, 26);//���� �ݾ��� ��µǴ� �κ����� ���� ��� x,y��� ���ڸ� �ִ´�.
	printf("    ");//���� ���ڸ� �����ش�.
	gotoxy(70, 26);
	printf("%d", totalM);//���� �ݾ��� ����Ѵ�
	if (!totalM)//totalM�� 0�̸�
	{
		Sleep(300);//0�� ��� �����
		gotoxy(70, 26);
		printf("    ");// �ƹ��͵� ������� �ʴ´�.
	}
	lp->curp = lp->headp->next;
	while (lp->curp != lp->tailp)
	{
		if (totalM >= ((Beverage *)(lp->curp + 1))->price && ((Beverage *)(lp->curp + 1))->quantity != 0)//�� �� �ִ� ����
		{
			((Beverage *)(lp->curp + 1))->color = 1;//��� ���
		}
		else//����� ����
		{
			if (totalM)
			{
				((Beverage *)(lp->curp + 1))->color = 0;//������ ���
			}
			else
			{
				((Beverage *)(lp->curp + 1))->color = -1;//���� ������ �ʾ����� ȸ�� ���
			}
		}
		lp->curp = lp->curp->next;
	}

	return;
}
void beveragePrint(Linkedlist *lp)//�����ư�� ���� ���� �ٲ㼭 ���
{
	int x, y;
	int buttonWidth = 8, buttonHeight = 2;
	lp->curp = lp->headp->next;
	while (lp->curp != lp->tailp)
	{
		if (((Beverage *)(lp->curp + 1))->color == 1)
		{
			textcolor(BLACK, GREEN);//textcolor �ؽ�Ʈ Į�� ������� ����
		}
		else if (((Beverage *)(lp->curp + 1))->color == 0)
		{
			if (((Beverage*)(lp->curp + 1))->quantity == 0)
			{
				textcolor(LIGHTRED, MAGENTA);
				gotoxy(((Beverage*)(lp->curp + 1))->x + 6, ((Beverage*)(lp->curp + 1))->y + 2);
				printf("ǰ��");
			}
			textcolor(BLACK, RED);//textcolor �ؽ�Ʈ Į�� ���������� ����
		}
		else
		{
			textcolor(BLACK, DARKGRAY);
		}
		//�ش� ����ü�� �����ư�� ���
		x = ((Beverage *)(lp->curp + 1))->x;
		y = ((Beverage *)(lp->curp + 1))->y;
		makeBox(buttonWidth, buttonHeight, ((Beverage*)(lp->curp + 1))->x + 2, ((Beverage*)(lp->curp + 1))->y + 5);//���ἱ�ù�ư���
		gotoxy(x + 4, y + 6);
		beveragePricePrint(lp->curp + 1);//���� ���� ���
		textcolor(LIGHTGRAY, BLACK);//textcolor������� 
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
	for (i = 1; i < res; i++)//���� ������ ���� ����ü�� �ִ� ������ �̵��� ��� ���ҽ�Ű�� ������ pric�� �����Ѵ�.
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
		textcolor(BLACK, YELLOW);//textcolor �ؽ�Ʈ Į�� ������� ����
		makeBox(buttonWidth, buttonHeight, ((Beverage*)(lp->curp + 1))->x + 2, ((Beverage*)(lp->curp + 1))->y + 5);
		((Beverage *)(lp->curp + 1))->color = -2;

		sndPlaySoundA("C:\\data\\Jump.wav", SND_ASYNC | SND_NODEFAULT);

		gotoxy(x + 4, y + 6);
		beveragePricePrint(lp->curp + 1);//���� ���� ���
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
		printf("��");
		Sleep(100);
		gotoxy(68, 30);
		printf(" ");
		textcolor(DARKGRAY, MAGENTA);
		gotoxy(68, 31);
		printf("��");
		Sleep(100);
		gotoxy(68, 31);
		printf(" ");
		textcolor(BLACK, MAGENTA);
		gotoxy(68, 32);
		printf("��");
		Sleep(300);
		gotoxy(68, 32);
		printf(" ");
		textcolor(LIGHTGRAY, BLACK);
	}
	showLeftMoney(0, lp);//ó������ ������ �� ���������� ����ؾ��ؼ�
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
	makeBox(totalWidth, totalHeight, 2, 1);//���Ǳ� �׵θ� ���
	lp->curp = lp->headp->next;
	textcolor(WHITE, LIGHTBLUE);
	makeBox(moneyWidth, moneyHeight, mx, my);//1000�� ���
	gotoxy(mx + 4, my + 1);
	printf("%4d", 1000);//1000�� ���
	textcolor(LIGHTGRAY, DARKGRAY);
	makeBox(moneyWidth, moneyHeight, mx, my += 4);//500�� ���
	gotoxy(mx + 4, my + 1);
	printf("%4d", 500);//500�� ���
	textcolor(LIGHTGRAY, DARKGRAY);
	makeBox(moneyWidth, moneyHeight, mx, my += 4);//100�� ���
	gotoxy(mx + 4, my + 1);
	printf("%4d", 100);//100�� ���
	textcolor(LIGHTGRAY, BLACK);

	lp->curp = lp->headp->next;

	while (lp->curp != lp->tailp)
	{
		textcolor(WHITE, MAGENTA);
		makeBox(boxWidth, boxHeight, ((Beverage*)(lp->curp + 1))->x, ((Beverage*)(lp->curp + 1))->y);//����� �ڽ� �ϳ� ���
		textcolor(BLACK, LIGHTGRAY);
		beverageNamePrint(lp->curp + 1, ((Beverage*)(lp->curp + 1))->x + 5, ((Beverage*)(lp->curp + 1))->y + 3);//���� �̸� ���
		textcolor(BLACK, ((Beverage*)(lp->curp + 1))->cancolor);
		makeBox(beverageWidth, beverageHeight, ((Beverage*)(lp->curp + 1))->x + 2, ((Beverage*)(lp->curp + 1))->y + 2);//����� ���� ���
		textcolor(BLACK, DARKGRAY);
		makeBox(buttonWidth, buttonHeight, ((Beverage*)(lp->curp + 1))->x + 2, ((Beverage*)(lp->curp + 1))->y + 5);//����� ��ư ���
		gotoxy(((Beverage*)(lp->curp + 1))->x + 4, ((Beverage*)(lp->curp + 1))->y + 6);
		beveragePricePrint(lp->curp + 1);//���� ���� ���

		lp->curp = lp->curp->next;
	}

	textcolor(YELLOW, BROWN);
	makeBox(40, 4, 14, 29);//����� �����°�
	textcolor(LIGHTCYAN, CYAN);
	makeBox(12, 2, 62, 21);//�������Ա� ��ġ
	gotoxy(64, 22);//�������Ա� �۾� ����� ��ġ
	printf("�������Ա�");
	textcolor(LIGHTGRAY, DARKGRAY);
	makeBox(6, 3, 51, 21);//�������� �׵θ�
	gotoxy(54, 22);
	printf("��");
	gotoxy(54, 23);
	printf("��");//��������
	textcolor(LIGHTGRAY, BLACK);
	makeBox(6, 2, 68, 25);//���� �ݾ� ��� ��ġ
	textcolor(LIGHTRED, RED);
	makeBox(4, 2, 62, 25);//��� ��ư ��ġ
	gotoxy(63, 26);
	printf("���");
	textcolor(LIGHTMAGENTA, MAGENTA);
	makeBox(12, 4, 62, 29);//�Ž����� �����°� ��ġ
	textcolor(LIGHTGRAY, BLACK);
	return;
}

void canPrint(Linkedlist *lp)
{
	int beverageWidth = 2, beverageHeight = 3, i, y = 0;
	while (y<3)
	{
		textcolor(BLACK, ((Beverage*)(lp->curp + 1))->cancolor);
		makeBox(6, 1, 31, 29 + y);//����� ���� ���
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
	makeBox(6, 1, 31, 32);//����� ���� ���
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
		makeBox(12, y--, 62, 23);//���� �� ��ġ
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
			printf("0   õ");
		}
		if (ly > 23)
		{
			gotoxy(66, ly--);
			printf("0   ��");
		}
		textcolor(LIGHTCYAN, CYAN);
		makeBox(12, 2, 62, 21);//�������Ա� ��ġ
		gotoxy(64, 22);//�������Ա� �۾� ����� ��ġ
		printf("�������Ա�");
		Sleep(150);
		textcolor(LIGHTMAGENTA, LIGHTMAGENTA);
		makeBox(12, 4, 62, 24);
		textcolor(LIGHTGRAY, BLACK);
		makeBox(6, 2, 68, 25);//���� �ݾ� ��� ��ġ
		gotoxy(70, 26);
		if (totalM < 9000)
		{
			printf("%d", totalM - 1000);//���� �ݾ��� ����Ѵ�
		}
		else
		{
			printf("%d", totalM);//���� �ݾ��� ����Ѵ�
		}
		textcolor(LIGHTRED, RED);
		makeBox(4, 2, 62, 25);//��� ��ư ��ġ
		gotoxy(63, 26);
		printf("���");
	}

	textcolor(LIGHTGRAY, BLACK);
	gotoxy(70, 26);
	printf("%d", totalM);//���� �ݾ��� ����Ѵ�
	return;
}

void giveMoneyPrint()
{
	int y = 0, ly = 22;
	while (y != 6)
	{
		textcolor(WHITE, LIGHTBLUE);
		makeBox(12, y++, 62, 23);//���� �� ��ġ
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
			printf("0   õ");
		}
		if (ly > 23)
		{
			gotoxy(66, ly);
			printf("0   ��");
		}
		ly++;
		textcolor(LIGHTCYAN, CYAN);
		makeBox(12, 2, 62, 21);//�������Ա� ��ġ
		gotoxy(64, 22);//�������Ա� �۾� ����� ��ġ
		printf("�������Ա�");
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
		makeBox(6, 3, 51, 21);//�������� �׵θ�
		gotoxy(54, 22);
		printf("��");
		gotoxy(54, 23);
		printf("��");//��������
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
	makeBox(6, 3, 51, 21);//�������� �׵θ�
	gotoxy(54, 22);
	printf("��");
	gotoxy(54, 23);
	printf("��");//��������
	textcolor(LIGHTGRAY, BLACK);
}
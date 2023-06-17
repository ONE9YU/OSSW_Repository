#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "title.h"

#define GBOARD_WIDTH 50
#define GBOARD_HEIGHT 30

#define ONE 49
#define TWO 50
#define THREE 51
#define FOUR 52
#define FIVE 53

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

int curPosX, curPosY;
int humanCurPosX, humanCurPosY;
int virusCurPosX, virusCurPosY;
int mode;
int next = 0;
int curTime;

typedef struct Virus {
	int x;
	int y;
}Virus;

Virus* virus;

void SetCurrentCursorPos(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//보드판 내부 지우기
void redrawGameBoard() {
	int x, y;
	for (y = 1; y < GBOARD_HEIGHT - 1; y++) {
		for (x = 2; x < GBOARD_WIDTH * 2 - 4; x++) {
			SetCurrentCursorPos(x, y);
			printf("  ");
		}
	}

	curPosX = GBOARD_WIDTH;
	curPosY = 0;
	SetCurrentCursorPos(GBOARD_WIDTH, 0);
}
//모드 선택 입력 받기
void modeKeyInput() {
	int key;
	while (1) {
		if (_kbhit() != 0) {
			key = _getch();
			switch (key) {
			case ONE:
				mode = 1;
				redrawGameBoard();
				next = 1;
				break;
			case TWO:
				mode = 2;
				redrawGameBoard();
				next = 1;
				break;
			case THREE:
				mode = 3;
				redrawGameBoard();
				next = 1;
				break;
			case FOUR:
				mode = 4;
				redrawGameBoard();
				next = 1;
				break;
			case FIVE:
				mode = 5;
				redrawGameBoard();
				next = 1;
				break;
			default:
				continue;
			}
		}
		if (next == 1)
			break;
	}
}
//모드 선택 버튼
void drawModeButton(int posX) {
	int x, y;
	int width = 14;
	int height = 20;

	for (y = 0; y <= 4; y++) {
		SetCurrentCursorPos(posX, height + y);
		if (y == 0)
			printf("┏");
		else if (y == 4)
			printf("┗");
		else
			printf("┃");
	}
	for (y = 0; y <= 4; y++) {
		SetCurrentCursorPos(width + posX, height + y);
		if (y == 0)
			printf("┓");
		else if (y == 4)
			printf("┛");
		else
			printf("┃");
	}
	for (x = posX + 2; x < width + posX; x++) {
		SetCurrentCursorPos(x, height);
		printf("━");
	}
	for (x = posX + 2; x < width + posX; x++) {
		SetCurrentCursorPos(x, height + 4);
		printf("━");
	}
}
//보드판 그리기
void drawGameBoard() {
	int x, y;
	for (y = 0; y < GBOARD_HEIGHT; y++) {
		SetCurrentCursorPos(0, y);
		if (y == 0)
			printf("┏");
		else if (y == GBOARD_HEIGHT - 1)
			printf("┗");
		else
			printf("┃");
	}
	for (y = 0; y < GBOARD_HEIGHT; y++) {
		SetCurrentCursorPos(GBOARD_WIDTH * 2 - 2, y);
		if (y == 0)
			printf("┓");
		else if (y == GBOARD_HEIGHT - 1)
			printf("┛");
		else
			printf("┃");
	}
	for (x = 2; x < GBOARD_WIDTH * 2 - 2; x++) {
		SetCurrentCursorPos(x, 0);
		printf("━");
	}
	for (x = 2; x < GBOARD_WIDTH * 2 - 2; x++) {
		SetCurrentCursorPos(x, GBOARD_HEIGHT - 1);
		printf("━");
	}

	curPosX = GBOARD_WIDTH;
	curPosY = 0;
	SetCurrentCursorPos(GBOARD_WIDTH, 0);
}
//"SELECT MODE" 출력
void printTitle2() {
	int x = 0, y = 4;
	//print select
	for (int k = 0; k < 6; k++) {
		for (int i = 0; i < 4; i++) {
			x = (k * 4) * 2 + i * 2 + 27;
			for (int j = 0; j < 5; j++) {
				SetCurrentCursorPos(x, y + j);
				if (title2[k][j][i] == 1)
					printf("■");
				else
					printf("  ");
			}
			printf("\n");
		}
		printf("\n");
	}
	//print mode
	y = 12;
	for (int k = 0; k < 6; k++) {
		for (int i = 0; i < 3; i++) {
			x = (k * 3) * 2 + i * 2 + 6 + 27;
			for (int j = 0; j < 5; j++) {
				SetCurrentCursorPos(x, y + j);
				if (title3[k][j][i] == 1)
					printf("■");
				else
					printf("  ");
			}
			printf("\n");
		}
		printf("\n");
	}
}
//"RIP COVID" 출력
void printTitle1() {
	int x = 0, y = 9;

	for (int k = 0; k < 10; k++) {
		for (int i = 0; i < 3; i++) {
			x = (k * 3) * 2 + i * 2 + 22;
			for (int j = 0; j < 5; j++) {
				SetCurrentCursorPos(x, y + j);
				if (title[k][j][i] == 1)
					printf("■");
				else
					printf("  ");
			}
			printf("\n");
		}
		printf("\n");
	}

	SetCurrentCursorPos(38, 20);
	printf("Press Any Key to Start");
}

void removeCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
//모드 선택
void selectMode() {
	int key;
	printTitle1();

	while (1) {
		if (_kbhit() != 0) {
			key = _getch();
			redrawGameBoard();
			printTitle2();
			break;
		}
	}

	//classic mode button
	drawModeButton(5);
	SetCurrentCursorPos(10, 21);
	printf("Classic");
	SetCurrentCursorPos(11, 23);
	printf("Mode");
	//item mode button
	drawModeButton(23);
	SetCurrentCursorPos(29, 21);
	printf("Item");
	SetCurrentCursorPos(29, 23);
	printf("Mode");
	// invisible mode button
	drawModeButton(41);
	SetCurrentCursorPos(45, 21);
	printf("Invisible");
	SetCurrentCursorPos(47, 23);
	printf("Mode");
	//hell mode button
	drawModeButton(59);
	SetCurrentCursorPos(65, 21);
	printf("Hell");
	SetCurrentCursorPos(65, 23);
	printf("Mode");
	//final mode button
	drawModeButton(78);
	SetCurrentCursorPos(84, 21);
	printf("Final");
	SetCurrentCursorPos(84, 23);
	printf("Mode");

	curPosX = GBOARD_WIDTH;
	curPosY = 0;
	SetCurrentCursorPos(GBOARD_WIDTH, 0);

	//모드 선택하는 입력 키 받기
	modeKeyInput();
}
//인간 생성
void createHuman() {

	humanCurPosX = 50;
	humanCurPosY = 15;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");
}
//바이러스 생성
void createVirus() {

	virus = (Virus*)malloc(100 * sizeof(Virus));

	srand((unsigned int)time(NULL));

	for (int i = 0; i < 100; i++) {
		virus[i].x = rand() % 97 + 1;
		virus[i].y = rand() % 28 + 1;
		SetCurrentCursorPos(virus[i].x, virus[i].y);
		printf("*");
	}
}
//충돌 검사
int DetectCollision(int posX, int posY) {

	if (posX == 1 || posX == GBOARD_WIDTH * 2 - 2 || posY == 0 || posY == GBOARD_HEIGHT - 1)
		return 0;

	return 1;
}

void ShiftRight(void) {

	if (!DetectCollision(humanCurPosX + 1, humanCurPosY))
		return;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf(" ");
	humanCurPosX += 1;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");
}

void ShiftLeft(void) {

	if (!DetectCollision(humanCurPosX - 1, humanCurPosY))
		return;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf(" ");
	humanCurPosX -= 1;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");
}

void ShiftUp(void) {

	if (!DetectCollision(humanCurPosX, humanCurPosY - 1))
		return;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf(" ");
	humanCurPosY -= 1;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");
}

void ShiftDown(void) {

	if (!DetectCollision(humanCurPosX, humanCurPosY + 1))
		return;

	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf(" ");
	humanCurPosY += 1;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");
}
//추적 바이러스
void trackingVirus() {

	for (int i = 0; i < 100; i++) {
		SetCurrentCursorPos(virus[i].x, virus[i].y);
		printf(" ");

		int x, y;
		x = virus[i].x - humanCurPosX;
		y = virus[i].y - humanCurPosY;

		if (x == 0 && y == 0)
			continue;
		else if (x == 0) {
			if (y > 0)
				virus[i].y--;
			else
				virus[i].y++;
		}
		else if (y == 0) {
			if (x > 0)
				virus[i].x--;
			else
				virus[i].x++;
		}
		else if (x > 0 && y > 0) {
			virus[i].x--;
			virus[i].y--;
		}
		else if (x > 0 && y < 0) {
			virus[i].x--;
			virus[i].y++;
		}
		else if (x < 0 && y > 0) {
			virus[i].x++;
			virus[i].y--;
		}
		else {
			virus[i].x++;
			virus[i].y++;
		}

		SetCurrentCursorPos(virus[i].x, virus[i].y);
		printf("*");
	}
}
//인간 이동
void moveHuman() {
	int key;

	for (int i = 0; i < 100; i++) {
		if (_kbhit() != 0) {
			key = _getch();
			switch (key) {
			case LEFT:
				ShiftLeft();
				break;
			case RIGHT:
				ShiftRight();
				break;
			case UP:
				ShiftUp();
				break;
			case DOWN:
				ShiftDown();
				break;
			}
		}
		Sleep(10);

	}
	trackingVirus();
}

int main() {
	//system("mode con:cols=100 lines=30");   // cols: 가로, lines: 세로
	removeCursor();
	drawGameBoard();
	selectMode();

	createHuman();
	createVirus();
	while (1) {
		moveHuman();
	}
	getchar();
	return 0;
}
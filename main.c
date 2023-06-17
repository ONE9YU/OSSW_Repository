#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "title.h"
#include <math.h>

#define GBOARD_WIDTH 100
#define GBOARD_HEIGHT 30

#define COL				GetStdHandle(STD_OUTPUT_HANDLE)
#define BLACK			SetConsoleTextAttribute(COL, 0x0000);
#define DARK_RED		SetConsoleTextAttribute(COL, 0x0004);
#define WHITE			SetConsoleTextAttribute(COL, 0x0007);
#define RED				SetConsoleTextAttribute(COL, 0x000c);
#define GREEN			SetConsoleTextAttribute(COL, 0x0002);
#define BLUE_GREEN		SetConsoleTextAttribute(COL, 0x0003);
#define LIGHT_WHITE		SetConsoleTextAttribute(COL, 0x000f);
#define YELLOW			SetConsoleTextAttribute(COL, 0x000e);
#define DARK_YELLOW		SetConsoleTextAttribute(COL, 0x0006);

#define ONE 49
#define TWO 50
#define THREE 51
#define FOUR 52
#define FIVE 53

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

clock_t start_time;
clock_t end_time;

int curPosX, curPosY;
int humanCurPosX = 50, humanCurPosY = 15;
int virusCurPosX, virusCurPosY;
int mode;
int next = 0;
int curTime;

int v_num = 0;
int vertical_num = 0;

typedef struct Virus {
	int x;
	int y;
}Virus;

typedef struct VirusOneby {
	int x;
	int y;
}VirusOneby;

typedef struct VirusVertical {
	int x;
	int y;
	int visible;
}VirusVertical;

typedef struct VirusCircle {
	int x;
	int y;
}VirusCircle;

typedef struct VirusSquare {
	int x;
	int y;
}VirusSquare;

Virus* virus;
VirusOneby virusOneby[100];
VirusVertical virusVertical[GBOARD_HEIGHT];
VirusCircle virusCircle[100];
VirusSquare virusSquare[200];

struct game_util {
	int score;
	int life;
	int* heart;
};

struct game_util game_util;

void SetCurrentCursorPos(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//사각형 그리기
void drawRect(int posX, int posY, int width, int height) {

	int x, y;
	for (y = 0; y < height; y++) {
		SetCurrentCursorPos(posX, posY + y);
		if (y == 0)
			printf("┏");
		else if (y == height - 1)
			printf("┗");
		else
			printf("┃");
	}
	for (y = 0; y < height; y++) {
		SetCurrentCursorPos(posX + width - 2, posY + y);
		if (y == 0)
			printf("┓");
		else if (y == height - 1)
			printf("┛");
		else
			printf("┃");
	}
	for (x = 2; x < width - 2; x++) {
		SetCurrentCursorPos(posX + x, posY);
		printf("━");
	}
	for (x = 2; x < width - 2; x++) {
		SetCurrentCursorPos(posX + x, posY + height - 1);
		printf("━");
	}
}
//보드판 내부 지우기
void redrawGameBoard() {
	int x, y;
	for (y = 1; y < GBOARD_HEIGHT - 1; y++) {
		for (x = 2; x < GBOARD_WIDTH - 4; x++) {
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
//"SELECT MODE" 출력
void printTitle2() {
	int x = 0, y = 4;
	YELLOW
		//print select
		for (int k = 0; k < 6; k++) {
			for (int i = 0; i < 4; i++) {
				x = (k * 4) * 2 + i * 2 + 27;
				for (int j = 0; j < 5; j++) {
					SetCurrentCursorPos(x, y + j);
					if (title2[k][j][i] == 1) {
						printf("■");
					}
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

void printGameOver() {
	int x = 0, y = 5;
	for (int k = 0; k < 8; k++) {
		for (int i = 0; i < 5; i++) {
			if (k < 4)
				x = (k * 5) * 2 + i * 2 + 22;
			else {
				x = ((k - 4) * 5) * 2 + i * 2 + 23;
				y = 11;
			}

			for (int j = 0; j < 5; j++) {
				SetCurrentCursorPos(x, y + j);

				if (gameOver[k][j][i] == 1)
					printf("■");
				else
					printf("  ");
			}
			printf("\n");
		}
		printf("\n");
	}
}

void GameOver() {
	DARK_RED
		drawRect(0, 0, GBOARD_WIDTH, GBOARD_HEIGHT);
	redrawGameBoard();
	printGameOver();
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

	drawRect(0, 0, GBOARD_WIDTH, GBOARD_HEIGHT);
	printTitle1();

	while (1) {
		if (_kbhit() != 0) {
			key = _getch();
			redrawGameBoard();
			printTitle2();
			break;
		}
	}

	SetCurrentCursorPos(38, 19);
	printf("Press The Number Key...");

	//classic mode button
	drawRect(5, 22, 16, 5);
	SetCurrentCursorPos(9, 23);
	printf("1.Classic");
	SetCurrentCursorPos(11, 25);
	printf("Mode");
	//item mode button
	drawRect(23, 22, 16, 5);
	SetCurrentCursorPos(28, 23);
	printf("2.Item");
	SetCurrentCursorPos(29, 25);
	printf("Mode");
	// invisible mode button
	drawRect(41, 22, 16, 5);
	SetCurrentCursorPos(44, 23);
	printf("3.Invisible");
	SetCurrentCursorPos(47, 25);
	printf("Mode");
	//hell mode button
	drawRect(59, 22, 16, 5);
	SetCurrentCursorPos(64, 23);
	printf("4.Hell");
	SetCurrentCursorPos(65, 25);
	printf("Mode");
	//final mode button
	drawRect(78, 22, 16, 5);
	SetCurrentCursorPos(83, 23);
	printf("5.Final");
	SetCurrentCursorPos(84, 25);
	printf("Mode");

	curPosX = GBOARD_WIDTH;
	curPosY = 0;
	SetCurrentCursorPos(GBOARD_WIDTH, 0);

	//모드 선택하는 입력 키 받기
	modeKeyInput();
}
//목숨 업데이트
void updateLife() {

	SetCurrentCursorPos(104, 5);
	for (int i = 1; i <= 5; i++) {
		if (i <= game_util.life)
			RED
		else
			WHITE
			printf(" ♥ ");
	}
	WHITE
}
//목숨 생성
void createLife() {

	drawRect(101, 4, 27, 3);
	game_util.life = 5;
	game_util.heart = (int*)calloc(5, sizeof(int));

	updateLife();
}
//시간 업데이트
void updateTime() {
	SetCurrentCursorPos(110, 1);
	int min = (int)(end_time - start_time) / CLOCKS_PER_SEC / 60;
	int sec = (int)(end_time - start_time) / CLOCKS_PER_SEC % 60;

	if (min < 10 && sec < 10)
		printf("0%d  :  0%d", min, sec);

	else if (min < 10 && sec >= 10)
		printf("0%d  :  %d", min, sec);

	else if (min >= 10 && sec < 10)
		printf("%d  :  0%d", min, sec);

	else
		printf("%d  :  %d", min, sec);
}
//시간 생성
void createTime() {
	drawRect(101, 0, 27, 3);
}
//인간 생성
void createHuman() {

	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");
}
//바이러스 생성
void createVirus() {

	RED
		virus = (Virus*)malloc(5 * sizeof(Virus));

	srand((unsigned int)time(NULL));

	for (int i = 0; i < 5; i++) {
		virus[i].x = rand() % 97 + 1;
		virus[i].y = rand() % 28 + 1;
		SetCurrentCursorPos(virus[i].x, virus[i].y);
		printf("*");
	}
	WHITE
}

void createVirusOneby() {

	RED
		srand((unsigned int)time(NULL));

	virusOneby[v_num].x = rand() % 97 + 1;
	virusOneby[v_num].y = rand() % 28 + 1;

	SetCurrentCursorPos(virusOneby[v_num].x, virusOneby[v_num].y);
	printf("*");

	v_num++;
	WHITE
}

void createVirusVertical() {
	RED
		int r[4];
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 4; i++)
		r[i] = rand() % 30;

	for (int i = 0; i < GBOARD_HEIGHT - 2; i++) {
		int flag = 0;
		for (int j = 0; j < 4; j++) {
			if (r[j] == i) {
				virusVertical[i].visible = 0;
				virusVertical[i].x = -1;
				virusVertical[i].y = -1;
				flag = 1;
				break;
			}
		}
		if (flag == 1)
			continue;

		virusVertical[i].x = 2;
		virusVertical[i].y = 1 + i;

		SetCurrentCursorPos(virusVertical[i].x, virusVertical[i].y);
		printf("*");
		virusVertical[i].visible = 1;
	}
	WHITE
}

void createVirusSquare() {

	int i, k = 0;

	for (i = 0; i < 18; i++) {
		virusSquare[k].x = humanCurPosX + i;
		virusSquare[k].y = humanCurPosY - 10;
		k++;

	}

	for (i = 0; i < 18; i++) {
		virusSquare[k].x = humanCurPosX - i;
		virusSquare[k].y = humanCurPosY - 10;
		k++;

	}

	for (i = 0; i < 18; i++) {
		virusSquare[k].x = humanCurPosX + i;
		virusSquare[k].y = humanCurPosY + 10;
		k++;

	}

	for (i = 0; i < 18; i++) {
		virusSquare[k].x = humanCurPosX - i;
		virusSquare[k].y = humanCurPosY + 10;
		k++;

	}

	for (i = 0; i < 10; i++) {
		virusSquare[k].x = humanCurPosX + 18;
		virusSquare[k].y = humanCurPosY + i;
		k++;

	}

	for (i = 0; i < 10; i++) {
		virusSquare[k].x = humanCurPosX - 18;
		virusSquare[k].y = humanCurPosY + i;
		k++;

	}

	for (i = 0; i < 10; i++) {
		virusSquare[k].x = humanCurPosX + 18;
		virusSquare[k].y = humanCurPosY - i;
		k++;

	}

	for (i = 0; i < 10; i++) {
		virusSquare[k].x = humanCurPosX - 18;
		virusSquare[k].y = humanCurPosY - i;
		k++;

	}

	for (int i = 0; i < 112; i++) {
		SetCurrentCursorPos(virusSquare[i].x, virusSquare[i].y);
		printf("*");
	}
}

//바이러스 충돌 검사
int DetectCollisionV() {
	int i, j;

	for (i = 0; i < 10; i++) {
		if (virus[i].x == humanCurPosX && virus[i].y == humanCurPosY) {
			return 2;
		}
	}
	for (i = 0; i < v_num; i++) {
		if (virusOneby[i].x == humanCurPosX && virusOneby[i].y == humanCurPosY) {
			return 2;
		}
	}

	for (i = 0; i < GBOARD_HEIGHT - 2; i++) {
		if (virusVertical[i].x == humanCurPosX && virusVertical[i].y == humanCurPosY) {
			return 2;
		}
	}
	return 1;
}

//충돌 검사
int DetectCollision(int posX, int posY) {

	if (posX == 1 || posX + 1 > GBOARD_WIDTH - 3 || posY == 0 || posY == GBOARD_HEIGHT - 1)
		return 0;

	return 1;
}

void ShiftRight(void) {

	if (!DetectCollision(humanCurPosX + 1, humanCurPosY))
		return;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf(" ");
	humanCurPosX += 2;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");

}

void ShiftLeft(void) {

	if (!DetectCollision(humanCurPosX - 1, humanCurPosY))
		return;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf(" ");
	humanCurPosX -= 2;
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

	for (int i = 0; i < 5; i++) {
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

		RED
			SetCurrentCursorPos(virus[i].x, virus[i].y);
		printf("*");
	}
	WHITE
}

void trackingVirusOneby() {

	for (int i = 0; i < v_num; i++) {
		SetCurrentCursorPos(virusOneby[i].x, virusOneby[i].y);
		printf(" ");

		int x, y;
		x = virusOneby[i].x - humanCurPosX;
		y = virusOneby[i].y - humanCurPosY;

		if (x == 0 && y == 0)
			continue;
		else if (x == 0) {
			if (y > 0)
				virusOneby[i].y--;
			else
				virusOneby[i].y++;
		}
		else if (y == 0) {
			if (x > 0)
				virusOneby[i].x--;
			else
				virusOneby[i].x++;
		}
		else if (x > 0 && y > 0) {
			virusOneby[i].x--;
			virusOneby[i].y--;
		}
		else if (x > 0 && y < 0) {
			virusOneby[i].x--;
			virusOneby[i].y++;
		}
		else if (x < 0 && y > 0) {
			virusOneby[i].x++;
			virusOneby[i].y--;
		}
		else {
			virusOneby[i].x++;
			virusOneby[i].y++;
		}

		RED
			SetCurrentCursorPos(virusOneby[i].x, virusOneby[i].y);
		printf("*");
	}
	vertical_num++;
	WHITE
}

void trackingVirusVertical() {

	if (virusVertical[0].x + 4 > GBOARD_WIDTH) {
		for (int i = 0; i < GBOARD_HEIGHT - 2; i++) {
			SetCurrentCursorPos(virusVertical[i].x, virusVertical[i].y);
			printf(" ");
		}
		return;
	}

	for (int i = 0; i < GBOARD_HEIGHT - 2; i++) {
		if (virusVertical[i].visible == 1) {
			SetCurrentCursorPos(virusVertical[i].x, virusVertical[i].y);
			printf(" ");

			virusVertical[i].x++;

			RED
				SetCurrentCursorPos(virusVertical[i].x, virusVertical[i].y);
			printf("*");
		}
	}
	WHITE
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
	}
}

int main() {
	int i, j, num_cnt = 0;
	int check = 0;
	int vertical_cnt = 0;
	int circle_cnt = 0;

	system("mode con:cols=130 lines=30");   // cols: 가로, lines: 세로
	removeCursor();
	selectMode();
	WHITE
		start_time = clock();
	createTime();
	createLife();

	createHuman();
	createVirus();

	while (1) {
		int i = 1;

		if (_kbhit())
			moveHuman();

		Sleep(200);

		if (_kbhit())
			moveHuman();

		if (i % 100 == 0) {
			num_cnt++;
		}

		for (j = 0; j <= num_cnt; j++)
		{
			createVirusOneby();
		}

		trackingVirus();
		trackingVirusOneby();

		check = DetectCollisionV();
		if (check == 2) {
			game_util.life = --game_util.life;
			updateLife();
			SetCurrentCursorPos(humanCurPosX, humanCurPosY);
			RED printf("∩\a");

			if (game_util.life == 0) {
				GameOver();
				break;
			}
			Sleep(500);
			updateTime();
			Sleep(500);
		}

		if (check == 2) {
			WHITE
				SetCurrentCursorPos(humanCurPosX, humanCurPosY);
			printf("  ");
			createHuman();
			check = 0;
		}

		if (vertical_num == 10) {
			createVirusVertical();
			//createVirusCircle();
			//createVirusSquare();
			vertical_cnt++;
		}

		if (vertical_cnt >= 1) {
			trackingVirusVertical();
		}

		Sleep(100);
		i++;
		end_time = clock();
		updateTime();
	}

	getchar();
	return 0;
}
#include "MyHeader.h"
#include "title.h"

// 사각형 그리기
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

// 보드판 내부 지우기
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

// "SELECT MODE" 출력
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

// "RIP COVID" 출력
void printTitle() {
	int key;
	int x = 0, y = 9;

	drawRect(0, 0, GBOARD_WIDTH, GBOARD_HEIGHT);

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
	while (1) {
		if (_kbhit() != 0) {
			key = _getch();
			redrawGameBoard();
			break;
		}
	}
}


void printGameOver() {
	int x = 0, y = 7;
	for (int k = 0; k < 8; k++) {
		for (int i = 0; i < 5; i++) {
			if (k < 4)
				x = (k * 5) * 2 + i * 2 + 30;
			else {
				x = ((k - 4) * 5) * 2 + i * 2 + 31;
				y = 17;
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


// 아이템 설명판
void drawItemBoard() {
	drawRect(100, 12, 29, 18);

	SetCurrentCursorPos(111, 13);
	printf("I T E M");

	SetCurrentCursorPos(104, 15);
	printf("C  :  Stop 5 seconds");

	SetCurrentCursorPos(104, 18);
	printf("P  :  Phoenix 5 seconds");

	SetCurrentCursorPos(104, 21);
	printf("L  :  ");
	RED printf("♥");
	WHITE printf(" x 1");

	SetCurrentCursorPos(104, 24);
	printf("S  :  Virus attack");

	SetCurrentCursorPos(104, 27);
	printf("X  :  Bomb");
}
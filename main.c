#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define WIDTH 100
#define HEIGHT 30
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

void SetCurrentCursorPos(int x, int y);
void RemoveCursor();
void CreateHuman();
void CreateVirus();
void HumanMove();
void TrackHuman();
void ShiftRight();
void ShiftLeft();
void ShiftUp();
void ShiftDown();

int humanPosX = 0;
int humanPosY = 0;
int virusPosX = 0;
int virusPosY = 0;
int collision = 0; // �浹 ���Ͼ�� 0
int speed = 10;

int main() {
	//SetConsoleTitle("Rip Covid");	// �ܼ�â ����
	system("mode con:cols=100 lines=30");	// cols: ����, lines: ����
	//system("color 42");	// �ܼ�â ����
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);	// �ܼ�â ��Ʈ ����
	//DrawGameBoard();

	RemoveCursor();
	CreateHuman();
	Sleep(1000);
	CreateVirus();

	while (!collision) {
		HumanMove();
	}

	if (collision) {
		SetCurrentCursorPos(50, 0);
		printf("Game Over");
	}

	getchar();
	return 0;
}

void SetCurrentCursorPos(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void RemoveCursor(void) {
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void CreateHuman() {
	humanPosX = WIDTH / 2;
	humanPosY = HEIGHT / 2;

	SetCurrentCursorPos(humanPosX, humanPosY);
	printf("��");
}

void CreateVirus() {

	srand((unsigned int)time(NULL));

	virusPosX = (rand() % (WIDTH / 2)) * 2;
	virusPosY = rand() % HEIGHT;

	SetCurrentCursorPos(virusPosX, virusPosY);
	printf("��");

}

void HumanMove() {
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
		Sleep(speed);

	}
	TrackHuman();
}

void TrackHuman() {


	Sleep(300);
	SetCurrentCursorPos(virusPosX, virusPosY);
	printf("  ");

	// ���̷��� �ΰ��������� x��ǥ �̵�
	if (humanPosX > virusPosX)
		virusPosX += 2;
	else if (humanPosX < virusPosX)
		virusPosX -= 2;

	// ���̷��� �ΰ��������� y��ǥ �̵�
	if (humanPosY > virusPosY)
		virusPosY += 1;
	else if (humanPosY < virusPosY)
		virusPosY -= 1;

	if (humanPosX == virusPosX && humanPosY == virusPosY) {
		collision = 1;
		return;
	}

	SetCurrentCursorPos(virusPosX, virusPosY);
	printf("��");

}

void ShiftRight(void) {
	SetCurrentCursorPos(humanPosX, humanPosY);
	printf("  ");
	humanPosX += 2;
	SetCurrentCursorPos(humanPosX, humanPosY);
	printf("��");
}

void ShiftLeft(void) {
	SetCurrentCursorPos(humanPosX, humanPosY);
	printf("  ");
	humanPosX -= 2;
	SetCurrentCursorPos(humanPosX, humanPosY);
	printf("��");
}

void ShiftUp(void) {
	SetCurrentCursorPos(humanPosX, humanPosY);
	printf("  ");
	humanPosY -= 1;
	SetCurrentCursorPos(humanPosX, humanPosY);
	printf("��");
}

void ShiftDown(void) {
	SetCurrentCursorPos(humanPosX, humanPosY);
	printf("  ");
	humanPosY += 1;
	SetCurrentCursorPos(humanPosX, humanPosY);
	printf("��");
}
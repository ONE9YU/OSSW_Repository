#include "MyHeader.h"

// 모드 선택 입력 받기
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

// 모드 선택
void selectMode() {
	int key;

	drawRect(0, 0, GBOARD_WIDTH, GBOARD_HEIGHT);
	printTitle();

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
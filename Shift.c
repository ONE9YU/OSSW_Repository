#include "MyHeader.h"

// 오른쪽
void ShiftRight(void) {
	if (spear_xy.get_check == 1) {
		if (!DetectCollision(humanCurPosX + 4, humanCurPosY))
			return;
	}
	else {
		if (!DetectCollision(humanCurPosX + 1, humanCurPosY))
			return;
	}
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf(" ");
	humanCurPosX += 1;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");

	if (spear_xy.get_check == 1)
		spear_wear();
}

// 왼쪽
void ShiftLeft(void) {
	if (spear_xy.get_check == 1) {
		if (!DetectCollision(humanCurPosX - 4, humanCurPosY))
			return;
	}
	else {
		if (!DetectCollision(humanCurPosX - 1, humanCurPosY))
			return;
	}
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf(" ");
	humanCurPosX -= 1;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");

	if (spear_xy.get_check == 1)
		spear_wear();
}

// 위쪽
void ShiftUp(void) {
	if (spear_xy.get_check == 1) {
		if (!DetectCollision(humanCurPosX, humanCurPosY - 2))
			return;
	}
	else {
		if (!DetectCollision(humanCurPosX, humanCurPosY - 1))
			return;
	}

	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf(" ");
	humanCurPosY -= 1;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");

	if (spear_xy.get_check == 1)
		spear_wear();
}

// 아래쪽
void ShiftDown(void) {
	if (spear_xy.get_check == 1) {
		if (!DetectCollision(humanCurPosX, humanCurPosY + 2))
			return;
	}
	else {
		if (!DetectCollision(humanCurPosX, humanCurPosY + 1))
			return;
	}

	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf(" ");
	humanCurPosY += 1;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");

	if (spear_xy.get_check == 1)
		spear_wear();
}
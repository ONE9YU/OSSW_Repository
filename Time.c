#include "MyHeader.h"

// 시간 업데이트
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

// 시간 생성
void createTime() {
	drawRect(101, 0, 27, 3);
}
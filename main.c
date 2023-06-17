#include "MyHeader.h"

// 인간 위치
int humanCurPosX = 50, humanCurPosY = 15;

// 바이러스 위치
int virusCurPosX, virusCurPosY;

// 모드
int mode;

// 시간
clock_t start_time;
clock_t end_time;

// 시계 아이템
int clockCurPosX = 0, clockCurPosY = 0;
int clock_item_time;
int clock_item_time_plus_5sec;
int clock_item_flag = 0;

// 추적 바이러스 플래그
int trackingVirus_flag = 0;
int trackingVirusOneby_flag = 0;
int trackingVirusVertical_flag = 0;

// 무적 아이템
int phoenixCurPosX = 0, phoenixCurPosY = 0;
int phoenix_item_time;
int phoenix_item_time_plus_5sec;
int phoenix_item_flag = 0;

// 생명 아이템
int lifeCurPosX = 0, lifeCurPosY = 0;
int life_item_flag = 0;

// 창 아이템
int spear_item_time;
int spear_item_time_plus_5sec;
int spear_clock_flag = 0;

// 게임 오버 플래그
int game_over_flag = 0;

// 아이템 먹은 횟수
int cnt_eat_item = 0;

// 주석 필요
int preX = 999, preY = 999;
int curPosX, curPosY;
int next = 0;
int curTime;
int v_num = 0;
int vertical_num = 0;
int boom_flag = 0;
int spear_flag = 0;
int killed_v = 0;

int main() {
	game_util.score = 0;
	boom_xy.get_check = 0;
	spear_xy.get_check = 0;

	int i, j, num_cnt = 0;
	int check = 0;
	int vertical_cnt = 0;
	int circle_cnt = 0;

	system("mode con:cols=130 lines=30");   // cols: 가로, lines: 세로
	removeCursor();
	printTitle();
	WHITE
		start_time = clock();
	createTime();
	createLife();
	drawItemBoard();
	createScore();

	createHuman();
	createVirus();

	while (1) {
		int i = 1;

		if (_kbhit())
			moveHuman();

		Sleep(200);

		if (_kbhit())
			moveHuman();

		if (i % 100 == 0)
			num_cnt++;

		for (j = 0; j <= num_cnt; j++)
			createVirusOneby();

		trackingVirus();
		trackingVirusOneby();

		check = DetectCollisionV();
		if (check == 2) {
			if (phoenix_item_flag == 0 || phoenix_item_flag == 1) {
				game_util.life = --game_util.life;
				updateLife();
				SetCurrentCursorPos(humanCurPosX, humanCurPosY);
				RED printf("∩\a");
			}

			if (game_util.life == 0) {
				game_over_flag = 1;
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
			//createVirusHorizontal();
			createVirusVertical();
			//createVirusCircle();
			//createVirusSquare();
			vertical_cnt++;
		}

		if (vertical_cnt >= 1) {
			trackingVirusVertical();
			//trackingVirusHorizontal();
		}

		Sleep(100);
		i++;
		end_time = clock();
		updateTime();

		// 아이템
		clock_item();
		phoenix_item();
		life_item();
		boom_item();
		spear_item();

		// 점수 업데이트
		createScore();

		if (spear_xy.get_check == 1) {
			spear_wear();
		}
	}

	getchar();

	return 0;
}
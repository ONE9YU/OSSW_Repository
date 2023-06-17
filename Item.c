#include "MyHeader.h"

// 시계 아이템
void clock_item() {
	ClockItem clock;
	int my_number = 1;
	int random_number;
	int f = 0;
	int t;

	srand((unsigned int)time(NULL));
	random_number = rand() % 3;
	clock.pos_x = rand() % 97 + 1;
	clock.pos_y = rand() % 28 + 1;

	// "C" 아이템 생성
	if (my_number == random_number && clock_item_flag == 0) {
		clockCurPosX = clock.pos_x;
		clockCurPosY = clock.pos_y;
		SetCurrentCursorPos(clockCurPosX, clockCurPosY);
		printf("C");
		clock_item_flag = 1;
	}

	// 인간이 "C" 아이템 먹으면 5초간 일시정지
	if (humanCurPosX == clockCurPosX && humanCurPosY == clockCurPosY) {
		clock_item_flag = 0;
		trackingVirus_flag = 1;
		trackingVirusOneby_flag = 1;
		trackingVirusVertical_flag = 1;
		cnt_eat_item++;
		createScore();

		if (f == 0) {
			t = (int)(end_time - start_time) / CLOCKS_PER_SEC % 60;
			clock_item_time = t;
			clock_item_time_plus_5sec = clock_item_time + 5;
			if (clock_item_time_plus_5sec >= 60)
				clock_item_time_plus_5sec %= 60;
			f = 1;
		}
	}

	// 5초가 지나면 바이러스 다시 움직임
	if (trackingVirus_flag == 1) {
		t = (int)(end_time - start_time) / CLOCKS_PER_SEC % 60;
		if (t == clock_item_time_plus_5sec) {
			trackingVirus_flag = 0;
			trackingVirusOneby_flag = 0;
			trackingVirusVertical_flag = 0;
			f = 0;
		}
	}
}

// 무적 아이템
void phoenix_item() {
	PhoenixItem phoenix;
	int my_number = 2;
	int random_number;
	int f = 0;
	int t;

	srand((unsigned int)time(NULL));
	random_number = rand() % 3;
	phoenix.pos_x = rand() % 97 + 1;
	phoenix.pos_y = rand() % 28 + 1;

	// "P" 아이템 생성
	if (my_number == random_number && phoenix_item_flag == 0) {
		phoenixCurPosX = phoenix.pos_x;
		phoenixCurPosY = phoenix.pos_y;
		SetCurrentCursorPos(phoenixCurPosX, phoenixCurPosY);
		printf("P");
		phoenix_item_flag = 1;
	}

	// 인간이 "P" 아이템 먹으면 5초간 무적 상태
	if (humanCurPosX == phoenixCurPosX && humanCurPosY == phoenixCurPosY) {
		phoenix_item_flag = 2; // 아이템 먹으면 flag = 2
		cnt_eat_item++;
		createScore();

		if (f == 0) {
			t = (int)(end_time - start_time) / CLOCKS_PER_SEC % 60;
			phoenix_item_time = t;
			phoenix_item_time_plus_5sec = phoenix_item_time + 5;
			if (phoenix_item_time_plus_5sec >= 60)
				phoenix_item_time_plus_5sec %= 60;
			f = 1;
		}
	}

	// 5초가 지나면 무적 상태 풀림
	if (phoenix_item_flag == 2) {
		t = (int)(end_time - start_time) / CLOCKS_PER_SEC % 60;
		if (t == phoenix_item_time_plus_5sec) {
			phoenix_item_flag = 0;
			f = 0;
		}
	}
}

// 생명 아이템
void life_item() {
	LifeItem life;
	int my_number = 0;
	int random_number;

	srand((unsigned int)time(NULL));
	random_number = rand() % 3;
	life.pos_x = rand() % 97 + 1;
	life.pos_y = rand() % 28 + 1;

	// "L" 아이템 생성
	if (my_number == random_number && life_item_flag == 0) {
		lifeCurPosX = life.pos_x;
		lifeCurPosY = life.pos_y;
		SetCurrentCursorPos(lifeCurPosX, lifeCurPosY);
		printf("L");
		life_item_flag = 1;
	}

	// "L"아이템을 먹으면 생명 + 1
	if (humanCurPosX == lifeCurPosX && humanCurPosY == lifeCurPosY)
	{
		life_item_flag = 0;
		cnt_eat_item++;
		createScore();

		if (game_util.life < 5)
			game_util.life += 1;
		updateLife();
	}
}

//spear 잔상 제거
void pre_remove() {
	int x, y, k;
	int i = 0, j = 0;

	x = preX - 2;
	y = preY - 1;

	for (k = 0; k < 9; k++) {
		spear_ready[k].x = x + i * 2;
		i++;
		spear_ready[k].y = y + j;

		if (i % 3 == 0) {
			j++;
			i = 0;
		}

	}


	SetCurrentCursorPos(spear_ready[1].x, spear_ready[1].y);
	printf("  ");
	SetCurrentCursorPos(spear_ready[3].x, spear_ready[3].y);
	printf("  ");
	SetCurrentCursorPos(spear_ready[5].x, spear_ready[5].y);
	printf("  ");
	SetCurrentCursorPos(spear_ready[7].x, spear_ready[7].y);
	printf("  ");
	SetCurrentCursorPos(spear_ready[4].x, spear_ready[4].y);
	printf(" ");

}

// 창 아이템 착용
void spear_wear() {

	int x, y, k;
	int i = 0, j = 0;
	int a, b, c, d;
	int t;


	if (spear_clock_flag == 0) {

		t = (int)(end_time - start_time) / CLOCKS_PER_SEC % 60;
		spear_item_time = t;
		spear_item_time_plus_5sec = spear_item_time + 5;
		if (spear_item_time_plus_5sec >= 60)
			spear_item_time_plus_5sec %= 60;
		spear_clock_flag = 1;
	}

	// 5초가 지나면 창 해제
	t = (int)(end_time - start_time) / CLOCKS_PER_SEC % 60;
	if (t == spear_item_time_plus_5sec) {

		SetCurrentCursorPos(humanCurPosX, humanCurPosY - 1);
		printf("  ");
		SetCurrentCursorPos(humanCurPosX, humanCurPosY + 1);
		printf("  ");
		SetCurrentCursorPos(humanCurPosX - 2, humanCurPosY);
		printf("  ");
		SetCurrentCursorPos(humanCurPosX + 2, humanCurPosY);
		printf("  ");

		spear_flag = 0; // 처음 창위치 랜덤한 자리나오게 하는 flag
		spear_xy.get_check = 0; // 창을 먹었는지 여부
		spear_clock_flag = 0;

		return;
	}




	x = humanCurPosX - 2;
	y = humanCurPosY - 1;

	pre_remove();

	for (k = 0; k < 9; k++) {
		spear_ready[k].x = x + i * 2;
		i++;
		spear_ready[k].y = y + j;

		if (i % 3 == 0) {
			j++;
			i = 0;
		}

	}


	SetCurrentCursorPos(spear_ready[0].x, spear_ready[0].y);
	printf(" ");
	SetCurrentCursorPos(spear_ready[2].x, spear_ready[2].y);
	printf(" ");
	SetCurrentCursorPos(spear_ready[6].x, spear_ready[6].y);
	printf(" ");
	SetCurrentCursorPos(spear_ready[8].x, spear_ready[8].y);
	printf(" ");

	SetCurrentCursorPos(spear_ready[1].x, spear_ready[1].y);
	printf("▲");
	SetCurrentCursorPos(spear_ready[3].x, spear_ready[3].y);
	printf("◀");
	SetCurrentCursorPos(spear_ready[5].x, spear_ready[5].y);
	printf("▶");
	SetCurrentCursorPos(spear_ready[7].x, spear_ready[7].y);
	printf("▼");
	SetCurrentCursorPos(spear_ready[4].x, spear_ready[4].y);
	printf("@");

	for (k = 0; k < 9; k++) {
		for (a = 0; a < 5; a++) {
			if (spear_ready[0].x <= virus[a].x && spear_ready[0].y <= virus[a].y &&
				spear_ready[2].x >= virus[a].x && spear_ready[2].y <= virus[a].y &&
				spear_ready[6].x <= virus[a].x && spear_ready[6].y >= virus[a].y &&
				spear_ready[8].x >= virus[a].x && spear_ready[8].y >= virus[a].y) {
				//SetCurrentCursorPos(virus[a].x, virus[a].y);
				//printf(" ");
				virus[a].x = 1000;
				virus[a].y = 1000;
				virus[a].killed_flag = 1;
				killed_v++;
				createScore();
			}
		}
		for (b = 0; b < v_num; b++) {
			if (spear_ready[0].x <= virusOneby[b].x && spear_ready[0].y <= virusOneby[b].y &&
				spear_ready[2].x >= virusOneby[b].x && spear_ready[2].y <= virusOneby[b].y &&
				spear_ready[6].x <= virusOneby[b].x && spear_ready[6].y >= virusOneby[b].y &&
				spear_ready[8].x >= virusOneby[b].x && spear_ready[8].y >= virusOneby[b].y) {
				//SetCurrentCursorPos(virusOneby[b].x, virusOneby[b].y);
				//printf(" ");
				virusOneby[b].x = 1000;
				virusOneby[b].y = 1000;
				virusOneby[b].killed_flag = 1;
				killed_v++;
				createScore();
			}
		}
		for (c = 0; c < 30; c++) {
			if (spear_ready[0].x <= virusVertical[c].x && spear_ready[0].y <= virusVertical[c].y &&
				spear_ready[2].x >= virusVertical[c].x && spear_ready[2].y <= virusVertical[c].y &&
				spear_ready[6].x <= virusVertical[c].x && spear_ready[6].y >= virusVertical[c].y &&
				spear_ready[8].x >= virusVertical[c].x && spear_ready[8].y >= virusVertical[c].y) {
				//SetCurrentCursorPos(virusVertical[c].x, virusVertical[c].y);
				//printf(" ");
				virusVertical[c].x = 1000;
				virusVertical[c].y = 1000;
				virusVertical[c].killed_flag = 1;
				killed_v++;
				createScore();
			}
		}
	}



	preX = humanCurPosX;
	preY = humanCurPosY;




}

//창 좌표
void spear_item() {
	if (spear_xy.get_check == 0) {



		if (spear_flag == 0) {

			srand((unsigned int)time(NULL));
			spear_xy.x = rand() % 80 + 10;
			spear_xy.y = rand() % 15 + 6;

			spear_flag = 1;
		}

		SetCurrentCursorPos(spear_xy.x, spear_xy.y);
		printf("S");

		if (spear_xy.x == humanCurPosX && spear_xy.y == humanCurPosY) {
			spear_xy.get_check = 1;

			spear_wear();

		}

	}
}

// 폭탄 폭발
void boom_shoot() {

	int x, y;
	int i = 1, j = 0;
	int k = 1;
	int a, b, c, d;

	x = boom_xy.x - 8;
	y = boom_xy.y - 2;

	for (k = 0; k < 36; k++) {


		boom_ready[k].x = x + i * 2;
		boom_ready[k].y = y + j;

		i++;

		if (i % 7 == 0) {
			j++;
			i = 1;
		}
	}


	for (k = 0; k < 36; k++) {

		SetCurrentCursorPos(boom_ready[k].x, boom_ready[k].y);
		printf("■");

	}
	Sleep(300);

	for (k = 0; k < 36; k++) {

		for (a = 0; a < 5; a++) {
			if (boom_ready[0].x <= virus[a].x && boom_ready[0].y <= virus[a].y &&
				boom_ready[5].x >= virus[a].x && boom_ready[5].y <= virus[a].y &&
				boom_ready[30].x <= virus[a].x && boom_ready[30].y >= virus[a].y &&
				boom_ready[35].x >= virus[a].x && boom_ready[35].y >= virus[a].y) {
				virus[a].x = 1000;
				virus[a].y = 1000;
				virus[a].killed_flag = 1;
				killed_v++;
				createScore();
			}
		}

		for (b = 0; b < v_num; b++) {
			if (boom_ready[0].x <= virusOneby[b].x && boom_ready[0].y <= virusOneby[b].y &&
				boom_ready[5].x >= virusOneby[b].x && boom_ready[5].y <= virusOneby[b].y &&
				boom_ready[30].x <= virusOneby[b].x && boom_ready[30].y >= virusOneby[b].y &&
				boom_ready[35].x >= virusOneby[b].x && boom_ready[35].y >= virusOneby[b].y) {
				virusOneby[b].x = 1000;
				virusOneby[b].y = 1000;
				virusOneby[b].killed_flag = 1;
				killed_v++;
				createScore();
			}
		}

		for (c = 0; c < 30; c++) {
			if (boom_ready[0].x <= virusVertical[c].x && boom_ready[0].y <= virusVertical[c].y &&
				boom_ready[5].x >= virusVertical[c].x && boom_ready[5].y <= virusVertical[c].y &&
				boom_ready[30].x <= virusVertical[c].x && boom_ready[30].y >= virusVertical[c].y &&
				boom_ready[35].x >= virusVertical[c].x && boom_ready[35].y >= virusVertical[c].y) {
				virusVertical[c].x = 1000;
				virusVertical[c].y = 1000;
				virusVertical[c].killed_flag = 1;
				killed_v++;
				createScore();
			}
		}

	}



	for (k = 0; k < 36; k++) {

		SetCurrentCursorPos(boom_ready[k].x, boom_ready[k].y);
		printf("  ");

	}

	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");

	Sleep(30);


	boom_xy.get_check = 0;
	boom_flag = 0;
}
//폭탄 좌표
void boom_item() {
	int x, i;

	if (boom_xy.get_check == 0) {



		if (boom_flag == 0) {
			srand((unsigned int)time(NULL));
			boom_xy.x = rand() % 70 + 15;
			boom_xy.y = rand() % 20 + 6;
			boom_flag = 1;

		}

		SetCurrentCursorPos(boom_xy.x, boom_xy.y);
		printf("X");


		if (boom_xy.x == humanCurPosX && boom_xy.y == humanCurPosY) {
			boom_xy.get_check = 1;
			SetCurrentCursorPos(boom_xy.x, boom_xy.y);
			printf(" ");

			boom_shoot();

		}

	}
}
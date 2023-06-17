#include "MyHeader.h"

// 格见 诀单捞飘
void updateLife() {

	SetCurrentCursorPos(104, 5);
	for (int i = 1; i <= 5; i++) {
		if (i <= game_util.life)
			RED
		else
			WHITE
			printf(" ⒕ ");
	}
	WHITE
}

// 格见 积己
void createLife() {

	drawRect(101, 4, 27, 3);
	game_util.life = 5;
	game_util.heart = (int*)calloc(5, sizeof(int));

	updateLife();
}
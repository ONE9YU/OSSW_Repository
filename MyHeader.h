#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include "data.h"

// 게임 가로, 세로 크기
#define GBOARD_WIDTH 100
#define GBOARD_HEIGHT 30

//  COLOR 설정
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

// MODE SELECT
#define ONE 49
#define TWO 50
#define THREE 51
#define FOUR 52
#define FIVE 53

// 방향키
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

typedef struct Virus {
	int x;
	int y;
	int killed_flag;
}Virus;

typedef struct VirusOneby {
	int x;
	int y;
	int killed_flag;
}VirusOneby;

typedef struct VirusVertical {
	int x;
	int y;
	int visible;
	int onoff;
	int killed_flag;
}VirusVertical;

typedef struct VirusCircle {
	int x;
	int y;
}VirusCircle;

typedef struct VirusSquare {
	int x;
	int y;
}VirusSquare;

typedef struct VirusHorizontal {
	int x;
	int y;
}VirusHorizontal;

typedef struct boom_xy {
	int x;
	int y;
	int get_check;

}Boom_xy;

typedef struct boom_ready {
	int x;
	int y;
}Boom_ready;

typedef struct spear_xy {
	int x;
	int y;
	int get_check;
}Spear_xy;

typedef struct spear_ready {
	int x;
	int y;
}Spear_ready;

typedef struct PreEraser {
	int x;
	int y;
}PreEraser;

typedef struct invisibleMap {
	int x;
	int y;
}InvisibleMap;

typedef struct visibleMap {
	int x;
	int y;
}VisibleMap;

struct game_util {
	int score;
	int life;
	int* heart;
};

typedef struct ClockItem {
	int pos_x;
	int pos_y;
}ClockItem;

typedef struct PhoenixItem {
	int pos_x;
	int pos_y;
}PhoenixItem;

typedef struct LifeItem {
	int pos_x;
	int pos_y;
}LifeItem;

Virus* virus;
VirusOneby virusOneby[10000];
VirusVertical virusVertical[GBOARD_HEIGHT];
VirusCircle virusCircle[100];
VirusSquare virusSquare[200];
VirusHorizontal virusHorizontal[GBOARD_WIDTH];

Boom_xy boom_xy;
Boom_ready boom_ready[100];

Spear_xy spear_xy;
Spear_ready spear_ready[9];
PreEraser preEraser[9];

InvisibleMap invisibleMap[3000];
VisibleMap visibleMap[100];

struct game_util game_util;
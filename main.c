#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#include "collision.h"
#include "const.h"
#include "fruit.h"
#include "game.h"
#include "map.h"
#include "queue.h"
#include "snake.h"

int main(void) {
	MapData map[22][22];
	system("color 7");
	hidecursor();
	int mode;
	int stage;
	int scoreArr[8] = { 0 };
	while (1) {
		system("mode con: cols=44 lines=30");
		if (Map_MenuDrawStart() == FALSE) break;
		
		system("cls");
		mode = Map_MenuDrawMode(scoreArr);
		system("cls");
		stage = Map_MenuDrawStage(mode, scoreArr);
		system("cls");
		Game_Start(map, stage, scoreArr, mode);
		system("pause");
	}
	return 0;
}

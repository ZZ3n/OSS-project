#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#include "collision.h"
#include "basic.h"
#include "fruit.h"
#include "game.h"
#include "map.h"
#include "queue.h"
#include "snake.h"

int main(void) 
{   
	//{ 22 = MAP_SIZE }
	MapData map[22][22];

	int scoreArr[8] = { 0 };
	int stage;
	int mode;
	int keyDown = getKeyDown();

	system("color 7");
	hidecursor();

	while (keyDown != 't')
	{
		system("mode con: cols=44 lines=30");

		if (Map_MenuDrawStart() == FALSE)
		{
			break;
		}

		system("cls");
		mode = Map_MenuDrawMode();

		system("cls");
		stage = Map_MenuDrawStage(mode, scoreArr);

		system("cls");
		Game_Start(map, stage, scoreArr, mode);
		system("pause");
	}
	return 0;
}

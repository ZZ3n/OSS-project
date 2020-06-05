#include <Windows.h>
#include "const.h"

void Game_PlayDrawTail(MapData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, 14);
	gotoxy(snake_x, snake_y);
	//print ○
	printf("\u25CB");
	map[snake_x][snake_y] = TAIL; // 맵에 꼬리의 위치를 저장함.
	SetConsoleTextAttribute(hand, 7);

}

void Game_PlayDrawHead(MapData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(snake_x, snake_y);
	SetConsoleTextAttribute(hand, 14);
	//print ●
	printf("\u25CF");
	SetConsoleTextAttribute(hand, 7);
	map[snake_x][snake_y] = HEAD;
}

void Game_PlayRemoveTail(MapData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y) {
	gotoxy(snake_x, snake_y);
	printf("  ");
	map[snake_x][snake_y] = EMPTY;
}

int Game_PlayPredictHead(int xy, int way) {
	if (way == UP || way == LEFT) {
		if (xy - 1 == -1) {
			xy = MAP_SIZE - 1;
		}
		else {
			--(xy);
		}
		return xy;
	}
	if (way == DOWN || way == RIGHT) {
		if (xy + 1 == MAP_SIZE) {
			xy = 0;
		}
		else {
			++xy;
		}
		return xy;
	}
	return FALSE;
}

int Game_PlayMoveSnake(MapData map[MAP_SIZE][MAP_SIZE], SnakePos * snake, int way) {
	Game_PlayRemoveTail(map, snake->x, snake->y);
	if (isColWithWall(map, snake, way) == TRUE) {
		gotoxy(1, 1);
		printf("> Hit : wall");
		return COLLISION;
	}
	if (isColWithTail(map, snake, way) == TRUE) {
		gotoxy(1, 1);
		printf("> Hit : tail");
		return COLLISION;
	}

	if (way == UP) {
		if (snake->y - 1 == -1) {
			snake->y = MAP_SIZE - 1;
		}
		else {
			--(snake->y);
		}
		Game_PlayDrawHead(map, snake->x, (snake->y));
		return UP;
	}
	if (way == DOWN) {
		if (snake->y + 1 == MAP_SIZE) {
			snake->y = 0;
		}
		else {
			++(snake->y);
		}
		Game_PlayDrawHead(map, snake->x, (snake->y));
		return DOWN;
	}
	if (way == LEFT) {
		if (snake->x - 1 == -1) {
			snake->x = MAP_SIZE - 1;
		}
		else {
			--(snake->x);
		}
		Game_PlayDrawHead(map, (snake->x), snake->y);
		return LEFT;
	}
	if (way == RIGHT) {
		if (snake->x + 1 == MAP_SIZE) {
			snake->x = 0;
		}
		else {
			++(snake->x);
		}
		Game_PlayDrawHead(map, snake->x, snake->y);
		return RIGHT;
	}
	return way;
}

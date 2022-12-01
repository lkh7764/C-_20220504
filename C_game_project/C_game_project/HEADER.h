#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

#pragma warning(disable: 4996)

#define ESC 27

void gotoxy(int x, int y);
void CursorView(char show);
void game_reset();
void printPlayerInfo(int fx, int Score, int hp);
void enemySet(int ballRate, int enemyRate, int stageMaxBall, int stageMaxEnemy, int* Score, int* bx, int* by);
void end(int end_score);
boolean playerEnter(int count, int ch, int* fx, int Score, int* bx, int* by);
boolean hp_check(int hp, int fx);
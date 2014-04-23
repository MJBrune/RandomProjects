#ifndef GAME_H
#define GAME_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#define COLS 40
#define ROWS 20
#define BUFFERLENGTH 256
#define DEAD 0
#define ALIVE 1
#define MAX 800
#pragma warning(disable: 4996)
#endif

void printGen(int (*currentGenPtr)[COLS]);
void getFirstGen(char fileName[BUFFERLENGTH], int currentGen[][COLS]);
int GetNeighbourCount(const int (*currentGenPtr)[COLS], int x, int y);
void getNextGen(int (*currentGenPtr)[COLS], int (*nextGenPtr)[COLS]);
void calculateNextGen(int (*currentGenPtr)[COLS], int (*nextGenPtr)[COLS]);
int getNeighbors(int i, int j, int (*currentGenPtr)[COLS]);
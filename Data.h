#pragma once
#ifndef _DATA_H_
#define _DATA_H_

#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>// _kbhit() va _getch()

using namespace std;

#define CONSOLE_WIDTH 1280
#define CONSOLE_HEIGHT 720
//Keyboard
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77
#define KEY_ENTER 13
#define SPACE 32
#define KEY_ESC 27
//Chess Board
#define BOARD_SIZE 13
#define LEFT 2
#define TOP 1
#define HORIZONTAL_DISTANCE 4
#define VERTICAL_DISTANCE 2


#define TOP_LEFT (char)218
#define TOP_RIGHT (char)191
#define BOTTOM_LEFT (char)192
#define BOTTOM_RIGHT (char)217
#define TOP_CROSS (char)194
#define BOTTOM_CROSS (char)193
#define	LEFT_CROSS (char)195
#define RIGHT_CROSS (char)180
#define CROSS (char)197
#define HORIZONTAL_LINE (char)196
#define VERTICAL_LINE (char)179


struct _BufferInfo {
	int col;
	int row;
};

struct _Point {
	int x;
	int y;
	int check;
};

struct _Menu {
	int items;
	int color;
	int vertical_Or_horizontal; // check x?p d?c hay ngang
};


#endif // !

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;
#define LOADING 119
#define WAITING 10
// DINH DANG DI CHUYEN
#pragma region KeyMove
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27
#define ENTER 13
#pragma region Size
// DINH DANG MAN HINH CONSOLE
#define CONSOLE_MAX_HEIGHT 70
#define CONSOLE_MAX_WIDTH 200
#define smallFontSizeW (short)GetSystemMetrics(SM_CXSCREEN)/CONSOLE_MAX_WIDTH - 3	 
#define smallFontSizeH (short)GetSystemMetrics(SM_CYSCREEN)/CONSOLE_MAX_HEIGHT 	- 3	 
#define CONSOLE_MENU_HEIGHT 23		 
#define CONSOLE_MENU_WIDTH	70	 
#define bigFontSizeW (short)GetSystemMetrics(SM_CXSCREEN)/CONSOLE_MENU_WIDTH  - 10		 
#define bigFontSizeH (short)GetSystemMetrics(SM_CYSCREEN)/CONSOLE_MENU_HEIGHT  - 10		 
#define WIDTH_OFFSET 20
#define HEIGHT_OFFSET 4
#define BOARD_LEFT_EDGE WIDTH_OFFSET		 
#define BOARD_RIGHT_EDGE (CONSOLE_MAX_WIDTH - WIDTH_OFFSET - 1)		 
#define BOARD_TOP_EDGE  HEIGHT_OFFSET	 
#define BOARD_BOTTOM_EDGE (CONSOLE_MAX_HEIGHT - HEIGHT_OFFSET - 1)
#define BOARD_GAME_TOP BOARD_TOP_EDGE
#define BOARD_GAME_BOTTOM (BOARD_BOTTOM_EDGE - 0)
#define BOARD_GAME_LEFT BOARD_LEFT_EDGE
#define BOARD_GAME_RIGHT (BOARD_RIGHT_EDGE - 0)
#pragma region Color
#define MAXIMUM 8	 
#define MINIMUM	2		 
#define MAX_LEVEL 4
#define SIDE_WALK_HEIGHT 4		 
#define DISTANCE 5
#define SLEEP_TIME 25
#define MAX_LANE 8
#define CAR_SOUND_FREQ 4500			 
#define TRUCK_SOUND_FREQ 2500		 
#define BIRD_SOUND_FREQ	1000		 
#define DINOSAUR_SOUND_FREQ 4000	 
#define FOREGROUND_BLACK        0x0000  //  text black
#define FOREGROUND_BLUE         0x0001  //  text blue
#define FOREGROUND_GREEN        0x0002  //  text green
#define FOREGROUND_CYAN         0x0003  //  text cyan
#define FOREGROUND_RED          0x0004  //  text red
#define FOREGROUND_MAGENTA      0x0005  //  text magenta
#define FOREGROUND_BROWN        0x0006  //  text brown
#define FOREGROUND_LIGHTGRAY    0x0007  //  text lightgray
#define FOREGROUND_DARKGRAY     0x0008  //  text darkgray
#define FOREGROUND_LIGHTBLUE    0x0009  //  text lightblue
#define FOREGROUND_LIGHTGREEN   0x000A  //  text lightgreen
#define FOREGROUND_LIGHTCYAN    0x000B  //  text lightcyan
#define FOREGROUND_LIGHTRED     0x000C  //  text lightred
#define FOREGROUND_LIGHTMAGENTA 0x000D  //  text lightmagenta
#define FOREGROUND_YELLOW       0x000E  //  text yellow
#define FOREGROUND_WHITE        0x000F  //  text white
#define BACKGROUND_BLACK        0x0000  // background black
#define BACKGROUND_BLUE         0x0010  // background blue
#define BACKGROUND_GREEN        0x0020  // background green
#define BACKGROUND_CYAN         0x0030  // background cyan
#define BACKGROUND_RED          0x0040  // background red
#define BACKGROUND_MAGENTA      0x0050  // background magenta
#define BACKGROUND_BROWN        0x0060  // background brown
#define BACKGROUND_LIGHTGRAY    0x0070  // background lightgray
#define BACKGROUND_DARKGRAY     0x0080  // background darkgray
#define BACKGROUND_LIGHTBLUE    0x0090  // background lightblue
#define BACKGROUND_LIGHTGREEN   0x00A0  // background lightgreen
#define BACKGROUND_LIGHTCYAN    0x00B0  // background lightcyan
#define BACKGROUND_LIGHTRED     0x00C0  // background lightred
#define BACKGROUND_LIGHTMAGENTA 0x00D0  // background lightmagenta
#define BACKGROUND_YELLOW       0x00E0  // background yellow
#define BACKGROUND_WHITE        0x00F0  // background white
#pragma endregion
void GotoXY(COORD);
COORD GetCursorPosition();
void TextColor(short);
void ClearConsole();
SMALL_RECT GetWindowSize();
void SetConsoleWindow(int width = CONSOLE_MAX_WIDTH, int height = CONSOLE_MAX_HEIGHT);
BOOL SetConsoleFontSize(COORD dwFontSize, const wchar_t *fontName);
void DrawBoard();
void GotoXY(int, int);
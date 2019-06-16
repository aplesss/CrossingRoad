#pragma once
#include "CGraphics.h"
void SetConsoleWindow(int width, int height)
{
	HWND consoleWindow = GetConsoleWindow();
	LONG Style = GetWindowLong(consoleWindow, GWL_STYLE);
	Style = Style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, Style);
	CONSOLE_CURSOR_INFO info;
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(ConsoleHandle, &info);
	COORD ConsoleBufferSize = { width, height };
	SetConsoleScreenBufferSize(ConsoleHandle, ConsoleBufferSize);
	SMALL_RECT Rect = { 0,0,ConsoleBufferSize.X - 1,ConsoleBufferSize.Y - 1 };
	SetConsoleWindowInfo(ConsoleHandle, TRUE, &Rect);
}
BOOL SetConsoleFontSize(COORD dwFontSize, const wchar_t *fontName) {
	HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX info{ sizeof(CONSOLE_FONT_INFOEX) };
	if (!GetCurrentConsoleFontEx(Out, false, &info))
		return false;
	info.dwFontSize = dwFontSize;
	wcscpy_s(info.FaceName, fontName);
	return SetCurrentConsoleFontEx(Out, false, &info);
}

void DrawBoard(void)
{
	TextColor(BACKGROUND_BLACK | FOREGROUND_WHITE);
	TextColor(16);
	GotoXY({ BOARD_LEFT_EDGE, BOARD_TOP_EDGE });
	cout << (char)201;
	GotoXY({ BOARD_RIGHT_EDGE, BOARD_TOP_EDGE });
	cout << (char)187;
	GotoXY({ BOARD_LEFT_EDGE, BOARD_BOTTOM_EDGE });
	cout << (char)200;
	GotoXY({ BOARD_RIGHT_EDGE, BOARD_BOTTOM_EDGE });
	cout << (char)188;
	GotoXY({ BOARD_RIGHT_EDGE + 55, BOARD_BOTTOM_EDGE - 20 });
	cout << (char)187;
	GotoXY({ BOARD_RIGHT_EDGE + 55, BOARD_BOTTOM_EDGE });
	cout << (char)188;
	GotoXY(BOARD_LEFT_EDGE + 1, BOARD_TOP_EDGE);
	for (short i = BOARD_LEFT_EDGE + 1; i < BOARD_RIGHT_EDGE; i++)
	{
		cout << (char)205;
	}

	GotoXY(BOARD_LEFT_EDGE + 1, BOARD_BOTTOM_EDGE);
	for (short i = BOARD_LEFT_EDGE + 1; i < BOARD_RIGHT_EDGE; i++)
	{
		cout << (char)205;
	}

	for (short i = BOARD_TOP_EDGE + 1; i < BOARD_BOTTOM_EDGE; i++)
	{
		GotoXY({ BOARD_LEFT_EDGE, i });
		cout << (char)186;
	}
	for (short i = BOARD_TOP_EDGE + 1; i < BOARD_BOTTOM_EDGE; i++)
	{
		GotoXY({ BOARD_RIGHT_EDGE, i });
		cout << (char)186;
	}
	for (short i = BOARD_RIGHT_EDGE + 1; i < BOARD_RIGHT_EDGE + 55; i++)
	{
		GotoXY({ i, BOARD_BOTTOM_EDGE - 20 });
		cout << (char)205;
	}
	for (short i = BOARD_RIGHT_EDGE + 1; i < BOARD_RIGHT_EDGE + 55; i++)
	{
		GotoXY({ i, BOARD_BOTTOM_EDGE });
		cout << (char)205;
	}
	for (short i = BOARD_BOTTOM_EDGE - 20; i < BOARD_BOTTOM_EDGE; i++)
	{
		GotoXY({ BOARD_RIGHT_EDGE + 55, i });
		cout << (char)186;
	}
	TextColor(7);
}
void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	HANDLE ConsoleHanle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(ConsoleHanle, coord);
}
void GotoXY(COORD coord)
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(ConsoleHandle, coord);
}
COORD GetCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD pos;
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleScreenBufferInfo(ConsoleHandle, &csbi)) {
		pos = { 0,0 };
	}

	pos = csbi.dwCursorPosition;
	return pos;
}


void TextColor(short color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void ClearConsole()
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(ConsoleHandle, &csbi);

	std::string str(csbi.srWindow.Right + 1, ' ');
	for (int i = 0; i <= csbi.srWindow.Bottom; i++) {
		GotoXY(0, i);
		printf("%s", str.c_str());
	}
}
SMALL_RECT GetWindowSize()
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	CONSOLE_CURSOR_INFO info;
	GetConsoleScreenBufferInfo(ConsoleHandle, &csbi);
	return csbi.srWindow;
}

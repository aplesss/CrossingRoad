#pragma once
#include "CGame.h"
bool Game::SOUND = true;
int Game::LEVEL = 1;
bool Game::IsExistFile(const char* fileName)
{
	fstream inFile(fileName);

	if (inFile)
	{
		inFile.close();
		return true;
	}

	return false;
}
void Game::DrawCurrentLevel()
{
	string s = to_string(level);
	Character cha("Character\\Level.txt");
	for (int i = 0; i < s.size(); i++) {
		Character temp = Character((string("Character\\") + s[i]).c_str());
		cha = cha + temp;
	}
	int x = BOARD_RIGHT_EDGE + 1;
	int y = BOARD_GAME_BOTTOM - cha.Height() - 7;
	TextColor(BACKGROUND_BLACK | FOREGROUND_BROWN);
	cha.Draw(x, y, false);
	if (Life > 0)
	{
		Character life("Character\\People.txt");
		Character test("Character\\People.txt");
		for (int i = 1; i < Life; i++)
		{
			life = life + test;
		}
		TextColor(BACKGROUND_BLACK | FOREGROUND_RED);
		life.Draw(x + life.Width() / 2, y + cha.Height() + 1, false);
	}

}
void Game::DrawLevel()
{
	string s = to_string(level);
	Character cha("Character\\Level.txt");

	for (int i = 0; i < s.size(); i++) {
		Character temp = Character((string("Character\\") + s[i]).c_str());
		cha = cha + temp;
	}

	SMALL_RECT rect = GetWindowSize();
	int x = (rect.Right + 1 - cha.Width()) / 2;
	int y = (rect.Bottom + 1 - cha.Height()) / 2;


	TextColor(BACKGROUND_BLACK | FOREGROUND_LIGHTCYAN);

	ClearConsole();
	cha.Draw(x, y, false);

	Character loading = Character("Character\\Loading.txt");
	TextColor(FOREGROUND_YELLOW);
	for (int i = 0; i < WAITING; i++)
	{
		loading.Draw(x-70+ loading.Width()*i, y+cha.Height()+1, false);
		Sleep(100);
	}
 
	ClearConsole();
	TextColor(BACKGROUND_BLACK | FOREGROUND_WHITE);
}

void Game::DrawMessage(string type)
{
	Character cha;
	if (type == "lose") {
		cha = Character("Character\\YOULOSE.txt");
	}
	else if (type == "gameover")
	{
		cha = Character("Character\\GAMEOVER.txt");
	}

	SMALL_RECT shape = GetWindowSize();
	int x = (shape.Right + 1 - cha.Width()) / 2;
	int y = (shape.Bottom + 1 - cha.Height()) / 2;

	TextColor(BACKGROUND_BLACK | FOREGROUND_LIGHTCYAN);

	ClearConsole();
	cha.Draw(x, y, false);
	Sleep(2500);
	ClearConsole();


	TextColor(BACKGROUND_BLACK | FOREGROUND_WHITE);
}

vector<string> Game::GetFileName(const char * path)
{
	vector<string> v;
	experimental::filesystem::path p(path);

	for (auto i = directory_iterator(p); i != directory_iterator(); i++)
	{
		if (!is_directory(i->path()))
			v.push_back(i->path().filename().string());
	}

	return v;
}

Game::Game()
{
	level = 1;
	Life = 3;
}

void Game::DrawGame()
{
	int n = line.size();
	for_each(line.begin(), line.end(), mem_fn(&Line::Draw));
	people.Draw();
}

Game::~Game()
{
}
void Game::ThreadFunction()
{
	while (true) {

		UpdatePosObject();
		checkin = true;
		lock_guard<mutex> *lock = new lock_guard<mutex>(theLock);
		DrawSeparator();
		DrawObject();
		MusicObject();
		delete lock;
		if (IsImpact())
		{
			/*for (int i = 0; i < WAITING; i++)
			{
				if (i % 3 == 0) TextColor(FOREGROUND_BROWN);
				else if(i % 3 == 1)TextColor(FOREGROUND_YELLOW);
				else TextColor(FOREGROUND_BLUE);
				people.Draw(false);
			}*/
			people.SetLive(false);
			try
			{
				ProcessDead();
			}
			catch (string s)
			{
				if (s == "MAIN MENU") checkin = false;
				return;
			}
		}
		checkin = false;
		Sleep(SLEEP_TIME);
	}
}

void Game::ResetGame()
{
	Located();
	this->Init();
}

void Game::PauseGame(char text)
{
	lock_guard<mutex> lock(theLock);
	SuspendThread(t.native_handle());
	ClearConsole();
	SetConsoleFontSize({ bigFontSizeW, bigFontSizeH }, L"Consolas");
	SetConsoleWindow(CONSOLE_MENU_WIDTH, CONSOLE_MENU_HEIGHT);
	string select;
	char ch;
	if(SOUND) PlaySound("Sound\\sfx_sounds_pause4_in.wav", NULL, SND_ASYNC);
	 if (text == 'l')
	{
		this->LoadGame();
		SetConsoleFontSize({ smallFontSizeW,smallFontSizeH }, L"Lucida Console");
		SetConsoleWindow(CONSOLE_MAX_WIDTH + 50, CONSOLE_MAX_HEIGHT);
		DrawCurrentLevel();
		DrawBoard();
		DrawPeople();
		ResumeThread(t.native_handle());
	}
	else
	{
		 if (text == 't')
		 {
			 SaveGame();
		 }
		menu.SetMenu("pause");
		while (true)
		{
			select = menu.Slection(SOUND);
			menu.ClearMenu();
			if (select == "CONTINUE") {
				ResumeGame();
				break;
			}
			else if (select == "SAVE GAME")
			{
				menu.Clear();
				SaveGame();
			}
			else if (select == "LOAD GAME") {
				this->LoadGame();
				SetConsoleFontSize({ smallFontSizeW,smallFontSizeH }, L"Lucida Console");
				SetConsoleWindow(CONSOLE_MAX_WIDTH + 50, CONSOLE_MAX_HEIGHT);
				DrawCurrentLevel();
				DrawBoard();
				DrawPeople();
				ResumeThread(t.native_handle());
				break;
			}
			else if (select == "GUIDE") {
				menu.DrawGuide();
				do
				{
					ch = _getch();
				} while (ch != ENTER);

				ClearConsole();
			}
			else if (select == "MAIN MENU")
			{
				ClearConsole();
				MenuGame m;
				m.SetMenu("yes_no");
				SMALL_RECT rect = GetWindowSize();
				int width = rect.Right - rect.Left + 1;
				int x = (width - strlen("Back to Menu?")) / 2;
				int y = (rect.Bottom) / 3 - 5;
				GotoXY(x, y);
				cout << "Back to Menu?";
				string select = m.Slection(SOUND);

				if (select == "NO") {
					string s(strlen("Back to Menu?"), ' ');
					GotoXY(x, y);
					cout << s;
				}
				else {
					TerminateThread(t.native_handle(), 0);
					t.join();
					Located();

					throw string("MAIN MENU");
				}
			}
		}
	}
}
void Game::ExitGame()
{
	ClearConsole();
	MenuGame m;
	m.SetMenu("yes_no");

	SMALL_RECT rect = GetWindowSize();
	int width = rect.Right - rect.Left + 1;
	int x = (width - strlen("Are you a bad guy?")) / 2;
	int y = (rect.Bottom) / 3 - 5;
	GotoXY(x, y);
	TextColor(4);
	cout << "Are you a bad guy?";

	string select = m.Slection(SOUND);

	if (select == "NO") {
		string s(strlen("Are you a bad guy?"), ' ');
		GotoXY(x, y);
		cout << s;
		return;
	}
	Located();
	quick_exit(EXIT_SUCCESS);
}

void Game::StartGame()
{
	if (SOUND)PlaySound("Sound\\FlyAway.wav", NULL, SND_ASYNC);
	char ch;
	string select;
	menu = MenuGame();
	SetConsoleFontSize({ bigFontSizeW, bigFontSizeH }, L"Consolas");
	SetConsoleWindow(CONSOLE_MENU_WIDTH, CONSOLE_MENU_HEIGHT);
	ClearConsole();

	while (true)
	{
		select = menu.Slection(SOUND);
		menu.ClearMenu();

		if (select == "NEW GAME") {
			SetConsoleFontSize({ smallFontSizeW,smallFontSizeH }, L"Lucida Console");
			SetConsoleWindow(CONSOLE_MAX_WIDTH + 50, CONSOLE_MAX_HEIGHT);
			level = LEVEL;
			DrawLevel();
			DrawBoard();
			DrawCurrentLevel();
			Init();
			return Run();
		}
		else if (select == "GUIDE") {
			menu.DrawGuide();
			do
			{
				ch = _getch();
			} while (ch != ENTER);
			ClearConsole();
		}
		else if (select == "SETTING") {
			this->SettingGame();
			ClearConsole();
		}
		else if (select == "LOAD GAME") {
			this->LoadGame();
			SetConsoleFontSize({ smallFontSizeW,smallFontSizeH }, L"Lucida Console");
			SetConsoleWindow(CONSOLE_MAX_WIDTH + 50, CONSOLE_MAX_HEIGHT);
			DrawCurrentLevel();
			DrawBoard();
			return Run();
		}
		else if (select == "EXIT") {
			ExitGame();
		}
	}
}
void Game::LoadGame()
{
	char fileName[50];
	int num;
	string path = "Saved\\";
	vector<string> v = GetFileName("Saved");
	vector<int> lv;
	vector<tm> time_info;
	ifstream is;

	if (!v.empty()) {
		lv.resize(v.size());
		time_info.resize(v.size());

		for (int i = 0; i < v.size(); i++) {
			is.open((path + v[i]).c_str(), ios::binary);
			is.read((char*)&lv[i], sizeof(int));
			is.read((char*)&time_info[i], sizeof(tm));
			is.close();
		}
	}

	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	CONSOLE_CURSOR_INFO info;

	GetConsoleScreenBufferInfo(ConsoleHandle, &csbi);
	int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int x = (width - 20 - 10 - 20) / 2;
	int y = (csbi.srWindow.Bottom) / 3 - 5;


	GotoXY((width - strlen("LOAD GAME")) / 2, y - 1);
	TextColor(BACKGROUND_BLACK | FOREGROUND_YELLOW);
	cout << "LOAD GAME";
	TextColor(BACKGROUND_BLACK | FOREGROUND_WHITE);
	GotoXY((width - strlen("Choose data")) / 2, y);
	cout << "Choose data";

	GotoXY(x, y + 4);
	TextColor(BACKGROUND_BLACK | FOREGROUND_CYAN);
	printf("%-20s %-10s %-20s", "Name", "Levels", "Date");
	TextColor(BACKGROUND_BLACK | FOREGROUND_WHITE);
	if (!v.empty()) {
		for (int i = 0; i < v.size(); i++) {
			GotoXY(x, y + 6 + i);
			printf("%-20s %-10d %02d/%02d/%02d %02d:%02d:%02d", v[i].c_str(), lv[i],
				time_info[i].tm_mday, time_info[i].tm_mon + 1, time_info[i].tm_year + 1900,
				time_info[i].tm_hour, time_info[i].tm_min, time_info[i].tm_sec);
		}
	}
	int x_sel = x - 2;
	int y_sel = y + 6;

	TextColor(BACKGROUND_BLACK | FOREGROUND_LIGHTCYAN);
	GotoXY(x_sel, y_sel);
	printf("%c", 175);
	string select;

	while (true) {
		char data = _getch();
		if (!(data == UP || data == DOWN))
			data = tolower(data);
		const char ch = data;
		if (ch == 'w' || ch == UP) {
			if (y_sel > y + 6) {
				GotoXY(x_sel, y_sel);
				cout << " ";
				y_sel--;
				if (SOUND) PlaySound("Sound\\sfx_menu_move4.wav", NULL, SND_ASYNC);
			}
		}
		else if (ch == 's' || ch == DOWN) {
			if (y_sel < y + 6 + v.size() - 1) {
				GotoXY(x_sel, y_sel);
				cout << " ";
				y_sel++;
				if (SOUND) PlaySound("Sound\\sfx_menu_move4.wav", NULL, SND_ASYNC);
			}
		}
		else if (ch == ENTER) {
			path += v[y_sel - y - 6];
			TextColor(BACKGROUND_BLACK | FOREGROUND_WHITE);
			break;
		}

		GotoXY(x_sel, y_sel);
		cout << (char)175;
	}

	tm tm1;
	ifstream inFile(path, ios::binary);

	inFile.read((char*)&level, sizeof(level));
	inFile.read((char*)&tm1, sizeof(tm));
	inFile.read((char*)&Life, sizeof(Life));
	inFile.read((char*)&num, sizeof(num));
	line.resize(num);

	for (int i = 0; i < num; i++) {
		line[i].Read(inFile);
	}
	people.Read(inFile);
//	menu.Read(inFile);
	inFile.read((char*)&checkin, sizeof(checkin));

	inFile.close();
	ClearConsole();
}
void Game::SettingGame()
{
	ClearConsole();
	MenuGame m;
	m.SetMenu("setting");
	string select = m.Slection(SOUND);
	if (select == "SET LEVEL")
	{
		ClearConsole();
		HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		CONSOLE_CURSOR_INFO info;
		GetConsoleScreenBufferInfo(ConsoleHandle, &csbi);
		int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		int x = (width - 20 - 10 - 20) / 2;
		int y = (csbi.srWindow.Bottom) / 3 - 5;
		GotoXY((width - strlen("SETTING LEVEL")) / 2, y - 1);
		TextColor(BACKGROUND_BLACK | FOREGROUND_YELLOW);
		cout << "SETTING LEVEL";
		TextColor(BACKGROUND_BLACK | FOREGROUND_WHITE);
		GotoXY((width - strlen("Choose LEVEL")) / 2, y);
		cout << "Choose Level";
		vector<string> v;
		v.push_back("Level 1");
		v.push_back("Level 2");
		v.push_back("Level 3");
		v.push_back("Level 4");
		if (!v.empty()) {
			for (int i = 0; i < v.size(); i++) {
				GotoXY(x, y + 6 + i);
				printf("%-20s ", v[i].c_str());
			}
		}
		int x_sel = x - 2;
		int y_sel = y + 6;
		TextColor(BACKGROUND_BLACK | FOREGROUND_LIGHTCYAN);
		GotoXY(x_sel, y_sel);
		printf("%c", 175);
		string select;
		while (true) {
			char data = _getch();
			if (!(data == UP || data == DOWN))
				data = tolower(data);
			const char ch = data;
			if (ch == 'w' || ch == UP) {
				if (y_sel > y + 6) {
					GotoXY(x_sel, y_sel);
					cout << " ";
					y_sel--;
					if (SOUND) PlaySound("Sound\\sfx_menu_move4.wav", NULL, SND_ASYNC);
				}
			}
			else if (ch == 's' || ch == DOWN) {
				if (y_sel < y + 6 + v.size() - 1) {
					GotoXY(x_sel, y_sel);
					cout << " ";
					y_sel++;
					if (SOUND) PlaySound("Sound\\sfx_menu_move4.wav", NULL, SND_ASYNC);
				}
			}
			else if (ch == ENTER) {
				 int STAGE =(y_sel - y - 6) + 1;
				 LEVEL = STAGE;
				TextColor(BACKGROUND_BLACK | FOREGROUND_WHITE);
				break;
			}
			GotoXY(x_sel, y_sel);
			cout << (char)175;
		}
		return;
	}
	else if (select == "SET SOUND") {
		m.Clear();
		m.SetMenu("on_off");
		SMALL_RECT rect = GetWindowSize();
		int width = rect.Right - rect.Left + 1;
		int x = (width - strlen("Turn off the Sound?")) / 2;
		int y = (rect.Bottom) / 3 - 5;
		GotoXY(x, y);
		cout << "Turn off the Sound?";
		select = m.Slection(SOUND);
		if (select == "OFF") {
			SOUND = false;
			string s(strlen("Turn off the Sound?"), ' ');
			GotoXY(x, y);
			cout << s;
		}
		else {
			SOUND = true;
			return;
		}
	}

}
void Game::SaveGame()
{

	char fileName[51];
	MenuGame m;
	string path = "Saved\\";

	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;

	SMALL_RECT rect = GetWindowSize();
	int width = rect.Right - rect.Left + 1;
	COORD pos;
	pos.Y = (rect.Bottom) / 3 - 4;
	pos.X = (width - strlen("File already exists! Overwrite?")) / 2;

	while (true)
	{
		GotoXY((width - strlen("Save Game")) / 2, pos.Y - 2);
		TextColor(BACKGROUND_BLACK | FOREGROUND_YELLOW);
		cout << "Save Game";
		TextColor(BACKGROUND_BLACK | FOREGROUND_WHITE);
		GotoXY(pos.X + strlen("File already exists! Overwrite?") / 4, pos.Y);
		cout << "Input name to save: ";
		GotoXY(pos.X + strlen("File already exists! Overwrite?") / 3, pos.Y + 1);

		info.dwSize = 100;
		info.bVisible = TRUE;
		SetConsoleCursorInfo(ConsoleHandle, &info);

		TextColor(BACKGROUND_BLACK | FOREGROUND_GREEN);
		cin.getline(fileName, 50);
		TextColor(BACKGROUND_BLACK | FOREGROUND_WHITE);

		info.bVisible = FALSE;
		SetConsoleCursorInfo(ConsoleHandle, &info);

		path += fileName;
		if (IsExistFile(path.c_str()))
		{
			int x = (width - strlen("File already exists! Overwrite?")) / 2;
			GotoXY(x, pos.Y + 2);
			cout << "File already exists! Overwrite?";
			m.SetMenu("yes_no");
			string select = m.Slection(SOUND);
			if (select == "YES") {
				m.Clear();
				break;
			}
			else {
				ClearConsole();
				path = "Saved\\";
			}
		}
		else
			break;
	}
	time_t current_time = time(0);
	tm * time_info = localtime(&current_time);

	ofstream outFile(path, ios::binary);

	outFile.write((char*)&level, sizeof(level));
	outFile.write((char*)time_info, sizeof(*time_info));
	outFile.write((char*)&Life, sizeof(Life));
	int num = line.size();
	outFile.write((char*)&num, sizeof(num));
	for (int i = 0; i < num; i++) {
		line[i].Write(outFile);
	}

	people.Write(outFile);
//	menu.Write(outFile);
	outFile.write((char*)&checkin, sizeof(checkin));
	outFile.close();
	GotoXY((width - strlen("Saved!")) / 2, pos.Y + 6);
	cout << "Saved";
	GotoXY((width - strlen("Press Enter to back the Menu")) / 2, pos.Y + 7);
	cout << "Press Enter to back the Menu";

	while (_getch() != ENTER);
	ClearConsole();
}

bool Game::IsLevelUp()
{
	const short people_bot = people.GetPos().Y + people.Height() - 1;

	return people_bot < HEIGHT_OFFSET + 1 + SIDE_WALK_HEIGHT;
}

void Game::LevelUp()
{
	ClearConsole();
	SuspendThread(t.native_handle());
	Located();
	level = (level == MAX_LEVEL) ? 1 : ++level;
	Init();
	DrawLevel();
	DrawBoard();
	DrawCurrentLevel();
	DrawPeople();
	ResumeThread(t.native_handle());
}

void Game::ResumeGame()
{
	if(SOUND)PlaySound("Sound\\sfx_sounds_pause4_out.wav", NULL, SND_ASYNC);
	SetConsoleFontSize({ smallFontSizeW, smallFontSizeH }, L"Lucida Console");
	SetConsoleWindow(CONSOLE_MAX_WIDTH + 50, CONSOLE_MAX_HEIGHT);
	DrawCurrentLevel();
	DrawBoard();
	DrawPeople();
	ResumeThread(t.native_handle());
}
void Game::Init()
{

	int pos;
	int arr[8] = { 0 };
	Character cha;
	short height = HEIGHT_OFFSET + 1 + SIDE_WALK_HEIGHT + 1;

	srand(static_cast<unsigned>(time(nullptr)));
	for (int i = 1; i <= 4; i++) {

		for (int j = 0; j < 2; j++) {
			do {
				pos = rand() % 8;
			} while (arr[pos]);
			arr[pos] = i;
		}
	}


	int n = 0;
	int x;
	Object *obj;
	Direction direc;
	COORD linePos;
	for (int i = 0; i < 8; i++) {

		n = (MINIMUM + level) + 1;
		x = rand() % (BOARD_GAME_RIGHT - BOARD_GAME_LEFT - 1) + (BOARD_GAME_LEFT + 1);
		direc = (i % 2 == 0 ? DLEFT : DRIGHT);
		vector<Object*> v;

		switch (arr[i])
		{
		case 1:
			v.push_back(new Cars(0, 0, direc));
			for (int j = 1; j < n; j++) {
				obj = new Cars(x, height + 1, direc);
				v.push_back(obj);

				if (direc == DLEFT) {
					x += obj->Width() + DISTANCE;
				}
				else {
					x -= obj->Width() + DISTANCE;
				}
			}

			linePos = { BOARD_GAME_LEFT + 1,height };
			line.push_back(Line(linePos, v, direc, SLEEP_TIME, CAR_SOUND_FREQ));
			break;

		case 2:
			n = 1 + (n - 1) * 2;
			v.push_back(new Birds(0, 0, direc));

			for (int j = 1; j < n; j++) {
				obj = new Birds(x, height + 1, direc);
				v.push_back(obj);

				if (direc == DLEFT) {
					x += obj->Width() + DISTANCE;
				}
				else {
					x -= obj->Width() + DISTANCE;
				}
			}

			linePos = { BOARD_GAME_LEFT + 1,height };
			line.push_back(Line(linePos, v, direc, SLEEP_TIME, BIRD_SOUND_FREQ));
			break;

		case 3:
			v.push_back(new Trucks(0, 0, direc));

			for (int j = 1; j < n; j++) {
				obj = new Trucks(x, height + 1, direc);
				v.push_back(obj);

				if (direc == DLEFT) {
					x += obj->Width() + DISTANCE;
				}
				else {
					x -= obj->Width() + DISTANCE;
				}
			}

			linePos = { BOARD_GAME_LEFT + 1,height };
			line.push_back(Line(linePos, v, direc, SLEEP_TIME, TRUCK_SOUND_FREQ));
			break;

		case 4:
			v.push_back(new Dinosaurs(0, 0, direc));

			for (int j = 1; j < n; j++) {
				obj = new Dinosaurs(x, height + 1, direc);
				v.push_back(obj);

				if (direc == DLEFT) {
					x += obj->Width() + DISTANCE;
				}
				else {
					x -= obj->Width() + DISTANCE;
				}
			}

			linePos = { BOARD_GAME_LEFT + 1,height };
			line.push_back(Line(linePos, v, direc, SLEEP_TIME, DINOSAUR_SOUND_FREQ));

			break;

		}

		height += line[i].Height() + 1;
		v.clear();
	}

	people = People((BOARD_GAME_LEFT + BOARD_GAME_RIGHT) / 2, BOARD_GAME_BOTTOM - people.Height());
	people.SetLive(true);
	checkin = false;
}

void Game::Run()
{
	DrawPeople();
	t = thread(&Game::ThreadFunction, this);
	char ch;

	while (true) {
		if (!people.IsDied()) {
			ch = _getch();
			if (!(ch == UP || ch == LEFT || ch == DOWN || ch == RIGHT))
				ch = tolower(ch);
		}
		else {
			while (checkin == true);// tao vong lap 
			if (people.IsDied())
			{
				TerminateThread(t.native_handle(), 0);
				t.join();
				ClearConsole();
				return StartGame();
			}
		}
		if (ch == 'a' || ch == 'd' || ch == 's' || ch == 'w' || ch == UP || ch == LEFT || ch == DOWN || ch == RIGHT) {

			lock_guard<mutex> lock(theLock);
			UpdatePosPeople(ch);
			DrawPeople();
			if (IsLevelUp()) {
				LevelUp();
			}
		}
		else if (ch == ESC||ch=='t'||ch=='l') {
			while (checkin == true);
			try
			{

				PauseGame(ch);
			}
			catch (string s)
			{
				if (s == "MAIN MENU") {
					Life = 3;
					return StartGame();
				}
			}
		}
		ch = ' ';
	}
}

void Game::UpdatePosPeople(const char MOVING)
{
	people.Move(MOVING);
}

void Game::UpdatePosObject()
{
	int n = line.size();

	for (int i = 0; i < n; i++) {
		line[i].PosUpdate();
	}
}

bool Game::IsImpact()
{
	const short people_top = people.GetPos().Y;
	const short people_bot = people.GetPos().Y + people.Height() - 1;

	if (people_bot <= line[0].GetPos().Y) {
		return false;
	}

	if (people_top > line[MAX_LANE - 1].GetPos().Y + line[MAX_LANE - 1].Height()) {
		return false;
	}

	for (int i = 0; i < MAX_LANE; i++) {

		const short line_top = line[i].GetPos().Y;
		const short line_bot = line[i].GetPos().Y + line[i].Height() - 1;

		if (line_top >= people_bot) {
			break;
		}

		if ((people_top >= line_top && people_top <= line_bot)
			|| (people_bot > line_top && people_bot <= line_bot)) {

			if (line[i].IsImpact(people)) {
				return true;
			}
		}
	}

	return false;
}

void Game::ProcessDead()
{

	if(SOUND)PlaySound("Sound\\sfx_deathscream_human4.wav", NULL, SND_ASYNC);

	Sleep(2000);
	(Life==0)? DrawMessage("gameover"):DrawMessage("lose");

	ClearConsole();
	SetConsoleFontSize({ bigFontSizeW, bigFontSizeH }, L"Consolas");
	SetConsoleWindow(CONSOLE_MENU_WIDTH, CONSOLE_MENU_HEIGHT);
	if (Life == 0)
	{
		menu.SetMenu("lose");
	}
	else
	{
		menu.SetMenu("continue");
	}

	while (true)
	{
		const string select = menu.Slection(SOUND);
		menu.ClearMenu();

		if (select == "RESTART") {

			SetConsoleFontSize({ smallFontSizeW,smallFontSizeH }, L"Lucida Console");
			SetConsoleWindow(CONSOLE_MAX_WIDTH + 50, CONSOLE_MAX_HEIGHT);
			menu.Clear();
			level = LEVEL;
			Life = 3;
			ResetGame();
			DrawBoard();
			DrawCurrentLevel();
			DrawPeople();
			return;
		}
		if (select == "CONTINUE") {

			SetConsoleFontSize({ smallFontSizeW,smallFontSizeH }, L"Lucida Console");
			SetConsoleWindow(CONSOLE_MAX_WIDTH + 50, CONSOLE_MAX_HEIGHT);
			menu.Clear();
			Life--;
			ResetGame();
			DrawBoard();
			DrawCurrentLevel();
			DrawPeople();
			return;
		}
		if (select == "MAIN MENU") {
			Located();
			Life = 3;
			ClearConsole();
			throw string("MAIN MENU");
		}
	}
}

void Game::DrawObject()
{

	for_each(line.begin(), line.end(), mem_fn(&Line::Draw));
}

void Game::DrawPeople()
{
	people.Draw();
}

void Game::DrawSeparator()
{
	int y = HEIGHT_OFFSET + 1 + SIDE_WALK_HEIGHT;
	string s[9];
	const short people_top = people.GetPos().Y;
	const short people_bot = people_top + people.Height() - 1;
	const short people_left = people.GetPos().X;
	const short people_right = people_left + people.Width() - 1;

	for (int k = 0; k < 9; k++) {
		if (k == 0 || k == 8) {
			if (people_top <= y && people_bot >= y) {
				for (int i = BOARD_GAME_LEFT + 1; i < people_left; i++) {
					s[k] += '_';
				}

				s[k] += people.GetCharacter().Get()[y - people_top];
				for (int i = people_right + 1; i < BOARD_GAME_RIGHT; i++) {
					s[k] += '_';
				}
			}
			else {
				for (int i = BOARD_GAME_LEFT + 1; i < BOARD_GAME_RIGHT; i++) {
					s[k] += '_';
				}
			}
		}
		else {
			if (people_top <= y && people_bot >= y) {
				for (int i = BOARD_GAME_LEFT + 1; i < people_left; i++) {
					s[k] += '_';
				}

				s[k] += people.GetCharacter().Get()[y - people_top];
				for (int i = people_right + 1; i < BOARD_GAME_RIGHT; i++) {
					s[k] += '_';

				}
			}
			else {
				for (int i = BOARD_GAME_LEFT + 1; i < BOARD_GAME_RIGHT; i++) {
					s[k] += '_';

				}
			}
		}

		if (k < 8) {
			y = line[k].GetPos().Y + line[k].Height();
		}
	}

	y = HEIGHT_OFFSET + 1 + SIDE_WALK_HEIGHT;
	for (int i = 0; i < 9; i++) {
		GotoXY(BOARD_GAME_LEFT + 1, y);
		cout << s[i];
		if (i < 8) {
			y = line[i].GetPos().Y + line[i].Height();
		}
	}
}

void Game::ClearBoard() const
{
	string s(BOARD_GAME_RIGHT - BOARD_GAME_LEFT + 1, ' ');

	for (int i = BOARD_GAME_TOP; i <= BOARD_GAME_BOTTOM; i++) {
		GotoXY(BOARD_GAME_LEFT, i);
		cout << s[i];
	}
}

void Game::Located()
{
	if (!line.empty()) {
		for (int i = 0; i < line.size(); i++) {
			line[i].Located();
		}
		line.clear();
	}
}

void Game::MusicObject()
{
	int n = line.size();
	if(SOUND)for_each(line.begin(), line.end(), bind(mem_fn(&Line::Music), std::placeholders::_1, people));
}
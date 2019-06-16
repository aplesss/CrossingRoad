#pragma once
#include"CPeople.h"
#include"CCars.h"
#include"CTrucks.h"
#include"CBirds.h"
#include"CDinosaurs.h"
#include"CMenuGame.h"
#include"CLine.h"
#include <filesystem>
#include <stdlib.h>
#include<thread>
#pragma warning(disable: 4996)
using namespace std::experimental::filesystem; // Dung de load file
class Game
{
private:
	static int LEVEL;
	static bool SOUND;
	vector<Line> line;
	People people;
	bool SetSound;
	int level;
	int Life;
	MenuGame menu;
	thread t;
	bool checkin;
	bool IsExistFile(const char *fileName);
	void DrawLevel();
	void DrawCurrentLevel();
	void DrawMessage(string);
	vector<string> GetFileName(const char *path);
	void DrawGame();
	void Init();
	void Run();
	void ThreadFunction();
	bool IsLevelUp();
	void LevelUp();
	void ResumeGame();
	void UpdatePosPeople(const char MOVING);
	void UpdatePosObject();
	bool IsImpact();
	void ProcessDead();
	void DrawObject();
	void DrawPeople();
	void DrawSeparator();
	void ClearBoard() const;
	void Located();
	void MusicObject();
	void ResetGame();
	void PauseGame(char text);
	void SettingGame();
	void ExitGame();
	void LoadGame();
	void SaveGame();
public:
	Game();
	~Game();
	void StartGame();
};


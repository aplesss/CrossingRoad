#include"CGame.h"
#include"CObject.h"
bool IS_RUNNING=true;
void ThreadIntro()
{
	CONSOLE_CURSOR_INFO info;
	info.bVisible = FALSE;
	info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	vector<Character*> Intro;
	Intro.push_back (new Character("Intro\\1.txt"));
	Intro.push_back(new Character("Intro\\2.txt"));
	Intro.push_back(new Character("Intro\\3.txt"));
	Intro.push_back(new Character("Intro\\4.txt"));
	Intro.push_back(new Character("Intro\\5.txt"));
	Intro.push_back(new Character("Intro\\6.txt"));
	Intro.push_back(new Character("Intro\\7.txt"));
	Intro.push_back(new Character("Intro\\8.txt"));
	Intro.push_back(new Character("Intro\\9.txt"));
	SetConsoleFontSize({100, 20}, L"Lucida Console");
	Character cha("Character\\INTRO_TRUCK.txt");
	Trucks trucks(10, cha.Height()+ Intro[0]->Height(), DRIGHT);
	PlaySound("Sound\\Intro.wav", NULL, SND_ASYNC);
	SetConsoleWindow(500, 500);
	int i = 0,j=0;
	while (IS_RUNNING)
	{
		if (i % 3 == 0)
			TextColor(9);
		else if (i % 3 == 1)TextColor(4);
		else TextColor(02);
		cha.Draw(20, Intro[0]->Height());
		if (i % 10==0&&j<Intro.size())
		{
			TextColor(14);
			Intro[j]->Draw((Intro[0]->Width())*j, 0,0);
			j++;
		}
		trucks.Draw();
		trucks.Move();
		if (trucks.GetPos().X >LOADING) break;
		GotoXY(50, trucks.Height() + cha.Height() + Intro[0]->Height()+1);
		(i % 5 == 0) ? TextColor(7) : TextColor(8);
		printf("PRESSING ENTER TO BEGIN!!!");
		Sleep(100);
		i++;
	}
}
void Exit(thread *t)
{
	ClearConsole();
	IS_RUNNING = false;
	t->join();

}
void main()
{
	SetConsoleTitle("CROSSING_ROAD");
	thread t1(ThreadIntro);
	char ch;
	while (1)
	{
		ch = _getch();
		if (ch == ENTER)
		{
			Exit(&t1);
			break;
		}
	}
	SetConsoleOutputCP(437);
	Game game;
	game.StartGame();
}
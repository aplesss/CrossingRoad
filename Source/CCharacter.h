#pragma once
#include<Windows.h>
#include<fstream>
#include<sstream>
#include<codecvt>
#include<vector>
#include<iostream>
#include<mutex>
#include<algorithm>
#include<stdio.h>
#include<conio.h>
#include"CGraphics.h"
using namespace std;
static mutex theLock;
class Character
{
	friend class People;
private:
	vector<string> str;
	int width, height;
public:
	Character();
	Character(const char *);
	string Get(const char *);
	vector<string>& Get();
	void Draw(COORD, bool shap = true);
	void Draw(int, int, bool shap=true);
	int Width();
	void Set(const char *);
	int Height();
	void Write(ostream &);
	void Read(istream &);
	Character operator + (Character &);
	~Character(){ }
};
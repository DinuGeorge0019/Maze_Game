#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "olcConsoleGameEngine.h"
#include "Enemy.h"
#include "Friend.h"


class Maps
{

private:
	wstring sLevel;	

public:

	string map_name;

	int nHeight;
	int nWidth;
	wchar_t GetTile(int x, int y);
	void SetTile(int x, int y, wchar_t c);
	bool GetSolid(int x, int y);
	bool CreateMap(string file, string name);
	void setLevelToNULL();
	void setLevelToGivenString(wstring& s);

	Maps();

};


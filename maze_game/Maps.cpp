#include "Maps.h"


Maps::Maps()
{
	nHeight = 0;
	nWidth = 0;
	map_name = "";
}

wchar_t Maps::GetTile(int x, int y)
{
	if (x >= 0 && x < nWidth && y >= 0 && y < nHeight)
		return sLevel[y * nWidth + x];
	else
		return L' ';

}

void Maps::SetTile(int x, int y, wchar_t c)
{
	if (x >= 0 && x < nWidth && y >= 0 && y < nHeight)
		sLevel[y * nWidth + x] = c;
}



bool Maps::GetSolid(int x, int y)
{

	if (x >= 0 && x <= nWidth && y >= 0 && y < nHeight)
	{
		if (sLevel[y * nWidth + x] == L'D' || sLevel[y * nWidth + x] == L'#')
		{
			return true;
		}
		else return false;
	}
	else return true;

}

void Maps::setLevelToNULL()
{
	sLevel = L"";
}

void Maps::setLevelToGivenString(wstring& s)
{
	sLevel = s;
}

bool Maps::CreateMap(string file, string name)
{

	map_name = name;

	wfstream in_file(file, ios::in );
	if (in_file.is_open())
	{
		in_file >> nWidth;
		in_file >> nHeight;		

		wstring sLevel_temp;
		while (getline(in_file, sLevel_temp))
		{
			sLevel += sLevel_temp;
		}

		return true;
	}
	else
	{
		return false;
	}


}


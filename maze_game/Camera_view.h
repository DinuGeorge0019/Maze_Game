#pragma once
class Camera_view
{
public:
	float PosX;
	float PosY;

	float fOffsetX;
	float fOffsetY;


	Camera_view();

	void ClampCamera(int& nLevelWidth, int& nLevelHeight, int& nVisibleTilesX, int& nVisibleTilesY);
};


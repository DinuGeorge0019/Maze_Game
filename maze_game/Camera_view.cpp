#include "Camera_view.h"

Camera_view::Camera_view()
{

	PosX = 0.0f;
	PosY = 0.0f;

	fOffsetX = PosX;
	fOffsetY = PosY;

}

void Camera_view::ClampCamera(int& nLevelWidth,int& nLevelHeight,  int& nVisibleTilesX, int& nVisibleTilesY)
{
	// Make camera see a whole screen all the time
	if (fOffsetX < 0)
	{
		fOffsetX = 0;
	}
	if (fOffsetY < 0)
	{
		fOffsetY = 0;
	}
	if (fOffsetX > nLevelWidth - nVisibleTilesX)
	{
		fOffsetX = nLevelWidth - nVisibleTilesX;
	}
	if (fOffsetY > nLevelHeight - nVisibleTilesY)
	{
		fOffsetY = nLevelHeight - nVisibleTilesY;
	}
}
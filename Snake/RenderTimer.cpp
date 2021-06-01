#include "RenderTimer.h"



RenderTimer::RenderTimer(BasicDrawPane *pane) : wxTimer()
{
	RenderTimer::pane = pane;
}


RenderTimer::~RenderTimer()
{
}

void RenderTimer::Notify()
{
	pane->snake->moveSegments();
	if (pane->inBounds() == false) {
		pane->snake->reset();
		pane->randomFoodLoc();
	}
	else if (pane->snake->collideWithItself() == false) {
		pane->snake->reset();
		pane->randomFoodLoc();
	}
	pane->checkGetFood();
	pane->Refresh();
}
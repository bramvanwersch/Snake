#pragma once

#include "wx/wx.h"
#include "Snake.h"


class BasicDrawPane : public wxPanel
{
public:
	BasicDrawPane(wxFrame* parent);
	~BasicDrawPane();

	void paintEvent(wxPaintEvent & evt);
	void paintNow();
	void render(wxDC& dc);

	bool inBounds();

	void checkGetFood();

	void onKeyDown(wxKeyEvent& event);
	void randomFoodLoc();

	Snake *snake = nullptr;
	int panelWidth = 500;
	int panelHeight = 500;
	int foodLoc[2] = { 0, 0 };

	DECLARE_EVENT_TABLE()
};


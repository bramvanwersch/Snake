#pragma once
#include <wx/wx.h>
#include <wx/timer.h>
#include "BasicDrawPane.h"


class RenderTimer : public wxTimer
{
	BasicDrawPane* pane;

public:
	RenderTimer(BasicDrawPane* pane);
	~RenderTimer();

	void Notify();

};


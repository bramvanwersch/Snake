#pragma once
#include "wx/wx.h"
#include <wx/gbsizer.h>
#include "BasicDrawPane.h"
#include "RenderTimer.h"


class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
	void onClose(wxCloseEvent& evt);

	RenderTimer* timer = nullptr;
	BasicDrawPane* drawPane = nullptr;
};


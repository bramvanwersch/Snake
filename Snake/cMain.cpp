#include "cMain.h"


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Snake", wxPoint(30, 30), wxSize(518, 541))
{
	// make sure the starting seed is random
	srand((unsigned int)time(NULL));
	drawPane = new BasicDrawPane(this);
	timer = new RenderTimer(drawPane);

	wxGridBagSizer* grid = new wxGridBagSizer(2, 2);


	grid->Add(drawPane, wxGBPosition(0, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 1);

	grid->AddGrowableRow(0);
	grid->AddGrowableCol(0);
	grid->AddGrowableCol(1);

	this->SetSizer(grid);
	this->SetAutoLayout(true);
	Show();
	timer->Start(50);
}


cMain::~cMain()
{
	delete timer;
}

void cMain::onClose(wxCloseEvent& evt)
{
	timer->Stop();
	evt.Skip();
}


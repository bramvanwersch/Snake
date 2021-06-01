#include "BasicDrawPane.h"

BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
// some useful events
/*
 EVT_MOTION(BasicDrawPane::mouseMoved)
 EVT_LEFT_DOWN(BasicDrawPane::mouseDown)
 EVT_LEFT_UP(BasicDrawPane::mouseReleased)
 EVT_RIGHT_DOWN(BasicDrawPane::rightClick)
 EVT_LEAVE_WINDOW(BasicDrawPane::mouseLeftWindow)
 EVT_KEY_DOWN(BasicDrawPane::keyPressed)
 EVT_KEY_UP(BasicDrawPane::keyReleased)
 EVT_MOUSEWHEEL(BasicDrawPane::mouseWheelMoved)
 */

 // catch paint events
	EVT_PAINT(BasicDrawPane::paintEvent)
	EVT_KEY_DOWN(BasicDrawPane::onKeyDown)

END_EVENT_TABLE()

BasicDrawPane::BasicDrawPane(wxFrame* parent): wxPanel(parent)
{
	snake = new Snake();
	randomFoodLoc();
}


BasicDrawPane::~BasicDrawPane()
{
	delete snake;
}

void BasicDrawPane::randomFoodLoc()
{
	foodLoc[0] = (rand() % panelWidth) / 10 * 10;
	foodLoc[1] = (rand() % panelHeight) / 10 * 10;
	
}


/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void BasicDrawPane::paintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	render(dc);
}

void BasicDrawPane::onKeyDown(wxKeyEvent& event)
{
	int keyCode = (int)event.GetKeyCode();
	switch (keyCode)
	{
	case 87:  // up w
		event.Skip();
		if (snake->speed[1] == 10) {
			break;
		}
		snake->speed[1] = -10;
		snake->speed[0] = 0;
		break;
	case 83: // down s
		event.Skip();
		if (snake->speed[1] == -10) {
			break;
		}
		snake->speed[1] = 10;
		snake->speed[0] = 0;
		break;
	case 65: // right a
		event.Skip();
		if (snake->speed[0] == 10) {
			break;
		}
		snake->speed[0] = -10;
		snake->speed[1] = 0;
		break;
	case 68: // left d
		event.Skip();
		if (snake->speed[0] == -10) {
			break;
		}
		snake->speed[0] = 10;
		snake->speed[1] = 0;
		break;
	default:
		break;
	}	
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 *
 * In most cases, this will not be needed at all; simply handling
 * paint events and calling Refresh() when a refresh is needed
 * will do the job.
 */
void BasicDrawPane::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void BasicDrawPane::render(wxDC&  dc)
{
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.DrawRectangle(0, 0, panelWidth, panelHeight);
	dc.SetPen(*wxTRANSPARENT_PEN);
	dc.SetBrush(*wxGREEN_BRUSH);
	for (unsigned int i = 0; i < snake->segments->size(); i++) {
		std::pair<int, int> coords = (*snake->segments)[i];
		dc.DrawRectangle(coords.first, coords.second, 10, 10);
	}
	dc.SetBrush(*wxRED_BRUSH);
	dc.DrawRectangle(foodLoc[0], foodLoc[1], 10, 10);
	dc.SetPen(wxNullPen);

	wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	dc.SetFont(font);
	const std::string score = "Score: ";
	std::string value = std::to_string(snake->segments->size() - 5);
	dc.DrawText(score + value, 5, 5);
	
}

bool BasicDrawPane::inBounds()
{
	std::pair<int, int> head_coord = (*snake->segments)[0];
	if (head_coord.first < 0 || head_coord.second < 0) {
		return false;
	}
	else if (head_coord.first > panelWidth - 10 || head_coord.second > panelHeight - 10) {
		return false;
	}
	return true;
}

void BasicDrawPane::checkGetFood()
{
	std::pair<int, int> head_coord = (*snake->segments)[0];
	if (head_coord.first == foodLoc[0] && head_coord.second == foodLoc[1]) {
		snake->segments->push_back(std::make_pair(0, 0));
		randomFoodLoc();
	}
}
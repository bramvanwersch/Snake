#include "Snake.h"


Snake::Snake()
{	
	segments = new std::vector<std::pair<int, int>>(0);
	segments->push_back(std::make_pair(250, 250));
	segments->push_back(std::make_pair(260, 250));
	segments->push_back(std::make_pair(270, 250));
	segments->push_back(std::make_pair(280, 250));
	segments->push_back(std::make_pair(290, 250));
}

Snake::~Snake()
{
	segments->clear();
	delete segments;
}

void Snake::reset()
{	
	if (segments->size() > 5) {
		segments->erase(segments->begin() + 5, segments->end());
	}
	for (unsigned int i = 0; i < segments->size(); i++) {
		(*segments)[i].first = 250 + 10 * i;
		(*segments)[i].second = 250;
	}

	speed[0] = 0;
	speed[1] = 0;
}

void Snake::moveSegments()
{
	if (speed[0] == 0 && speed[1] == 0) {
		return;
	}
	int prevX = (*segments)[0].first;
	int prevY = (*segments)[0].second;
	(*segments)[0].first += speed[0];
	(*segments)[0].second += speed[1];
	for (unsigned int i = 1; i < segments->size(); i++) {

		int prevTempX = (*segments)[i].first;
		int prevTempY = (*segments)[i].second;

		(*segments)[i].first = prevX;
		(*segments)[i].second = prevY;

		prevX = prevTempX;
		prevY = prevTempY;
	}
}


bool Snake::collideWithItself()
{
	std::pair<int, int> *first_coord = &(*segments)[0];
	for (unsigned int i = 1; i < segments->size(); i++) {
		if (first_coord->first == (*segments)[i].first && first_coord->second == (*segments)[i].second) {
			return false;
		}
	}
	return true;
}

int Snake::getScore() {
	return segments->size() - 5;
}
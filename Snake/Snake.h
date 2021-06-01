#pragma once
#include <vector>


class Snake
{
public:
	Snake();
	~Snake();
	void reset();
	void moveSegments();

	bool collideWithItself();

	int getScore();

	std::vector<std::pair<int, int>> *segments = nullptr;
	int speed[2] = { 0, 0 };
};

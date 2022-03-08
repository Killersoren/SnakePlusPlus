#pragma once
class Snake
{
public:
	const int width = 40;
	const int height = 20;
	int x, y;
	int tailX[100], tailY[100];
	int tailLength;

	enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
	Direction dir;

	Snake();

	void move_snake();
	void input_move();
	void tail_logic();
	void wall_collision();
	void snake_speed();

	bool tail_collision();
};
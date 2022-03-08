#pragma once
class Snake
{
public:
	int x, y;
	int tailX[100], tailY[100];
	int tailLength;
	int health;

	enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
	Direction dir;

	Snake();

	void move_snake();
	void input_move();
	void tail_logic();
	void wall_collision();
	void speed_snake();

	bool tail_collision();
};
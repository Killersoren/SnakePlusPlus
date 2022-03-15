#pragma once
class Snake
{
public:
	int x, y;
	int tailX[100], tailY[100];
	int tailLength;
	int *health = new int(3);

	enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
	Direction dir;

	Snake();
	~Snake();

	void move_snake();
	void input_move();
	void tail_logic();
	void wall_collision();
	void speed_fast();
	void speed_moderat();
	void speed_slow();

	bool tail_collision();
};
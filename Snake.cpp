#include <iostream>
#include <conio.h>
#include <windows.h>

#include "Snake.h"
#include "Constants.h"

Snake::Snake()
{
    this->dir = STOP;
    this->x = width / 2;
    this->y = height / 2;
    //this->health = new int(0);
}

//Snake::Snake(int health)
//{
//    this->health = new int(health);
//}

Snake::~Snake()
{
    std::cout << "Destructor called";
    //delete health;
}

void Snake::move_snake()
{
    // Changes snake's head coordinates depending on a direction
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }
}

void Snake::input_move()
{
    // Changes snake's direction depending on the button pressed and doesn't allow player to change direction in invalid way 
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
            if (dir != DOWN)
                dir = UP;
            break;
        case 'a':
            if (dir != RIGHT)
                dir = LEFT;
            break;
        case 's':
            if (dir != UP)
                dir = DOWN;
            break;
        case 'd':
            if (dir != LEFT)
                dir = RIGHT;
            break;
        }
    }
}

void Snake::tail_logic()
{
    // Tail logic. Every new eteration we remember previous position of the head and save it to prevX, prevY.
    // Then we update array with snake's parts positions (change first numbers in arrays tailX, tailY to a new head coordinates).
    // And after that for each number in arrays except the first ones we make some changes.
    // Save tailX[i], tailY[i] to prevX2, prevY2 and equate tailX[i], tailY[i] to prevX, prevY.
    // And equate prevX, prevY to prevX2, prevY2.
    // Then change rest of the arrays in the same way.

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prevX2, prevY2;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++)
    {
        prevX2 = tailX[i];
        prevY2 = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prevX2;
        prevY = prevY2;
    }
}

void Snake::wall_collision()
{
    // Changes snake position if it goes through the wall
    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;
    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;
}

void Snake::speed_fast()
{
    if (dir == UP || dir == DOWN)
        Sleep(6); // Helps to equate vertical snake movement speed and horizontal speed
    Sleep(10);
}

void Snake::speed_moderat()
{
    if (dir == UP || dir == DOWN)
        Sleep(12); // Helps to equate vertical snake movement speed and horizontal speed
    Sleep(20);
}

void Snake::speed_slow()
{
    if (dir == UP || dir == DOWN)
        Sleep(25); // Helps to equate vertical snake movement speed and horizontal speed
    Sleep(40);
}

bool Snake::tail_collision()
{
    // Detects collision with a tail
    for (int i = 0; i < tailLength; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            return true;
    }
    return false;

}

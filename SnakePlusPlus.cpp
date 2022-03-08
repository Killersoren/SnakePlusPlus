#include <iostream>
#include <windows.h>
#include <ctime>

#include "Snake.h"
#include "Food.h"
#include "Constants.h"

using namespace std;

// Variables and arrays declaration
int score;

bool invalidCoord;
bool gameOver;

Snake snake;
Food food;

void ClearScreen()
{
    // Function which cleans the screen without flickering
    COORD cursorPosition;   cursorPosition.X = 0;   cursorPosition.Y = 0;   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void Setup()
{   // Initialize variables
    gameOver = false;

    srand(time(NULL));

    food.spawn_food();

    score = 0;
}

void Draw() // Drawing playing field, snake and fruits
{
    ClearScreen();

    cout << "\n\n\n\t\t\t\t\t";

    // Draws top border
    for (int i = 0; i < width + 2; i++)
        cout << '-';
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        cout << "\t\t\t\t\t";
        for (int k = 0; k < width; k++)
        {
            // Left border
            if (k == 0)
                cout << '|';
            // Snake's head
            if (i == snake.y && k == snake.x)
                cout << '@';

            // Fruit
            else if (i == food.fruitY && k == food.fruitX)
                cout << '*';

            else
            {
                // Checks if there is a tail block with appropriate coordinates and draws it 
                bool printTail = false;
                for (int j = 0; j < snake.tailLength; j++)
                {
                    if (snake.tailX[j] == k && snake.tailY[j] == i)
                    {
                        cout << 'o';
                        printTail = true;
                    }
                }

                // Draws blank space if there is nothing to display
                if (!printTail)
                    cout << ' ';
            }

            // Right border
            if (k == width - 1)
                cout << '|';
        }
        cout << endl;
    }

    // Draws bottom border
    cout << "\t\t\t\t\t";
    for (int i = 0; i < width + 2; i++)
        cout << '-';
    cout << endl;

    // Displays player's score
    //cout << "\t\t\t\t\t";
    cout << "\t\t\t\t\tScore: " << score;

    // Display player's health
    cout << "\t\t\t Health: " << snake.health << endl;

}

void Logic()
{
    snake.tail_logic();

    snake.move_snake();

    if (snake.tail_collision())
    {
        snake.health--;
        
        if (snake.health <= 0)
            gameOver = true;
    }

    // Detects collision with a fruit
    if (snake.x == food.fruitX && snake.y == food.fruitY)
    {
        score += 1;

        food.spawn_food();

        // Generate new fruit position if it consides with snake's tail position 
        for (int i = 0; i < snake.tailLength;)
        {
            invalidCoord = false;
            if (snake.tailX[i] == food.fruitX && snake.tailY[i] == food.fruitY)
            {
                invalidCoord = true;
                food.spawn_food();
                break;
            }
            if (!invalidCoord)
                i++;
        }
        snake.tailLength++;
    }

    snake.wall_collision();
}

int main()
{
    Setup();
    while (!gameOver) // Game mainloop 
    {
        Draw();

        snake.speed_snake();

        snake.input_move();

        Logic();
    }

    return 0;
}
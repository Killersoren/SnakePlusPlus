#include <iostream>
#include <windows.h>
#include <ctime>

#include "Snake.h"
#include "Food.h"
#include "Constants.h"
#include "InfoBox.h"

using namespace std;

// Variables and arrays declaration
int score;

bool invalidCoord;
bool gameOver;

Snake snake;
Food food;

InfoBox infoBox;


void ClearScreen()
{
    // Function which cleans the screen without flickering
   COORD cursorPosition;   cursorPosition.X = 0;   cursorPosition.Y = 0;   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

/// <summary>
/// Setup default game variables, gameover and food spawn 
/// </summary>
void Setup()
{   // Initialize variables
    gameOver = false;

    //???
    //srand(time(NULL));

    food.spawn_food();

    
    score = 0;
    infoBox.setScore(0);
    infoBox.setHealth(3);

}

/// <summary>
/// Draws grid, food, infobox ,and player
/// </summary>
void Draw()
{
    ClearScreen();

    // \n = nextline
    // \t = empty space
    cout << "\n\n\n\t\t\t\t\t";

    // Top border
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
            // Player
            if (i == snake.y && k == snake.x)
                cout << 'S';

            // Fruit
            else if (i == food.foodY && k == food.foodX)
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
    infoBox.printInfo();

}


bool Gameover()
{
    if (snake.tail_collision())
    {
        snake.health--;
        infoBox.setHealth(-1);
        if (snake.health <= 0)
            gameOver = true;

        return true;
    }
    else
    {
        return false;
    }
}


/// <summary>
/// Handles collissions with walls, food, and tail. 
/// Checks player health 
/// </summary>
void Logic()
{

    snake.tail_logic();

    snake.move_snake();

    if (snake.tail_collision())
    {
        snake.health--;
        infoBox.setHealth(-1);
        if (snake.health <= 0)
            gameOver = true;
    }

    // Detects collision with a fruit
    if (snake.x == food.foodX && snake.y == food.foodY)
    {
        score += 10;
        infoBox.setScore(10);
       // infoBox.setHealth(1);

        food.spawn_food();

        // Generate new fruit position if it consides with snake's tail position 
        for (int i = 0; i < snake.tailLength;)
        {
            invalidCoord = false;
            if (snake.tailX[i] == food.foodX && snake.tailY[i] == food.foodY)
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

        if (score >= 200)
        {
            snake.speed_fast();
        }
        else if (score >= 100)
        {
            snake.speed_moderat();
        }
        else
        {
            snake.speed_slow();
        }

        snake.input_move();

        Logic();
    }

    return 0;
}
#include <iostream>
#include <windows.h>
#include <ctime>

#include "Snake.h"
#include "Food.h"
#include "HealthFood.h"
#include "Constants.h"
#include <irrKlang.h>
#include <vector>
#include "InfoBox.h"

using namespace irrklang;
using namespace std;

int choice;
int score;

bool invalidCoord;
bool gameOver;

Snake *snake = new Snake();

Food* food = new Food;
HealthFood* foodH = new HealthFood;

int health = *snake->health;
//InfoBox *infoBox = new InfoBox;

//Failed attempt to make menu items into pointers
//string *a = new string("0. Quit");
//string *b = new string("1. Play Game");

int number;

 vector<Food*> foodList;
 vector<int> intList;

ISoundEngine* engine = createIrrKlangDevice();

void ClearScreen()
{
    // Function which cleans the screen with little flickering
    COORD cursorPosition;   cursorPosition.X = 0;   cursorPosition.Y = 0;   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void SpawnFood()
{
    number = rand() % 2;

    cout << number;
    if (number == 0)
    {
        Food* tmpFood = new Food;

        foodList.push_back(tmpFood);

        tmpFood->spawn_food();
        cout << "defaultFood \n";
        cout << tmpFood->foodX << "-x";
        cout << "\n";
        cout << tmpFood->foodY << "-y";
    }

    else if (number == 1)
    {
        HealthFood* tmpFoodH = new HealthFood;

        foodList.push_back(tmpFoodH);

        tmpFoodH->spawn_food();
        cout << "SpecialtFood \n";
        cout << tmpFoodH->foodX << "-x";
        cout << "\n";
        cout << tmpFoodH->foodY << "-y";
    }
}


void RemoveFood()
{
    delete foodList.at(0);
    foodList.at(0) = NULL;
    foodList.pop_back();

}

void Setup()
{   // Initialize variables
    gameOver = false;

   // cout <<  foodList.capacity() ;

    srand(time(NULL));

    score = 0;
   // infoBox.setScore(0);
    //infoBox.setHealth(3);
    //food.spawn_food();


}

void Draw() // Drawing playing field, snake and food
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
            if (i == snake->y && k == snake->x)
                cout << '@';

            // Food which gives tail
            else if (i == foodList.at(0)->foodY && k == foodList.at(0)->foodX && foodList.at(0)->specialFruit == false)

            // Food which gives health
                cout << '*';
            else if (i == foodList.at(0)->foodY && k == foodList.at(0)->foodX && foodList.at(0)->specialFruit == true)

                cout << 'H';

            else
            {
                // Checks if there is a tail block with appropriate coordinates and draws it 
                bool printTail = false;
                for (int j = 0; j < snake->tailLength; j++)
                {
                    if (snake->tailX[j] == k && snake->tailY[j] == i)
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
    cout << "\t\t\t Health: " << health << endl;

    //Display infobox with score and health
    //infoBox.printInfo();

}

void EatSound()
{
        engine->play2D("bell.wav");
}

void Logic()
{
    snake->tail_logic();

    snake->move_snake();

    if (snake->tail_collision())
    {
        health--;
        //infoBox.setHealth(-1);

        //if (infoBox.getHealth() <= -1)
        //    gameOver = true;
        if (health <= -1)
            gameOver = true;
    }

    // Detects collision with a food
    if (snake->x == foodList.at(0)->foodX && snake->y == foodList.at(0)->foodY || snake->x == foodH->foodX && snake->y == foodH->foodY)
    {
        if (foodList.at(0)->specialFruit)
        {
            if (health < 5)
            {
                health += 1;
                //infoBox.setHealth(1);
            }
            else
            {
                score += 5;
                //infoBox.setScore(5);
            }
        }
        else
        {
            score += 10;
            //infoBox.setScore(10);

        }
        RemoveFood();
        SpawnFood();

        // Generate new fruit position if it consides with snake's tail position 
        for (int i = 0; i < snake->tailLength;)
        {
            invalidCoord = false;
            if (snake->tailX[i] == food->foodX && snake->tailY[i] == food->foodY || snake->tailX[i] == foodH->foodX && snake->tailY[i] == foodH->foodY)
            {
                invalidCoord = true;
                //food.spawn_food();
                SpawnFood();
                break;
            }
            if (!invalidCoord)
                i++;
        }
        EatSound();
        snake->tailLength++;
    }
    snake->wall_collision();
}

void PlayGame()
{
    std::cout << std::endl << "Game started" << std::endl;

    Setup();

    SpawnFood();

    while (!gameOver) // Game mainloop
    {
        Draw();
        if (score >= 200)
        {
            snake->speed_fast();
        }
        else if (score >= 100)
        {
            snake->speed_moderat();
        }
        else
        {
            snake->speed_slow();
        }
        snake->input_move();

        Logic();
    }

    if (gameOver)
    {
        RemoveFood();
        health = 3;
    }
}

int main()
{
    //Failed attempt to make menu items into pointers
    /*string *a = new string("0. Quit");
    string *b = new string("1. Play Game");*/

    //Main menu
    do
    {
        //Failed attempt to make menu items into pointers
        //std::cout << a << std::endl << b;

        std::cout << "0. Quit" << std::endl << "1. Play Game" << std::endl;
        std::cin >> choice;

        //Failed attempt to make menu items into pointers
        /*delete a;
        delete b;*/

        switch (choice)
        {
        case 0:
            std::cout << "Quitting game\n";
            return 0;
        case 1:
        {
            if (snake)
                delete snake;

            snake = new Snake();

            PlayGame();
        }
        break;
        }
    }

    while (choice != 0);
}
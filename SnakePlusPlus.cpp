#include <iostream>
#include <windows.h>
#include <ctime>

#include "Snake.h"
#include "Food.h"
#include "HealthFood.h"
#include "Constants.h"
#include <irrKlang.h>
#include <vector>

using namespace irrklang;
using namespace std;

int choice;
int score;

bool invalidCoord;
bool gameOver;

Snake snake;

Food* food = new Food;
HealthFood* foodH = new HealthFood;

int number;

 vector<Food*> foodList;
 vector<int> intList;


ISoundEngine* engine = createIrrKlangDevice();


void ClearScreen()
{
    // Function which cleans the screen without flickering
    COORD cursorPosition;   cursorPosition.X = 0;   cursorPosition.Y = 0;   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}


//
//for (size_t i = 0; i < length; i++)
//{
//
//}



void SpawnFood()
{
    number = rand() % 2;

    cout << number;



    if (number == 0)
    {
        Food* tmpFood = new Food;

        foodList.push_back(tmpFood);

        //food.spawn_food();

        tmpFood->spawn_food();
        cout << tmpFood->foodX;
        cout << tmpFood->foodY;

        cout << "test1 \n";

    }

    else if (number == 1)
    {
        HealthFood* tmpFoodH = new HealthFood;

        foodList.push_back(tmpFoodH);

        //foodH.spawn_food();
        tmpFoodH->spawn_food();
        cout << "test2 \n";


    }


}


void RemoveFood()
{
    delete foodList.at(0);
    foodList.at(0) = NULL;
    foodList.pop_back();

}

void RemoveFoodH(HealthFood food)
{

}

void Setup()
{   // Initialize variables
    gameOver = false;

    cout <<  foodList.capacity();

    srand(time(NULL));
    //srand(time(static_cast<unsigned>(0)));



    //food.spawn_food();


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
            if (i == snake->y && k == snake->x)
                cout << '@';

            //// Fruit
            //else if (i == food.foodY && k == food.foodX)

            //    cout << '*';

            //// Fruit
            //else if (i == foodH.foodY && k == foodH.foodX)
            //    cout << 'H';


            else if (i == foodList.at(0)->foodY && k == foodList.at(0)->foodX && foodList.at(0)->specialFruit == false)

                cout << '*';


            else if (i == foodList.at(0)->foodY && k == foodList.at(0)->foodX && foodList.at(0)->specialFruit == true)

                cout << 'H';

           
            //// Fruit
            //else if (i == food->foodY && k == food->foodX)

            //    cout << '*';

            //// Fruit
            //else if (i == foodH->foodY && k == foodH->foodX)
            //    cout << 'H';



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
    //int ba = *snake->health;
    cout << "\t\t\t Health: " << ba << endl;

}

void EatSound()
{

    ////engine->play2D("TrumpTale.wav");
    //engine->play2D("Inception.mp3");


    
        engine->play2D("bell.wav");

        //int tmp;
        //cout << "Press 1 + enter to exit";
        //cin >> tmp;
      //  engine->drop();
   


}

void Logic()
{
    snake->tail_logic();

    snake->move_snake();

    if (snake->tail_collision())
    {
        ba--;
        
        if (ba <= -1)
            gameOver = true;
    }

    // Detects collision with a fruit
    if (snake.x == foodList.at(0)->foodX && snake.y == foodList.at(0)->foodY || snake.x == foodH->foodX && snake.y == foodH->foodY)
    {
        if (foodList.at(0)->specialFruit)
        {
            if (snake.health < 5)
            {
                snake.health += 1;
            }
            else
            {
                score += 5;
            }
        }
        else
        {
            score += 10;
        }
        RemoveFood();
        SpawnFood();

        //Standard mad spawning

        //number = rand() % 2;

        //cout << number;

        //if (number == 1)
        //{
        //    food.spawn_food();
        //    cout << "test1";
        //}

        //else
        //{
        //    foodH.spawn_food();
        //    cout << "test2";
        //}


        // Generate new fruit position if it consides with snake's tail position 
        for (int i = 0; i < snake->tailLength;)
        {
            invalidCoord = false;
            if (snake.tailX[i] == food->foodX && snake.tailY[i] == food->foodY || snake.tailX[i] == foodH->foodX && snake.tailY[i] == foodH->foodY)
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
        snake.tailLength++;
        snake->tailLength++;
    }

    snake->wall_collision();
}

void PlayGame() 
{
    std::cout << "Game started\n";
    Setup();

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
        //test();

    }
}

int main()
{
    do
    {
        // A failed try to make the menu strings into pointers
        // std::cout << *a << std::endl << *b;

        std::cout << "0. Quit" << std::endl << "1. Play Game\n";
        std::cin >> choice;

        // A failed try to make the menu strings into pointers
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

    PlayGame();
}
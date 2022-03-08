#include "Food.h"
#include <stdlib.h>

void Food::spawn_food()
{
    fruitX = rand() % width;
    fruitY = rand() % height;

    /*fruitX = (rand() % width - 3) + 1;
    fruitY = (rand() % height - 3) + 1;*/
}

#include <stdlib.h>

#include "HealthFood.h"
#include "Constants.h"
#include "Snake.h"


void HealthFood::spawn_food()
{
    foodX = rand() % width;
    foodY = rand() % height;
    specialFruit = true;
}


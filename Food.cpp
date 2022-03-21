#include <stdlib.h>

#include "Food.h"
#include "Constants.h"

void Food::spawn_food()
{
    foodX = rand() % width;
     foodY = rand() % height;
     specialFruit = false;
}

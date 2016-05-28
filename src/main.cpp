#include <ijengine/exception.h>
#include "ije02_game.h"
#include <iostream>

using namespace ijengine;
using namespace std;

int main()
{
    int rc;

    try
    {
        Ije02Game game("Teste", SCREEN_BASE_SIZE * SCREEN_WIDTH_PROPORTION, 
                       SCREEN_BASE_SIZE * SCREEN_HEIGHT_PROPORTION);
        rc = game.run("red");
    } catch (Exception& ex)
    {
        cout << ex.what() << endl;
    }

    return rc;
}

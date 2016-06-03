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
        Ije02Game game("Teste", SCREEN_SCALED_WIDTH, SCREEN_SCALED_HEIGHT, GAME_SCALE);
        rc = game.run("red");
    } catch (Exception& ex)
    {
        cout << ex.what() << endl;
    }

    return rc;
}

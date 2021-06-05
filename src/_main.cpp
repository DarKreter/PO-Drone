#include <iostream>
#include <unistd.h>
#include <Scene.hpp>

int main()
{

    Scene lol;
    lol.SetRange(Vector3D({60,60,60}));
    lol.Draw();
    
    usleep(10'000'000);
    return 0;
}




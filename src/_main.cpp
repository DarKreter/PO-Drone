#include <iostream>
#include <unistd.h>
#include <Scene.hpp>
#include <Cuboid.hpp>

int main()
{

    Scene lol;
    lol.SetRange(Vector3D({60,60,60}));
    
    lol.AddObject(std::make_shared<Cuboid>("pr1.dat"));
    lol.AddObject(std::make_shared<Cuboid>("pr2.dat"));
    
    lol.Draw();
    usleep(1'000'000);
    
    lol.AddObject(std::make_shared<Cuboid>("pr3.dat"));
    
    lol.Draw();
    
    usleep(100'000'000);
    return 0;
}




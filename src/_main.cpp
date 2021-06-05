#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <Scene.hpp>
#include <Cuboid.hpp>

using namespace std;

#define frequency 60.

[[noreturn]] void *DrawThread([[maybe_unused]] void *arg)
{
    cout << "Siema" << std::endl;

    auto* scene = reinterpret_cast<Scene*>(arg);
    while(true)
    {
        scene->Draw();
        usleep(1'000'000./frequency);
    }
    
}

void StartNewThread(void*(*Funkcja)(void *), void * argList = NULL)
{
    pthread_t threads;
    pthread_create(&threads, NULL, Funkcja, argList);
}


int main ()
{
    Scene lol;
    lol.SetRange(Vector3D({200,200,200}));

    lol.AddObject(std::make_shared<Cuboid>("pr1.dat"));
    lol.AddObject(std::make_shared<Cuboid>("pr2.dat"));
    lol.AddObject(std::make_shared<Cuboid>("pr3.dat"));
    lol.AddObject(std::make_shared<Cuboid>("pr5.dat"));
    lol.AddObject(std::make_shared<Cuboid>("pr4.dat"));

    StartNewThread(DrawThread, &lol);
    
    usleep(4'000'000);
    for(int i = 0; i < 500; i++)
    {
        lol[0].Translation(Vector3D({0.3,0,0}));
        lol[1].Translation(Vector3D({-0.3,0,0}));
        lol[2].Translation(Vector3D({0,0.1,0}));
        lol[3].Translation(Vector3D({0.2,0,-0.4}));
        lol[4].Translation(Vector3D({0,0,0.1}));
//        lol.Draw();
        usleep(10'000);
    }

    usleep(100'000'000);
    
    
    pthread_exit(NULL);
}


#include <unistd.h>
#include <pthread.h>
#include <Scene.hpp>
#include <Cuboid.hpp>

using namespace std;


int main ()
{
    Scene lol;
    
    lol.SetRange(Vector3D({100,100,100}));
    
    
    lol.AddObject(std::make_shared<Cuboid>(Vector3D({20,0,-30}), 50, 80, 20));
    
    cout << "Vectorów3D teraz: "    << Vector3D::HowManyVectorsNow() << endl;
    cout << "Vectorów3D ogólnie: "  << Vector3D::HowManyVectorsTotal() << endl;
    usleep(5'000'000);
    
//    lol[0].TranslationRaw(Vector3D({20,20,0}));
    lol[0].RotationRaw(MatrixRot3x3(90, MatrixRot3x3::Axis::OZ));
    
    cout << "Vectorów3D teraz: "    << Vector3D::HowManyVectorsNow() << endl;
    cout << "Vectorów3D ogólnie: "  << Vector3D::HowManyVectorsTotal() << endl;
    
//    lol[0].Translation(Vector3D({20,20,0}), 40);
//    lol[0].Rotation(90,  MatrixRot3x3::Axis::OZ, 30);

    usleep(100'000);

    
    cout << "Vectorów3D teraz: "    << Vector3D::HowManyVectorsNow() << endl;
    cout << "Vectorów3D ogólnie: "  << Vector3D::HowManyVectorsTotal() << endl;
    
    usleep(40'000'000);
    
//
//    lol.AddObject(std::make_shared<Cuboid>("pr2.dat"));
//    usleep(4'000'000);
    
    pthread_exit(nullptr);
    
}


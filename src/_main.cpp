#include <unistd.h>
#include <pthread.h>
#include <Scene.hpp>
#include <Cuboid.hpp>
#include <Prism.hpp>
#include <Surface.hpp>
#include <BrokenLine.hpp>

using namespace std;


int main ()
{
    Scene lol(30);
    
    lol.SetRange(50);
//    lol.AddObject(std::make_shared<Surface>(lol.GetRange()));
//    lol.AddObject(std::make_shared<BrokenLine>(vector<Vector3D>({Vector3D({0,0,-50}), Vector3D({0,0,0}),
//                                                                 Vector3D({30,20,0}), Vector3D({30,20,-50}) })));
//    lol.AddObject(std::make_shared<Prism>(Vector3D({0,0,0}), 20, 50));
//    lol.AddObject(std::make_shared<Cuboid>(Vector3D({50,50,-20}), 20, 30,15));
    
    cout << "Vectorów3D teraz: "    << Vector3D::HowManyVectorsNow() << endl;
    cout << "Vectorów3D ogólnie: "  << Vector3D::HowManyVectorsTotal() << endl;
    usleep(2'000'000);
    
//    lol[0].TranslationRaw(Vector3D({20,20,0}));
//    lol[0].RotationRaw(MatrixRot3x3(90, MatrixRot3x3::Axis::OZ));

    
//    lol[0].Translation(Vector3D({20,20,0}), 40);
//    lol[0].Rotation(360,  MatrixRot3x3::Axis::OZ, 180);

    usleep(100'000);

    
    cout << "Vectorów3D teraz: "    << Vector3D::HowManyVectorsNow() << endl;
    cout << "Vectorów3D ogólnie: "  << Vector3D::HowManyVectorsTotal() << endl;
    
    usleep(40'000'000);
    
//
//    lol.AddObject(std::make_shared<Cuboid>("pr2.dat"));
//    usleep(4'000'000);
    
    pthread_exit(nullptr);
    
}


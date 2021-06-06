#include <unistd.h>
#include <pthread.h>
#include <Scene.hpp>
#include <Cuboid.hpp>
#include <Prism.hpp>
#include <Surface.hpp>
#include <BrokenLine.hpp>
#include <Drone.hpp>

using namespace std;


int main ()
{
    Scene lol(24);
    lol.SetRange(100);
    lol.AddObject(std::make_shared<Surface>(&lol, lol.GetRange()));
    std::shared_ptr<Drone> dronik = std::make_shared<Drone>(&lol,Vector3D({10,0,0}), 30,20,20,
                            MatrixRot3x3(0, MatrixRot3x3::Axis::OX));
    lol.AddDrone(dronik);
//    lol.AddObject(std::make_shared<BrokenLine>(vector<Vector3D>({Vector3D({0,0,-50}), Vector3D({0,0,0}),
//                                                                 Vector3D({30,20,0}), Vector3D({30,20,-50}) })));
//    lol.AddObject(std::make_shared<Prism>(Vector3D({0,0,0}), 20, 50));
//    lol.AddObject(std::make_shared<Cuboid>(Vector3D({50,50,-20}), 20, 30,15));
    
    cout << "Vectorów3D teraz: "    << Vector3D::HowManyVectorsNow() << endl;
    cout << "Vectorów3D ogólnie: "  << Vector3D::HowManyVectorsTotal() << endl;
    usleep(5'000'000);
    
//    dronik->TranslationRaw(Vector3D({20,20,0}));
//    dronik->RotationRaw(MatrixRot3x3(180, MatrixRot3x3::Axis::OZ));
    
    
    dronik->Rotation(180,  MatrixRot3x3::Axis::OZ, 180);
    dronik->Translation(Vector3D({-50,0,0}), 50);

    usleep(100'000);

    
    cout << "Vectorów3D teraz: "    << Vector3D::HowManyVectorsNow() << endl;
    cout << "Vectorów3D ogólnie: "  << Vector3D::HowManyVectorsTotal() << endl;
    
    usleep(40'000'000);
    
//
//    lol.AddObject(std::make_shared<Cuboid>("pr2.dat"));
//    usleep(4'000'000);
    
    pthread_exit(nullptr);
    
}


#include <Scene.hpp>
#include <Cuboid.hpp>
#include <Prism.hpp>
#include <Surface.hpp>
#include <BrokenLine.hpp>
#include <Drone.hpp>
#include <RidgeMountain.hpp>
#include <Pyramid.hpp>

using namespace std;
void Menu(std::shared_ptr<Drone> activeDrone);

int main ()
{
    
    try
    {
        
        char znak; uint16_t nr; double angle;
        Scene scene(24);
        std::shared_ptr<Drone> activeDrone = nullptr;

    
        scene.SetRange(200);
    
        scene.AddObject(std::make_shared<Surface>(&scene, scene.GetRange()));
  
        scene.AddObject(std::make_shared<RidgeMountain>(&scene, Vector3D({-50, 0, 100}),
                                                        200, 40, 200, MatrixRot3x3(55, MatrixRot3x3::Axis::OZ)));
        
        scene.AddObject(std::make_shared<Pyramid>(&scene, Vector3D({-100, 170, 0}),
                                                  20, 20, 300, MatrixRot3x3(78, MatrixRot3x3::Axis::OZ)));
    
        scene.AddObject(std::make_shared<Pyramid>(&scene, Vector3D({-70, -150, 0}),
                                                  35, 15, 240, MatrixRot3x3()));
        
        scene.AddObject(std::make_shared<Pyramid>(&scene, Vector3D({-130, -70, 0}),
                                                  50, 30, 150, MatrixRot3x3(33, MatrixRot3x3::Axis::OZ)));
    
        scene.AddObject(std::make_shared<Cuboid>(&scene, Vector3D({100, -105, 40}),
                                                  70, 140, 80, MatrixRot3x3(15, MatrixRot3x3::Axis::OZ)));
        
        std::shared_ptr<Drone> drone = std::make_shared<Drone>(&scene, Vector3D({-150, -150, 10}), 30, 20, 20,
                                                               MatrixRot3x3(0, MatrixRot3x3::Axis::OZ));
        scene.AddDrone(drone);
        
        drone = std::make_shared<Drone>(&scene, Vector3D({20, 20, 10}), 30, 20, 20,
                                        MatrixRot3x3(60, MatrixRot3x3::Axis::OZ));
        scene.AddDrone(drone);
        
        activeDrone = scene(0);
        if(system("clear") != 0)
            cout << "Error podczas użycia komendy systemowej!" << endl;
        Menu(activeDrone);
        
        
//        while(true)
//            usleep(1'000'000);
        
        while (true)
        {
            
            cout << "Twoj wybor? (m - menu): ";
            cin >> znak;
            switch (znak)
            {
                
                case 'a':
                    cout << endl << "Wybor aktywnego drona\n\n"
                        << "1 - Polozenie (x,y): " << setw(5) << scene(0)->LocalCoordCenter()[0] << " "
                        << setw(5) << scene(0)->LocalCoordCenter()[1] << (scene(0) == activeDrone ?  "\t<-- Dron aktywny": "") << endl
                        << "2 - Polozenie (x,y): " << setw(5) << scene(1)->LocalCoordCenter()[0] << " "
                        << setw(5) << scene(1)->LocalCoordCenter()[1] << (scene(1) == activeDrone ?  "\t<-- Dron aktywny": "") << endl;
                    cout << endl << "Wprowadz numer aktywnego drona: ";
                    
                    cin >> nr;
                    cout << endl;
                    activeDrone = scene(nr-1);
                    break;
                case 'p':
                    cout << setw(41) << "Podaj kierunek lotu (kat w stopniach): ";  cin >> angle;
                    cout << setw(41) << "Podaj dlugosc lotu: ";  cin >> nr;
                    cout << endl;
        
        
                    activeDrone->Route(nr, angle);
                    
                    break;
                
                case 'm':
                    Menu(activeDrone);
                    break;
                
                case 'c':
                    if(system("clear") != 0)
                        cout << "Error podczas użycia komendy systemowej!" << endl;
                    break;
                
                case 'k':
                    return 0;
                
                case ' ': case '\t': case '\n':
                    break;
                default:
                    cout << "Nie rozpoznana opcja!" << endl;
                    cin.ignore(std::numeric_limits<int>::max(), '\n');
                
            }
            
        }
    }
    
    catch (std::runtime_error& e)
    {
        cout << e.what() << endl;
    }
    catch (std::out_of_range& e)
    {
        cout << e.what() << endl;
    }
    catch (...)
    {
        cout << "Wystapil nie rozpoznany blad!" << endl;
    }
    
}



void Menu(std::shared_ptr<Drone> activeDrone)
{
    cout << "Polozenie drona aktywnego (x,y): " << activeDrone->LocalCoordCenter()[0] << " " << activeDrone->LocalCoordCenter()[1] << endl << endl;
    
    cout << "a - wybierz aktywnego drona" << endl
         << "p - zadaj parametry obrotu" << endl
         << "m - wyswietl menu" << endl
         << "c - czysci ekran" << endl
         << "k - koniec dzialania programu" << endl << endl;
    
    cout << "Aktualna ilosc obiektow Vector3D: "  << Vector3D::HowManyVectorsNow() << endl;
    cout << "  Laczna ilosc obiektow Vector3D: "  << Vector3D::HowManyVectorsTotal() << endl << endl;
}

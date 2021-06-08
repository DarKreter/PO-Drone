#include "Scene.hpp"
#include <tuple>
#include <utility>

/**
 * @file
 * @brief Definicje funkcji składowych klasy Scene
 */



/**
 * Na podstawie 3 wartości przesłanych w Wektorze3D,
 * ustawiany jest zakres wartości wyświetlany na osiach w programie gnuplot.
 * Konstruktor jednocześnie inicjalizuje podstawowe parametry gnuplota,
 * tak by poprawnie wyświetlał bryły w przestrzeni 3D.
 * Tworzy również plik "temp.dat" na potrzeby komunikacji z programem gnuplot.
 *
 * @param range - wektor którego odpowiednie składowe odpowiadają za zakres wartości na osiach.
 */
Scene::Scene(float fr) : frequency{fr}
{
    this->~Scene();
    system("mkdir -p temp");
    
    ZmienTrybRys(PzG::TR_3D);
}


/**
 * Czyści wszystkie narysowane figury oraz rysuje je na podstawie aktualnej ich ilości
 * i ich wartości na wierzchołkach
 * Dane są przekazywane przez plik "temp.dat"
 */
void Scene::Draw()
{
    for(auto& fig: objects)
        fig->Draw();
    
    for(auto& drone: drones)
        drone->Draw();
    
    Rysuj();
}

/**
 * Na podstawie nazwy pliku w którym zapisane są wierzchołki nowego prostopadłoscianu,
 * zostanie utworzona nowa bryła, a następnie dodana do kontenera przechowującego wszystkie bryły.
 *
 * @param object - nazwa pliku w którym zapisane są wszystkie wierzchołki
 */
void Scene::AddObject(const std::shared_ptr<Figure>& object)
{
    
    objects.push_back(object);

    Draw();
}

void Scene::AddDrone(const std::shared_ptr<Drone>& drone)
{
    drones.push_back(drone);
    
    Draw();
}


std::shared_ptr<Drone> Scene::operator()(unsigned int n)
{
    if ( n >= drones.size())
        throw std::out_of_range{"Figure out of range!"};
    return (drones[n]);
}


bool Scene::AddNewFile(const std::string& fileName, PzG::RodzajRysowania drawType, int width)
{
    system(("touch " + fileName).c_str());
    return DodajNazwePliku(fileName.c_str(), drawType, width);
}

void Scene::SetRange(double rangee)
{
    range = rangee;
    UstawZakresX(-range, range);
    UstawZakresY(-range, range);
    UstawZakresZ(0, 2*range);
}

Scene::~Scene()
{
//    system("rm -r temp");
}

void Scene::RemoveObject(std::size_t n)
{
    std::list<std::shared_ptr<Figure>>::iterator it = objects.begin();
    std::advance(it, n);
    objects.erase(it);

    Draw();
}

void Scene::RemoveLastFile(const std::string& fileName)
{
    UsunOstatniaNazwe();
    system(("rm -f " + fileName).c_str());
    system(("touch -f " + fileName).c_str());
}

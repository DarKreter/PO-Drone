#include "Scene.hpp"
#include <tuple>
#include <utility>

/**
 * @file
 * @brief Definicje funkcji składowych klasy Scene
 */



/**
 * Stworzenie sceny oraz stworzenie folderu przejściowego na pliki do każdej figury
 *
 * @param fr - częstotliwość animacji
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
 * Dane są przekazywane przez odpowiednie pliki
 */
void Scene::Draw()
{
    for(auto& fig: objects)
        fig->Draw();
    
//    for(auto& drone: drones)
//        drone->Draw();
    
    Rysuj();
}

/**
 * Dodanie nowego obiektu do listy wszystkich obiektów
 *
 * @param object - obiekt do dodania
 */
void Scene::AddObject(const std::shared_ptr<Figure>& object)
{
    
    objects.push_back(object);

    Draw();
}

/**
 * Dodanie nowego drona do listy dronów
 *
 * @param drone - dron do dodania
 */
void Scene::AddDrone(const std::shared_ptr<Drone>& drone)
{
    drones.push_back(drone);
    objects.push_back(drone);
    
    Draw();
}

/**
 * operator dostępowy do dronów
 *
 * @param n - indeks drona do którego chcemy sie dostać
 * @return - Dron którego chcieliśmy
 */
std::shared_ptr<Drone> Scene::operator()(unsigned int n)
{
    if ( n >= drones.size())
        throw std::out_of_range{"Figure out of range!"};
    return (drones[n]);
}

/**
 * Dodanie nowego pliku w którym będziemy zapisywać dane obiektu
 *
 * @param fileName - nazwa tego pliku
 * @param drawType - sposób w jaki będziemy ten plik rysować
 * @param width - szerokość pliku
 * @return - czy się powiodło
 */
bool Scene::AddNewFile(const std::string& fileName, PzG::RodzajRysowania drawType, int width)
{
    system(("touch " + fileName).c_str());
    return DodajNazwePliku(fileName.c_str(), drawType, width);
}

/**
 * ustawienie zakresu dzialności sceny w przestrzeni
 *
 * @param rangee - zakres sceny
 */
void Scene::SetRange(double rangee)
{
    range = rangee;
    UstawZakresX(-range, range);
    UstawZakresY(-range, range);
    UstawZakresZ(0, 2*range);
}

/**
 * usunięcie plików przejściowych
 */
Scene::~Scene()
{
//    system("rm -r temp");
}

/**
 * Usunięcie obiektu z listy obiektó na podstawie indeksu
 *
 * @param n - indeks do usunięcia
 */
void Scene::RemoveObject(std::size_t n)
{
    std::list<std::shared_ptr<Figure>>::iterator it = objects.begin();
    std::advance(it, n);
    objects.erase(it);

    Draw();
}

/**
 * Usunięcie pliku z dysku i usunięcie ostatniego pliku z gnuplota
 *
 * @param fileName - nazwa pliku do usunięcia
 */
void Scene::RemoveLastFile(const std::string& fileName)
{
//    UsunOstatniaNazwe();
    system(("rm -f " + fileName).c_str());
    system(("touch -f " + fileName).c_str());
}

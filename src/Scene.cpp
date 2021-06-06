#include "Scene.hpp"
#include <fstream>
#include <tuple>
#include <unistd.h>
#include <pthread.h>

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
Scene::Scene(float fr) : count{0}, drawFlag{false}, frequency{fr}
{
    system("mkdir -p temp");
    
    ZmienTrybRys(PzG::TR_3D);
//    EnableDrawing();    //TODO: remove
}


/**
 * Czyści wszystkie narysowane figury oraz rysuje je na podstawie aktualnej ich ilości
 * i ich wartości na wierzchołkach
 * Dane są przekazywane przez plik "temp.dat"
 */
void Scene::Draw()
{
    for(auto& fig: objects)
//        while(!fig->ReadyToDraw())  ;
        fig->Draw();
    

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
    AddNewFile(object->FileName("temp/object" + std::to_string(++count)));
    objects.push_back(object);
    
    std::cout << "Vectorów3D teraz: "    << Vector3D::HowManyVectorsNow() << std::endl;
    std::cout << "Vectorów3D ogólnie: "  << Vector3D::HowManyVectorsTotal() << std::endl;
    
    Draw();

}

/**
 * Możemy za jego pomocą dostać się do poszczególnych figur.
 * Umożliwa on dostęp do figur, bez możliwości modyfikacji.
 * Gdy indeks jest spoza zakresu [0;ILOŚĆ_BRYŁ] zostanie rzucony wyjątek std::out_of_range
 *
 * @param n - indeks figury do której chcemy uzyskać dostęp
 * @return zwraca referencję do figury którą chcemy zmodyfikować
 */
const Figure& Scene::operator[](unsigned int n) const
{
    if ( n >= size())
        throw std::out_of_range{"Figure out of range!"};
    return *(objects[n]);
}

/**
 * Możemy za jego pomocą dostać się do poszczególnych figur.
 * Umożliwa on modifikację tychże figur.
 * Gdy indeks jest spoza zakresu [0;ILOŚĆ_BRYŁ] zostanie rzucony wyjątek std::out_of_range
 *
 * @param n - indeks figury do której chcemy uzyskać dostęp
 * @return zwraca referencję do figury którą chcemy zmodyfikować
 */
Figure& Scene::operator[](unsigned int n)
{
    if ( n >= size())
        throw std::out_of_range{"Figure out of range!"};
    return *(objects[n]);
}

bool Scene::AddNewFile(std::string fileName, PzG::RodzajRysowania drawType, int width)
{
    system(("touch " + fileName).c_str());
    return DodajNazwePliku(fileName.c_str(), drawType, width);
}

void Scene::SetRange(Vector3D range)
{
    UstawZakresX(-range[0], range[0]);
    UstawZakresY(-range[1], range[1]);
    UstawZakresZ(-range[2], range[2]);
}

Scene::~Scene()
{
    system("rm -r temp");
    
    DisableDrawing();
}

void Scene::EnableDrawing()
{
    drawFlag = true;
    pthread_t threads;
    
    pthread_create(&threads, NULL, DrawThread, new std::tuple<Scene*, float, volatile bool&>(this,frequency,drawFlag));
}

void *DrawThread([[maybe_unused]] void *arg)
{
//    auto [scene, frequency, threadEnable] = *(reinterpret_cast<std::tuple<Scene*, float, volatile bool&>*>(arg));
    auto krotka =  *(reinterpret_cast<std::tuple<Scene*, float, volatile bool&>*>(arg));
    auto scene = std::get<0>(krotka);
    auto frequency = std::get<1>(krotka);
    auto& threadEnable = std::get<2>(krotka);
    delete reinterpret_cast<std::tuple<Scene*, float, volatile bool&>*>(arg);
    
    while(threadEnable)
    {
        scene->Draw();
        usleep(1'000'000./frequency);
    }
    
    pthread_exit(nullptr);
}



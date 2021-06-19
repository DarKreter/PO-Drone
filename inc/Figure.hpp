//
// Created by darkr on 05.06.2021.
//

#ifndef DRONE_FIGURE_HPP
#define DRONE_FIGURE_HPP

#include <string>
#include <utility>
#include <unistd.h>
#include <Vector.hpp>
#include <MatrixRot.hpp>
#include <Rectangle.hpp>
#include <vector>
#include <functional>
#include <memory>

/**
 * @file
 * @brief
 * Definicja klasy Figure
 */

class Scene;

/**
 * @brief Modeluje pojęcie pojedynczego obiektu
 *
 * Przechowuje wszystkie informacje dotyczące pojedynczej figury nie wazne czy jest to
 * prostopadloscian czy tez granistoslup.
 * Jest to klasa abstrakcyjna
 */
class Figure
{
public:
    /**
     * @brief Okresla jakiego typu jest aktualnie figura
     */
    enum class Type
    {
        Figure = 0/** jest to figura*/,
        Cuboid/** jest to jest to prostopadłościan*/,
        Prism/** jest to graniastosłup*/,
        BrokenLine/** jest to linia łamana*/,
        Plateau/** jest to płaskowyż*/,
        Drone/** jest to dron*/,
        Pyramid/** jest to ostrosłup*/,
        RidgeMountain/** jest to góra z długą granią*/,
        Surface/** jest to powierzchnia tytana*/
    }whoIAm;
    
protected:
    /**
     * @brief przechowuje informacje o nazwie pliku dla gnuplota tego obiektu
     */
    std::string fileName;
    /**
     * @brief Przechowuje informacje co ile punktów nalezy zrobic dodatkowy znak nowej linii
     */
    uint8_t fileNewLine;
    
    /**
     * @brief Macierze przechowujace rotacje drona względem swojego środa jak i innego punktu
     */
    MatrixRot3x3 localOrientation, globalOrientation;
    /**
     * @brief Polozenie srodka danej figury
     */
    Vector3D localCoordCenter;
    /**
     * @brief Punkt wzgledem ktorego mamy obrocic nasz punkt
     */
    const Vector3D* rotationCenter;
    
    /**
     * @brief wskaznik na scene w ktorej figura sie znajduje
     */
    Scene* whereIAm;
    
    /**
     * @brief Licznik figur
     */
    static std::uint16_t count;
    
    /**
 * @brief Konstruktor tworzacy figure dostajacy niezbedne informacje o niej
     */
    explicit Figure(Scene *scene, std::string fn, uint8_t fnl, Type tt, const MatrixRot3x3 &matRot,
                    Vector3D localCenter, Vector3D *rotationCentr = nullptr);
    
    /**
     * @brief Funkcja animujaca okreslony ruch
     */
    template<typename T>
    void Animate(std::function<void(double)>function, T arg, double speed, double frequency);
    
    /**
     * @brief Funkcja ktora na podstawie srodka ukladu wspolrzednych tworzy bryle wokol punktu 0
     */
    virtual std::vector<Vector3D>& CalcLocalCoords(std::vector<Vector3D>&) = 0;
    
    /**
     * @brief informacja czy figura jest zagniezdzona w innej
     */
    bool nested = false;
    
public:
    /**
     * @brief Zwraca rzut figury na oś OXY
     */
    virtual Rectangle OXYprojection();
    
    /**
     * @brief Funkcja przeliczajaca wektor punktow lokalnych na globalny uklad wspolrzednych
     */
    void CalcGlobalCoords(std::vector<Vector3D>& vertices);
    
    /**
     * @brief Funkcja zapisujaca do pliku aktualne polozenie figury
     */
    virtual void Draw();
    
    /**
     * @brief Funkcja realizujaca przesuniecie figury o dany wektor z dana predkoscia
     */
    virtual void Translation(Vector3D wektor, double speed);
    /**
     * @brief Funckja realizujaca przesuniecie figury o dany wektor bez animacji
     */
    virtual void TranslationRaw(const Vector3D& wektor);
    
    /**
     * @brief Funkcja realizujaca obrot wokol danego punktu
     */
    virtual void RotationGlobal(double angle, MatrixRot3x3::Axis axis,  double speed);
    /**
     * @brief Funkcja realizujaca obrot wokol wlasnego srodka
     */
    virtual void RotationLocal(double angle, MatrixRot3x3::Axis axis,  double speed);
    /**
     * @brief Funkcja realizujaca obrot wokol wlasnego srodka bez animacji
     */
    virtual void RotationRawLocal(const MatrixRot3x3& macRot);
    /**
    * @brief Funkcja realizujaca obrot wokol danego punktu bez animacji
    */
    virtual void RotationRawGlobal(const MatrixRot3x3& macRot);
    
/**
 * @brief Nadpisuje nazwe pliku i ja zwraca
 * @param sf - nowa nazwa pliku
 * @return - nowa nazwa pliku
 */
    std::string FileName(std::string sf) {return fileName = sf;}
    /**
     * @brief Ustawienie sceny figury na przyslany wskaznik
     * @param s - wskaznik na scene na ktora sie ustawiamy
     */
    void SetScene(Scene*s) {whereIAm = s;}
    /**
     * @brief Sprawdzenie czy figura jest zagniezdzona
     */
    void Nested() { nested = true; }
    /**
     * @brief Funkcja dostepowa do lokalnego srodka figury
     * @return Wektor polozenia lokalnego srodka figury
     */
    Vector3D LocalCoordCenter() { return localCoordCenter; }
    /**
     * @brief Zwraca srodek podstawy figury
     * @return  dwie pierwsze wspolrzednie lokalnego srodka
     */
    Vector<2> BaseCenter() { return Vector<2>({localCoordCenter[0], localCoordCenter[1]}); }
    /**
     * @brief Dostep do globalnego srodka figury
     * @return Wektor polozenia globalnego srodka
     */
    MatrixRot3x3 GlobalOrientation() { return globalOrientation; }
    /**
     * @brief Pozwala ustawic srodek rotacji na dany punkt
     * @param w - wskaznik na wektor na ktory chcemy ustawic
     */
    void RotationCenter(Vector3D* w) {rotationCenter = w;}
    /**
     * @brief Wyczyszczenie srodka rotacji
     */
    void ClearRotationCenter() {rotationCenter = &localCoordCenter;}
    /**
     * @brief Informacja jakiego typu obiektem jestesmy
     * @return typ wyliczeniowy jakiego rodzaju obiektem jestesmy
     */
    Type WhoIAm() { return whoIAm; }
    /**
     * @brief Informacja jakiego typu obiektem jestesmy ale w stringu
     * @return Slowna informacja kim jestesmy
     */
    std::string WhoIAmText();

    /**
     * @brief Destruktor figury
     */
    ~Figure();
};

#include<Figure.tpp>

#endif //DRONE_FIGURE_HPP

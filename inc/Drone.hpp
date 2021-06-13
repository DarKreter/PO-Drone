//
// Created by darkr on 06.06.2021.
//
#ifndef DRONE_DRONE_HPP
#define DRONE_DRONE_HPP
#include <memory>
#include <MatrixRot.hpp>
#include <Cuboid.hpp>
#include <Prism.hpp>
#include <BrokenLine.hpp>

/**
 * @file
 * @brief Definicja klasy dron
 */

/**
 * @brief Opis klasy dron definiujacej pojecie drona
 */
class Drone: public Figure
{
private:
    /**
     * @brief korpus drona i swiatla na przodzie
     */
    std::shared_ptr<Cuboid> body, light1, light2;
    /**
     * @brief 4 rotory drona
     */
    std::array<std::shared_ptr<Prism>,4> rotors;

public:

    /**
     * @brief konstruktor drona ktory go tworzy
     */
    explicit Drone(Scene* scene, const Vector3D& localCenter, double wid, double len, double hei, const MatrixRot3x3& matRot = MatrixRot3x3());
    
    /**
     * @brief Przelicza na podstawie srodka wszystkie wierzcholki do lokalnego ukladu
     */
    std::vector<Vector3D>& CalcLocalCoords(std::vector<Vector3D>&) override;
    
    /**
     * @brief Przesuwa drona o zadany wektor z animacja
     */
    void Translation(Vector3D wektor, double speed) override;
    /**
     * @brief Przesuwa drona o zadany wektor od razu
     */
    void TranslationRaw(const Vector3D& wektor) override;
    
    /**
     * @brief Obraca drona o zadany kat z animacja
     */
    void Rotation(double angle, MatrixRot3x3::Axis axis,  double speed);
    /**
     * @brief PObraca drona o zadany kat od razu
     */
    void RotationRaw(const MatrixRot3x3& macRot);
    
    /**
     * @brief Liczy wierzcholki i zapisuje je do pliku
     */
    void Draw() override;
    
    /**
     * @brief Wykonuje trase
     */
    void Route(double nr, double angle);
    /**
     * @brief Tworzy linie lamana na podstawie zadanych parametrow lotu
     */
    std::shared_ptr<BrokenLine> CreateRoute(double nr, double angle);
    
    /**
     * @brief Ustawia srodki elementow do obracania
     */
    void SetCenter();
    /**
     * @brief czysci srodki elementow do obracania
     */
    void ClearCenter();
};


#endif //DRONE_DRONE_HPP

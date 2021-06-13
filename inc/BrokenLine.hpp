//
// Created by darkr on 06.06.2021.
//

#ifndef DRONE_BROKENLINE_HPP
#define DRONE_BROKENLINE_HPP
#include <iostream>
#include <MatrixRot.hpp>
#include <Vector.hpp>
#include "MatrixRot.hpp"
#include "Figure.hpp"

/**
 * @file
 * @brief Definicja klasy linia łamana
 */

class BrokenLine: public Figure
{
    /**
     * @brief Wektor punktow z ktorych ma sie utworzyc ta linia
     */
    std::vector<Vector3D> points;

public:
    
    /**
     * @brief konstruktor linii lamanej
     */
    explicit BrokenLine(Scene *scene, std::vector<Vector3D> p);
    
    /**
     * @brief Liczenie wszystkich wspolrzednych na podstawie srodka i bokow
     */
    std::vector<Vector3D>& CalcLocalCoords(std::vector<Vector3D>& a) override;
    
//    void Draw() override;

    /**
     * @brief destruktor linii lamanej ktory zwalnia pamiec dla srodka rotacji
     */
    ~BrokenLine() {delete rotationCenter;}
    
};


#endif //DRONE_BROKENLINE_HPP

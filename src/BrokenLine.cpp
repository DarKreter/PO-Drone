//
// Created by darkr on 06.06.2021.
//

#include "BrokenLine.hpp"
#include <fstream>
#include <utility>
/**
 * @file
 * @brief Definicje funkcji klasy linia łamana
 */

/**
 * Tworzy linie łamaną
 *
 * @param scene - wskaźnik na scene w której jest ten obiekt
 * @param p - wektor punktów z których będzie się składać linia
 */
BrokenLine::BrokenLine(Scene *scene, std::vector<Vector3D> p)
        : Figure(scene, "SomethingWentWrong.jpg", 128, Type::BrokenLine, MatrixRot3x3(), Vector3D()), points{std::move(p)}
{}

/**
 * Przeliczanie wierzchołków do układu lokalnego
 *
 * @param vertices - wektor gdzie będziemy zapisywać wierzchołki
 * @return - zwracamy wyliczone wierzchołki
 */
std::vector<Vector3D>& BrokenLine::CalcLocalCoords(std::vector<Vector3D>& vertices)
{
    for(auto& point: points)
        vertices.push_back(point);
    
    return vertices;
}




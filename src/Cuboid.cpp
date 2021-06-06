#include <Cuboid.hpp>
#include <fstream>
#include <vector>


/**
 * @file
 * @brief Definicje funkcji składowych klasy Cuboid
 */

/**
 * Wszystkie wierzchołki zostają wczytane bezpośrednio z pliku.
 *
 * @param name - nazwa pliku który zostanie otworzony i zostaną z niego
 * wczytane wszystkie wierzchołki
 */
Cuboid::Cuboid(const Vector3D& localCenter, double w, double l, double h, const MatrixRot3x3& matRot)
    : Figure("SomethingWentWrong.jpg", 2, matRot, localCenter), width{w}, length{l}, height{h}
{}


std::vector<Vector3D>& Cuboid::CalcLocalCoords(std::vector<Vector3D>& vertices)
{
    
    double halfWidth = width/2, halfHeight = height/2, halfLength = length/2;
    
    Vector3D vertex;
    for(int i = 0;i < 8; i++)
    {
        if(i < 4)
            vertex[2] = -halfHeight;
        else
            vertex[2] = halfHeight;
        
        if(i%2 == 0)
            vertex[0] = -halfLength;
        else
            vertex[0] = halfLength;
        
        if(i > 1 && i < 6)
            vertex[1] = -halfWidth;
        else
            vertex[1] = halfWidth;
        
        vertices.push_back(vertex);
    }
    
    vertices.push_back(vertices[0]);
    vertices.push_back(vertices[1]);
    
    return vertices;
}




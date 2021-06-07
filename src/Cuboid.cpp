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
Cuboid::Cuboid(Scene *scene, const Vector3D &localCenter, double w, double l, double h, const MatrixRot3x3 &matRot, Vector3D* rotCen)
    : Figure(scene, "SomethingWentWrong.jpg", 4, matRot, localCenter, rotCen), width{w}, length{l}, height{h}
{}


std::vector<Vector3D>& Cuboid::CalcLocalCoords(std::vector<Vector3D>& vertices)
{
    
    double halfWidth = width/2., halfHeight = height/2., halfLength = length/2.;
    
    MatrixRot3x3 obrot(90,MatrixRot3x3::Axis::OY);
    
    
    Vector3D vertex;
    for(int i = 0;i < 5; i++)
        for(int j = 0; j<4;++j)
        {
            if(j < 2)
                vertex[1] = -halfWidth;
            else
                vertex[1] = halfWidth;
            
            if(j % 3 == 0)
            {
                vertex[2] = 0;
                vertex[0] = 0;
            }
            else
            {
                if(i < 2 || i ==4)
                    vertex[2] = halfHeight;
                else
                    vertex[2] = -halfHeight;
               
                if(i == 1 || i == 2)
                    vertex[0] = halfLength;
                else
                    vertex[0] = -halfLength;
            }
            
            vertices.push_back(vertex);
        }
    
    return vertices;
}




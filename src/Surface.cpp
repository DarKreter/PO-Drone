//
// Created by darkr on 06.06.2021.
//

#include "Surface.hpp"
#include <fstream>
/**
 * @file
 * @brief Definicje składowych funkcji klasy Surface
 */

/**
 * Tworzy obiekt klasy Surface
 *
 * @param scene - Scena w której aktualnie znajduje się płaszczyzna
 * @param r - zasięg płaszczyzny
 */
Surface::Surface(Scene *scene, double r)
        : Figure(scene, "SomethingWentWrong.jpg", 0, Type::Surface, MatrixRot3x3(), Vector3D()), range{r}, level{0}
{}

/**
 * Wpisaniue odpowiednich wierzchołków do pliku tak aby dało się narysować płaszczyznę
 */
void Surface::Draw()
{
    std::ofstream str(fileName);
    for(uint8_t i = 0; i <= 20; i++)
    {
        for(uint8_t j = 0; j <= 20; j++)
            str << j*range/10 - range << " "<< i*range/10 - range << " "<< level << std::endl;
        
        str << std::endl;
    }
    
    str.close();
}



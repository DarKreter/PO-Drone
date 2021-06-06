//
// Created by darkr on 06.06.2021.
//

#include "Surface.hpp"
#include <fstream>


Surface::Surface(double r)
        : Figure("SomethingWentWrong.jpg", 0, MatrixRot3x3(), Vector3D()), range{r}, level{-r}
{}

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



//
// Created by darkr on 05.06.2021.
//

#include <fstream>
#include "Figure.hpp"

Figure::Figure(std::string fn): fileName{std::move(fn)}
{
    std::ifstream file(fileName);
    file >> (*this);
    file.close();
}
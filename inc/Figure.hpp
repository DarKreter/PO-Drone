//
// Created by darkr on 05.06.2021.
//

#ifndef DRONE_FIGURE_HPP
#define DRONE_FIGURE_HPP


#include <string>
#include <utility>
#include <Vector.hpp>

class Figure
{
protected:
    std::string fileName;
    
    explicit Figure(std::string);
    
public:
    virtual void Draw() = 0;
    virtual void Translation(Vector3D) = 0;

    std::string FileName(std::string sf) {return fileName = sf;}
};

std::istream& operator >> (std::istream& strm, Figure& pr);

#endif //DRONE_FIGURE_HPP

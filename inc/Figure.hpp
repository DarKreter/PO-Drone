//
// Created by darkr on 05.06.2021.
//

#ifndef DRONE_FIGURE_HPP
#define DRONE_FIGURE_HPP


#include <string>
#include <utility>

class Figure
{
    std::string fileName;
public:
    explicit Figure(std::string);
    
    virtual void Draw() = 0;
    
    std::string FileName() {return fileName;}
};

std::istream& operator >> (std::istream& strm, Figure& pr);

#endif //DRONE_FIGURE_HPP

//
// Created by janru on 08.03.2022.
//

#ifndef ZAD1_FILE_END_STATE_H
#define ZAD1_FILE_END_STATE_H


#include <string>
#include <fstream>

class file_solution {
    std::ofstream file;
public:
    file_solution(std::string file);
};


#endif //ZAD1_FILE_END_STATE_H
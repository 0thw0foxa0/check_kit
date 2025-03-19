#include "kits.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool Kit::loadFromFile(std::string filename)
{
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cout<<"Не удалось открыть файл:  "<<filename<<std::endl;
        return false;
    }
    requirements.clear();
    std::string line;
    std::getline(file,line); // пропуск строки "каталог кол-во"
    while(std::getline(file,line)){
        if(line.empty())continue; // пропуск пустой строки
        std::istringstream iss(line); //разбиваем строку на части
        std::string catalog;
        int quantity;
        iss>>catalog>>quantity; // чтения строки кат и кол-во
        if(catalog.front()=='"'&&catalog.back()=='"')catalog=catalog.substr(1,catalog.length()-2);
        requirements.push_back({catalog,quantity});
    }
    file.close();
    return true;
}

std::vector<std::pair<std::string,int>> Kit::getRequirements()
{
    return requirements;
}
#ifndef KIT_H
#define KIT_H

#include<string>
#include<vector>

class Kit
{
public:
    bool loadFromFile(std::string filename); // загружает файл
    std::vector<std::pair<std::string,int>> getRequirements(); // возвращает требования
private:
    std::vector<std::pair<std::string,int>> requirements; // список каталогов
};

#endif
#ifndef DOCUMENT_H
#define DOCUMENT_H

#include<string>
#include<vector>

class Document
{
public:
    struct Item
    {
        int position,quantity;
        std::vector<std::string> catalogs;
    };
    bool loadFromFile(std::string filename); // загружает файл
    bool containsKit(std::vector<std::pair<std::string,int>> kit,std::vector<Item>& matches); // проверка включает ли набор
private:
    std::vector<Item> items;
};

#endif // DOCUMENT_H
#include "document.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool Document::loadFromFile(std::string filename)
{
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cout<<"Файл: "<<filename<<"не открылся"<<std::endl;
        return false;
    }
    items.clear();
    std::string line;
    std::getline(file,line); // пропуск строки "поз кол-во каталоги"
    while(std::getline(file,line))
    {
        if(line.empty())continue; // пропуск пустой строки
        std::istringstream iss(line); // чтение строки
        Item item;
        iss>>item.position>>item.quantity; //  разбивка строки
        std::string catalog;
        while(iss>>catalog)
        {
            if(catalog.front()=='"'&&catalog.back()=='"')catalog=catalog.substr(1,catalog.length()-2); // пропуск ""
            if(!catalog.empty()&&catalog.back()==',')catalog.pop_back(); // пропуск ,
            item.catalogs.push_back(catalog);
        }
        items.push_back(item);
    }
    file.close();
    return true;
}

bool Document::containsKit(std::vector<std::pair<std::string,int>> kit,std::vector<Item>& matches)
{
    std::vector<int> available(kit.size(),0); // считаем доступное количество для каждого каталога
    for(const auto& item:items)
    {
        for(const auto& catalog:item.catalogs)
        {
            for(size_t i=0;i<kit.size();i++)if(catalog==kit[i].first)available[i]+=item.quantity; // колличество совпадений
        }
    }
    matches.clear();
    for(size_t i=0;i<kit.size();i++)if(available[i]<kit[i].second)return false; // не хватает товара
    std::vector<int> used(kit.size(),0); // сколько уже использовано для каждого каталога
    for(const auto& item:items)
    {
        for(const auto& catalog:item.catalogs){
            for(size_t i=0;i<kit.size();i++)
            {
                if(catalog==kit[i].first&&used[i]<kit[i].second)
                {
                    int use=std::min(kit[i].second-used[i],item.quantity);
                    matches.push_back({item.position,use,{catalog}});
                    used[i]+=use;
                }
            }
        }
    }
    return true;
}
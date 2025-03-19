#include "document.h"
#include "kits.h"
#include "path_utils.h"
#include <string>
#include <iostream>
#include <ostream> // только для некоторых компиляторов

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif


int main(int argc,char* argv[])
{

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // вывод utf-8 для windows
    SetConsoleCP(CP_UTF8); // ввод utf-8 для windows
#endif
    std::string docPath=getFilePath(argv[0],"document"),kitPath=getFilePath(argv[0],"kit");
  

    Document doc;
    if(!doc.loadFromFile(docPath))return 1;

    Kit kit;
    if(!kit.loadFromFile(kitPath))return 1;

    std::vector<Document::Item> matches;

    if(doc.containsKit(kit.getRequirements(),matches))
    {
        std::cout<<"Набор содержится в документе.\nСостав набора\nПоз.\tКол-во\tКаталог\n";
        for(const auto& item:matches)std::cout<<item.position<<"\t"<<item.quantity<<"\t"<<item.catalogs[0].c_str()<<"\n";
    }
    else std::cout<<"Набор не входит в документ.\n";

    return 0;
}

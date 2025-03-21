#include <fstream>
#include <string>
#include <iostream>

std::string getFilePath(const std::string& argv0, const std::string& basename) 
{
    // std::cout << "Путь к программе: " << argv0 << std::endl; // ОТЛАДОЧНАЯ СТРОКА

    size_t lastSlash = argv0.find_last_of("\\/");
    std::string rootPath;

    if (lastSlash == std::string::npos) 
    {
        // std::cout << "Слэш не найден" << std::endl; // ОТЛАДОЧНАЯ СТРОКА
#ifdef _WIN32
        // На Windows проверяем, откуда запущен исполняемый файл
        if (argv0.find("Debug") != std::string::npos || argv0.find("Release") != std::string::npos) {
            rootPath = "../../"; // Windows: из build/Debug или build/Release в корень
        } else {
            rootPath = "../";    // Windows: из build в корень (MinGW)
        }
#else
        rootPath = "../";    // Linux: из build в корень
#endif
    } 
    else 
    {
        std::string execPath = argv0.substr(0, lastSlash);
#ifdef _WIN32
        // На Windows проверяем, есть ли в пути Debug или Release
        if (execPath.find("Debug") != std::string::npos || execPath.find("Release") != std::string::npos) {
            rootPath = execPath + "/../../"; // Windows: два уровня вверх
        } else {
            rootPath = execPath + "/../";    // Windows: один уровень вверх (MinGW)
        }
#else
        rootPath = execPath + "/../";    // Linux: один уровень вверх
#endif
    }
    // std::cout << "Путь к корню: " << rootPath << std::endl; // ОТЛАДОЧНАЯ СТРОКА

    std::string path = rootPath + basename + ".txt";
    // std::cout << "Пробуем открыть: " << path << std::endl; // ОТЛАДОЧНАЯ СТРОКА
    std::ifstream file(path);
    if (file.is_open()) 
    {
        file.close();
        // std::cout << "Файл найден: " << path << std::endl; // ОТЛАДОЧНАЯ СТРОКА
        return path;
    }

    // std::cout << "Файл не найден, возвращаем: " << path << std::endl; // ОТЛАДОЧНАЯ СТРОКА
    return path;  
}

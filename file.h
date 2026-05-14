#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "memtrace.h"

//File class, its task is to read and write the in/out -put TXT
class File {
public:
    std::vector<std::string> readTXT(std::string path);
    void writeTXT(std::string path, std::vector<std::string> data);
};

#endif //FILE_H
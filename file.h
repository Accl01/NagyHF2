#ifndef FILE_H
#define FILE_H


#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "memtrace.h"

class File {
public:
    std::vector<std::string> readTXT(std::string path);
    void writeTXT(std::string path, std::vector<std::string> data);


};

#endif //FILE_H
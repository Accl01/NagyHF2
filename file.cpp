#include "file.h"

std::vector<std::string> File::readTXT(std::string path){
    std::vector<std::string> inputs;
    std::ifstream input(path);

    if(!input.is_open()){
        return inputs;
    }

    std::string line;
    while(std::getline(input, line)){
        if(!line.empty()){
            inputs.push_back(line);
        }
    }
    input.close();
    return inputs;
}

void File::writeTXT(std::string path, std::vector<std::string> data){
    std::ofstream output(path);
    for(const auto& line: data){
        output << line << std::endl;
    }
    output.close();
}

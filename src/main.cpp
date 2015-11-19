#include <iostream> 
#include <string>
#include "read/json.h"

int main(){
        for (std::string line; std::getline(std::cin, line);) {
                std::cout << encode(line.c_str()).DebugString() << std::endl;
        }
        return 0;
}

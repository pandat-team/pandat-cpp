#include <iostream> 
#include <string>
#include <queue>
#include "read/json.h"
#include "write/csv.h"

int main(){
        std::queue<Tuple> out;
        encode(std::cin, out);
        decode(out, std::cout);
        /*
        for (std::string line; std::getline(std::cin, line);) {
                Tuple t = encode(line.c_str());
                std::cout << decode() << std::endl;

                std::cout << encode(line.c_str()).DebugString() << std::endl;
        }*/
        return 0;
}

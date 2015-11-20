#include <iostream> 
#include <string>
#include <queue>
#include <atomic>
#include <thread>
#include "readerwriterqueue/readerwriterqueue.h"
#include "read/json.h"
#include "write/csv.h"

using namespace moodycamel;

int main(){
        BlockingReaderWriterQueue<Tuple> out(100);
        std::thread writer([&]() {
                        decode(out, std::cout);

                        });
        std::thread reader([&]() {
                        encode(std::cin, out);

                        });
        writer.join();
        reader.join();
        return 0;
}

#include <queue>
#include <sstream> 
#include <string>
#include "libcsv/csv.h"
#include "pirf/pirf.pb.h"
#include <unistd.h>
#include "readerwriterqueue/readerwriterqueue.h"

using namespace moodycamel;

std::string csv_header_from_tuple(Tuple tuple){
        std::ostringstream os;
        for (int i = 0; i < tuple.body_size(); i++) {
                if (tuple.body(i).has_string_pair_content()){
                        os << tuple.body(i).string_pair_content().key() << ",";
                        continue;
                }
                if (tuple.body(i).has_int_pair_content()){
                        os << tuple.body(i).int_pair_content().key() << ",";
                        continue;
                }
                if (tuple.body(i).has_double_pair_content()){
                        os << tuple.body(i).double_pair_content().key() << ",";
                        continue;
                }
                if (tuple.body(i).has_bool_pair_content()){
                        os << tuple.body(i).bool_pair_content().key() << ",";
                        continue;
                }
                if (tuple.body(i).has_null_pair_content()){
                        os << tuple.body(i).null_pair_content().key() << ",";
                        continue;
                }
        }
        return os.str();
}



std::string csv_tuple_from_tuple(Tuple tuple){
        std::ostringstream os;
        for (int i = 0; i < tuple.body_size(); i++) {
                if (tuple.body(i).has_string_pair_content()){
                        os << tuple.body(i).string_pair_content().value() << ",";
                        continue;
                }
                if (tuple.body(i).has_int_pair_content()){
                        os << tuple.body(i).int_pair_content().value() << ",";
                        continue;
                }
                if (tuple.body(i).has_double_pair_content()){
                        os << tuple.body(i).double_pair_content().value() << ",";
                        continue;
                }
                if (tuple.body(i).has_bool_pair_content()){
                        os << tuple.body(i).bool_pair_content().value() << ",";
                        continue;
                }
                if (tuple.body(i).has_null_pair_content()){
                        os << tuple.body(i).null_pair_content().value() << ",";
                        continue;
                }
        }
        return os.str();
}

void decode(BlockingReaderWriterQueue<Tuple> &in, std::ostream &out) {
        Tuple t;
        in.wait_dequeue(t);
        out << csv_header_from_tuple(t) << std::endl;
        while (true){
                in.wait_dequeue(t);
                if (t.poison()) break;
                out << csv_tuple_from_tuple(t) << std::endl;
        }
}

#include <queue>
#include <sstream> 
#include <string>
#include "libcsv/csv.h"
#include "pirf/pirf.pb.h"




std::string csv_header_from_tuple(Tuple tuple){
        std::ostringstream os;
        for (int i = 0; i < tuple.body_size(); i++) {
                if (tuple.body(i).has_string_pair_content()){
                        os << tuple.body(i).string_pair_content().key() << ",";

                }
        }
        os << "hello";
        return os.str();
}

void decode(std::queue<Tuple> &in, std::ostream &out) {
        out << in.front().DebugString() << std::endl;
        out << csv_header_from_tuple(in.front()) << "moo" << std::endl;
}

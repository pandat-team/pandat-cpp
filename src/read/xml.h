#include <iostream> 
#include <string>
#include "rapidxml/rapidxml.hpp"
#include "pirf/pirf.pb.h"
using namespace rapidxml;

Tuple encode(){
        char text[] = "<a></a>";
        xml_document<> doc;    // character type defaults to char
        doc.parse<parse_fastest>(text);    // 0 means default parse flags
        xml_node<> *node = doc.first_node("a");
        std::cout << node->value() << std::endl;
        for (xml_attribute<> *attr = node->first_attribute();
                        attr; attr = attr->next_attribute())
        {
                std::cout << "Node foobar has attribute " << attr->name() << " ";
                std::cout << "with value " << attr->value() << "\n";
        }
        Tuple t;
        return t;
}

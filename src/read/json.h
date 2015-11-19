#include <queue>
#include "rapidjson/document.h"
#include "pirf/pirf.pb.h"

using namespace rapidjson;

template <typename ARRAY>
void encode_array(ARRAY *array, Tuple::Body::ArrayPair::Array *dest_array);

template <typename JSON>
void encode_tuple(JSON *document, Tuple *tuple){

        for (Value::ConstMemberIterator itr = document->MemberBegin();
                        itr != document->MemberEnd(); ++itr)
        {
                Tuple::Body *body_ptr = tuple->add_body();
                const char* name = itr->name.GetString();
                switch(itr->value.GetType()){
                        case kNullType:
                                {  
                                        Tuple::Body::NullPair *pair = body_ptr->mutable_null_pair_content();
                                        pair->set_key(name);
                                        break;
                                }
                        case kFalseType:
                                {  
                                        Tuple::Body::BoolPair *pair = body_ptr->mutable_bool_pair_content();
                                        pair->set_key(name);
                                        pair->set_value(false);
                                        break;
                                }
                        case kTrueType:
                                {  
                                        Tuple::Body::BoolPair *pair = body_ptr->mutable_bool_pair_content();
                                        pair->set_key(name);
                                        pair->set_value(true);
                                        break;
                                }
                        case kObjectType:
                                {  
                                        Tuple::Body::TuplePair *pair = body_ptr->mutable_tuple_pair_content();
                                        pair->set_key(name);
                                        encode_tuple(&itr->value,pair->mutable_value());
                                        break;
                                }
                        case kArrayType:
                                {
                                        Tuple::Body::ArrayPair *pair = body_ptr->mutable_array_pair_content();
                                        pair->set_key(name);
                                        Tuple::Body::ArrayPair::Array *array = pair->mutable_value();
                                        encode_array(&itr->value,array);
                                        break;
                                }
                        case kStringType:
                                {
                                        Tuple::Body::StringPair *pair = body_ptr->mutable_string_pair_content();
                                        pair->set_key(name);
                                        pair->set_value(itr->value.GetString());
                                        break;
                                }
                        case kNumberType:
                                if (itr->value.IsInt())
                                {
                                        Tuple::Body::IntPair *pair = body_ptr->mutable_int_pair_content();
                                        pair->set_key(name);
                                        pair->set_value(itr->value.GetInt());
                                        break;
                                }
                                if (itr->value.IsDouble())
                                {
                                        Tuple::Body::DoublePair *pair = body_ptr->mutable_double_pair_content();
                                        pair->set_key(name);
                                        pair->set_value(itr->value.GetDouble());
                                        break;
                                }


                }
        }

}

template <typename ARRAY>
void encode_array(ARRAY *array, Tuple::Body::ArrayPair::Array *dest_array){
        for (Value::ConstValueIterator itr = array->Begin(); itr != array->End(); ++itr) {
                Tuple::Body::ArrayPair::Array::Element *element = dest_array->add_element();
                switch (itr->GetType()){
                        case kNullType:
                                {
                                        element->set_null_content(Tuple::Body::NULL_VALUE);
                                        break;
                                }
                        case kFalseType:
                                {
                                        element->set_bool_content(false);
                                        break;
                                }
                        case kTrueType:
                                {
                                        element->set_bool_content(true);
                                        break;
                                }
                        case kObjectType:
                                {
                                        Tuple *tuple = element->mutable_tuple_content();
                                        encode_tuple(itr,tuple);
                                        break;
                                }
                        case kArrayType:
                                {

                                        Tuple::Body::ArrayPair::Array *array = element->mutable_array_content();
                                        encode_array(itr,array);
                                        break;
                                }
                        case kStringType:
                                {
                                        element->set_string_content(itr->GetString());
                                        break;
                                }
                        case kNumberType:
                                {
                                        if (itr->IsInt())
                                        {
                                                element->set_int_content(itr->GetInt());
                                                break;
                                        }
                                        if (itr->IsDouble())
                                        {
                                                element->set_double_content(itr->GetDouble());
                                                break;
                                        }
                                        break;
                                }

                }
        }

}

void encode(std::istream &in, std::queue<Tuple> &out) {
        Document document;
        Tuple tuple;
        for (std::string line; std::getline(in, line);) {
                document.Parse(line.c_str());
                encode_tuple(&document, &tuple);
                out.push(tuple);
                tuple.Clear();
        }
}

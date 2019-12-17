//
// Created by me on 2019-12-17.
//

#ifndef MSGPAKC_EXAMPLES_HEADER_H
#define MSGPAKC_EXAMPLES_HEADER_H

#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "msgpack-c/include/msgpack.hpp"
#include "msgpack-c/include/msgpack/fbuffer.hpp"

std::map<msgpack::type::object_type, std::string> typeMap{
        {msgpack::type::object_type::NIL, "NIL"},
        {msgpack::type::object_type::BOOLEAN, "BOOLEAN"},
        {msgpack::type::object_type::POSITIVE_INTEGER, "POSITIVE_INTEGER"},
        {msgpack::type::object_type::NEGATIVE_INTEGER, "NEGATIVE_INTEGER"},
        {msgpack::type::object_type::FLOAT32, "FLOAT32"},
        {msgpack::type::object_type::FLOAT64, "FLOAT64"},
        {msgpack::type::object_type::FLOAT, "FLOAT"},
        {msgpack::type::object_type::STR, "STR"},
        {msgpack::type::object_type::BIN, "BIN"},
        {msgpack::type::object_type::ARRAY, "ARRAY"},
        {msgpack::type::object_type::MAP, "MAP"},
        {msgpack::type::object_type::EXT, "EXT"},
};

void printout(msgpack::unpacker &unpacker){
    // generic object handler:
    msgpack::object_handle _oh;
    // loop through data in the unpacker and place it into object handle
    while(unpacker.next(_oh)) {
        // instantiate msgpack object:
        auto mpk_obj = _oh.get();
        // do work on object.
        if (mpk_obj.type != msgpack::v1::type::NIL){
            if (mpk_obj.type == msgpack::v1::type::MAP){
                std::cout << "Map Object:\n";
                // taken from msgpack impl...
                msgpack::object_kv* p(mpk_obj.via.map.ptr);
                msgpack::object_kv* const pend(mpk_obj.via.map.ptr + mpk_obj.via.map.size);
                for (; p != pend; ++p) {
                    // as msgpack objects:
                    auto _k = p->key;
                    auto _v = p->val;
                    // TODO: add explicit conversion to target type.
                    std::cout <<"\tKey: " << _k << ",\t type: " << typeMap[_k.type] << ",\tvalue: " << _v << ",\ttype: " << typeMap[_v.type] << "\n";
                }
            }else
                std::cout << "Item: " << mpk_obj << ", \t type: " << typeMap[mpk_obj.type] << "\n";
        }
    }
}




#endif //MSGPAKC_EXAMPLES_HEADER_H

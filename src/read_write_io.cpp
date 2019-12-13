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
                std::cout <<"\tKey: " << mpk_obj.via.map.ptr->key << ",\t type: " << typeMap[mpk_obj.via.map.ptr->key.type] << "\n";
                std::cout <<"\tVal: " << mpk_obj.via.map.ptr->val << ",\t type: " << typeMap[mpk_obj.via.map.ptr->val.type] << "\n";
                // TODO: what is the best way to extract?
            }else
                std::cout << "Item: " << mpk_obj << ", \t type: " << typeMap[mpk_obj.type] << "\n";
        }
    }
}

void file_rw(){
    /*
    *
    * */
    printf("File Write / Read example\n");
    // Create File Stream:
    FILE* file_rw;
    file_rw = fopen("mypackfile_rw.mpk", "wb");
    // Create msgpack file buffer
    msgpack::fbuffer fileBuffer_rw(file_rw);  // file buffer
    // create a key-value pair packer linked to file-buffer
    msgpack::packer<msgpack::fbuffer> packer(&fileBuffer_rw);
    // create key-value map definition, n = number of items in map...
    packer.pack_map(1);                                 // MESSAGE 1
    // Populate:
    // key
    packer.pack(std::string("x"));                      // MESSAGE 1
    // value
    packer.pack(3);                                     // MESSAGE 1
    // pack as binary with length l, first set lenght:
    packer.pack_bin(10);                                // MESSAGE 2
    // set data as char array:
    packer.pack_bin_body("abcdefghij", 10);             // MESSAGE 2
    // key value with binary...
    packer.pack_map(1);                                 // MESSAGE 3
    // key:
    packer.pack("binary_item");                         // MESSAGE 3
    // pack as binary with length l, first set lenght:
    packer.pack_bin(10);                                // MESSAGE 3
    // set data as char array:
    packer.pack_bin_body("abcdefghij", 10);             // MESSAGE 3

    // Write out:
    fclose(file_rw);
    // Load:
    // create input filestream:
    std::ifstream in_file_rw("mypackfile_rw.mpk", std::ifstream::in);
    std::stringstream in_fileBuffer_rw;
    // read file into stringstream buffer:
    in_fileBuffer_rw << in_file_rw.rdbuf();

    // deserializes these objects using msgpack::unpacker.
    msgpack::unpacker unpacker;

    // feeds the buffer.
    unpacker.reserve_buffer(in_fileBuffer_rw.str().size());
    memcpy(unpacker.buffer(), in_fileBuffer_rw.str().data(), in_fileBuffer_rw.str().size());
    unpacker.buffer_consumed(in_fileBuffer_rw.str().size());
    unpacker.data(); // still NIL
    // now starts streaming deserialization.
    printout(unpacker);

}

void stream_rw(){
    /*
    *
    * */
    printf("Stream Write / Read example\n");
    // Create msgpack stream buffer object
    msgpack::sbuffer streamBuffer;  // file buffer
    // create a key-value pair packer linked to file-buffer
    msgpack::packer<msgpack::sbuffer> packer(&streamBuffer);
    // create key-value map definition, n = number of items in map...
    packer.pack_map(1);                                         // MESSAGE 1
    // Populate:
    // key
    packer.pack(std::string("x"));                              // MESSAGE 1
    // value
    packer.pack(3);                                             // MESSAGE 1
    // pack as binary with length l, first set lenght:
    packer.pack_bin(10);                                        // MESSAGE 2
    // set data as char array:
    packer.pack_bin_body("abcdefghij", 10);                     // MESSAGE 2
    // key value with binary...
    packer.pack_map(1);                                         // MESSAGE 3
    // key:
    packer.pack("binary_item");                                 // MESSAGE 3
    // pack as binary with length l, first set lenght:
    packer.pack_bin(10);                                        // MESSAGE 3
    // set data as char array:
    packer.pack_bin_body("abcdefghij", 10);                     // MESSAGE 3

    // deserializes these objects using msgpack::unpacker.
    msgpack::unpacker unpacker;

    // feeds the buffer.
    unpacker.reserve_buffer(streamBuffer.size());
    memcpy(unpacker.buffer(), streamBuffer.data(), streamBuffer.size());
    unpacker.buffer_consumed(streamBuffer.size());
    unpacker.data(); // still NIL
    // now starts streaming deserialization.
    // now starts streaming deserialization.
    printout(unpacker);
}

int main(int argc, char *argv[]) {

    // file read/write example:
    file_rw();

    //stream read/write example:
    stream_rw();


    return 0;
}

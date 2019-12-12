//
//

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


class mpacker{
public:
    FILE *file{};
    char fname_base[256]{};
    char fname[256]{};
    msgpack::fbuffer *fileBuffer=nullptr;
    msgpack::packer<msgpack::fbuffer> *packer=nullptr;

    mpacker()= default;
    ~mpacker()= default;

    void close_file(){
        if (file != nullptr) {	//file opened
            fflush(file);
            fclose(file);
        }
    }

    void open(std::string& fileName){
        time_t now = time(nullptr);
        sprintf(fname_base, "%s.mpk", fileName.c_str());

        sprintf(fname, "%s.active", fname_base);
        file = fopen(fname, "wb");

        fileBuffer = new msgpack::fbuffer(file);
        packer = new msgpack::packer<msgpack::fbuffer>(fileBuffer);
    }

    void open(char * cfileName){
        std::string fileName(cfileName);
        open(fileName);
    }

};


int main(int argc, char *argv[]) {

    mpacker myPacker;

    myPacker.open("test01");

    myPacker.packer->pack(10);
    myPacker.packer->pack("blah");
    myPacker.packer->pack_map(1);
    // Populate:
    // key
    myPacker.packer->pack(std::string("x"));
    // value
    myPacker.packer->pack(3);
    // pack as binary with length l, first set lenght:
    myPacker.packer->pack_bin(10);
    // set data as char array:
    myPacker.packer->pack_bin_body("abcdefghij", 10);
    // key value with binary...
    myPacker.packer->pack_map(1);
    // key:
    myPacker.packer->pack("binary_item");
    // pack as binary with length l, first set lenght:
    myPacker.packer->pack_bin(10);
    // set data as char array:
    myPacker.packer->pack_bin_body("abcdefghij", 10);


    myPacker.close_file();

    myPacker.open("test02");

    myPacker.packer->pack(20);
    myPacker.packer->pack("blah");
    myPacker.packer->pack_map(1);
    // Populate:
    // key
    myPacker.packer->pack(std::string("y"));
    // value
    myPacker.packer->pack(12.5);
    // pack as binary with length l, first set lenght:
    myPacker.packer->pack_bin(10);
    // set data as char array:
    myPacker.packer->pack_bin_body("kajsdhfkah", 10);
    // key value with binary...
    myPacker.packer->pack_map(1);
    // key:
    myPacker.packer->pack("myItem");
    // pack as binary with length l, first set lenght:
    myPacker.packer->pack_bin(10);
    // set data as char array:
    myPacker.packer->pack_bin_body("kajsdhfkah", 10);

    myPacker.close_file();

    return 0;
}

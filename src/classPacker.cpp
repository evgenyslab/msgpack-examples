//
//

#include "header.h"

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

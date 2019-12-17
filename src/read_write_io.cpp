#include "header.h"

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
    packer.pack_map(1);
    // Populate:
    // key
    packer.pack(std::string("x"));
    // value
    packer.pack(3);
    // pack as binary with length l, first set lenght:
    packer.pack_bin(10);
    // set data as char array:
    packer.pack_bin_body("abcdefghij", 10);
    // key value with binary...
    packer.pack_map(2);
    // key:
    packer.pack("binary_item");
    // pack as binary with length l, first set lenght:
    packer.pack_bin(10);
    // set data as char array:
    packer.pack_bin_body("abcdefghij", 10);
    // key:
    packer.pack("second_item");
    packer.pack("hello_there");

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
    msgpack::sbuffer streamBuffer;  // stream buffer
    // create a key-value pair packer linked to stream-buffer
    msgpack::packer<msgpack::sbuffer> packer(&streamBuffer);
    // create key-value map definition, n = number of items in map...
    packer.pack_map(1);
    // Populate:
    // key
    packer.pack(std::string("x"));
    // value
    packer.pack(3);
    // pack as binary with length l, first set lenght:
    packer.pack_bin(10);
    // set data as char array:
    packer.pack_bin_body("abcdefghij", 10);
    // key value with binary...
    packer.pack_map(1);
    // key:
    packer.pack("binary_item");
    // pack as binary with length l, first set lenght:
    packer.pack_bin(10);
    // set data as char array:
    packer.pack_bin_body("abcdefghij", 10);


    // deserializes these objects using msgpack::unpacker.
    msgpack::unpacker unpacker;

    // feeds the buffer.
    unpacker.reserve_buffer(streamBuffer.size());
    memcpy(unpacker.buffer(), streamBuffer.data(), streamBuffer.size());
    unpacker.buffer_consumed(streamBuffer.size());
    unpacker.data(); // still NIL
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

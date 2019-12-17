#include "header.h"


int main(int argc, char *argv[]) {

    msgpack::sbuffer streamBuffer;  // stream buffer
    // create a key-value pair packer linked to stream-buffer
    msgpack::packer<msgpack::sbuffer> spacker(&streamBuffer);

    spacker.pack(1);
    spacker.pack_map(4);
    spacker.pack("key_01");
    spacker.pack("val_01");
    spacker.pack("key_02");
    spacker.pack("val_02");
    spacker.pack("key_03");
    spacker.pack("val_03");
    spacker.pack("key_04");
    spacker.pack(4.51);
    spacker.pack(10);

    FILE* file_rw;
    file_rw = fopen("mypackfilefromstream.mpk", "wb");
    // Create msgpack file buffer
    msgpack::fbuffer fileBuffer_rw(file_rw);  // file buffer
    // create a key-value pair packer linked to file-buffer
    msgpack::packer<msgpack::fbuffer> fpacker(&fileBuffer_rw);
    // copy stream buffer to file-based buffer for write out:
    fileBuffer_rw.write(streamBuffer.data(), streamBuffer.size());
    // add more data:
    fpacker.pack_map(3);
    fpacker.pack("key_05");
    fpacker.pack("val_05");
    fpacker.pack("key_06");
    fpacker.pack("val_06");
    fpacker.pack("key_07");
    fpacker.pack(100);


    // Write out:
    fclose(file_rw);
    // Load:
    // create input filestream:
    std::ifstream in_file_rw("mypackfilefromstream.mpk", std::ifstream::in);
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


    return 0;
}
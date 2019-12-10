#include <fstream>
#include <iostream>
#include "msgpack-c/include/msgpack.hpp"
#include "msgpack-c/include/msgpack/fbuffer.hpp"
#include <string>
#include <sstream>

int main(int argc, char *argv[]) {



    // Write with fstream:
    FILE* fp;
    fp = fopen("mypackfile.mpk", "wb");
    msgpack::fbuffer fbuf(fp);  // file buffer



    // serializes this object.
    std::vector<std::string> vec;
    vec.emplace_back("Hello");
    vec.emplace_back("MessagePack");
    // pack vector:
    msgpack::pack(&fbuf, vec);
    // add stuff...


    // close file..
    fclose(fp);

    std::ifstream ifs("mypackfile.mpk", std::ifstream::in);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    msgpack::unpacked upd;
    msgpack::unpack(upd, buffer.str().data(), buffer.str().size());
    std::cout << upd.get() << std::endl;


    // msgpack serialized example:
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, vec);

    // deserialize it.
    msgpack::object_handle oh =
            msgpack::unpack(sbuf.data(), sbuf.size());

    // print the deserialized object.
    msgpack::object obj = oh.get();
    std::cout << obj << std::endl;  //=> ["Hello", "MessagePack"]

    // convert it into statically typed object.
    std::vector<std::string> rvec;
    obj.convert(rvec);
    return 0;
}

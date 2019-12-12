#!usr/bin/python3
"""
Basic msgpack reading into array or dictionary
"""

import msgpack

# open msgpack file:
f = open("/home/rtuser/dev/private/msgpack-examples/cmake-build-debug/mypackfile_rw.mpk", "rb")
# use max_bin_length=val or max_array_length=val to circumvent internal
# create unpacker object:
pk = msgpack.Unpacker(f)
# parse each message into data array:
msgs = [i for i in pk]
# close the file
f.close()
# process data here...



# Alternative using with operator
with open("filepath", "rb") as file:
    pk = msgpack.Unpacker(file)
    for _item in pk:
        # do work on _item
        pass

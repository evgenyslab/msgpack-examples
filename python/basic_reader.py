#!usr/bin/python3
"""
Basic msgpack reading into array or dictionary
"""

import msgpack

# open msgpack file:
fileName = "/home/rtuser/dev/private/msgpack-examples/cmake-build-debug/test02.mpk.active"
f = open(fileName, "rb")
# use max_bin_length=val or max_array_length=val to circumvent internal
# create unpacker object:
pk = msgpack.Unpacker(f)
# parse each message into data array:
msgs = [i for i in pk]
# close the file
f.close()
# process data here...



# Alternative using with operator
with open(fileName, "rb") as file:
    pk = msgpack.Unpacker(file)
    msgs = [i for i in pk]


# Alternative using with operator
with open(fileName, "rb") as file:
    pk = msgpack.Unpacker(file)
    for _item in pk:
        # do work on _item
        pass
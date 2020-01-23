#!usr/bin/python3
"""
Basic msgpack reading into array or dictionary

Some notes:

Writing msgpack files with c++ or python and reading back in python
yeilds the same results.

Strings written to file will be read with "b'" bytes literal, that need to be converted
to appropriate output.

Numbers are loaded correctly and do not need to be converted from bytes literal.

One aspect to note, image data is generally recorded as a string/char array, and will therefore
be written as a byte literal; however converting to string may result in problems when using
the python built-in UTF-8 decoder due to random character escape keys.
"""

import msgpack
import numpy as np

# open msgpack file:
fileName = "/home/en/git/private/msgpack-examples/cmake-build-debug/test01.mpk.active"
f = open(fileName, "rb")
# use max_bin_length=val or max_array_length=val to circumvent internal
# create unpacker object:
pk = msgpack.Unpacker(f)
# unpacker is a generator, can call next() on it:
next_msg = next(pk)
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

# Pack some data
# packing a key-value pair adds 10 Bytes per char
data = {}
for k in range(10):
    data["keasdfadsfa{:d}".format(k)] = np.random.rand()

keys = [k for k in data]
datar = [data[k] for k in data]

_p = str(msgpack.packb(data))

# Write msgpack file
with open('data.msgpack', 'wb') as outfile:
    msgpack.pack(data, outfile)
    msgpack.pack(data, outfile)
    msgpack.pack(data, outfile)

with open('datar.msgpack', 'wb') as outfile:
    msgpack.pack(keys, outfile)
    msgpack.pack(datar, outfile)
    msgpack.pack(datar, outfile)

# Read msgpack file
with open(fileName, 'rb') as data_file:
    unpacker = msgpack.Unpacker(data_file)
    data_loaded = []
    for m in unpacker:
        data_loaded.append(m)

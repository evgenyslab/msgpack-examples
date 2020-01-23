# msgpack-examples
A repository of usefull C++/Python msgpack examples

# Getting Message Pack

run:

```bash
git submodule update --init --recursive
```

# Examples to do:

## C++

### Read and Write IO

- create sbuffer message pack, unpack and print
- create fbuffer message pack, save to file, load file, print

### Simple Buffer to File Buffer

- an interesting example of a local pack object whose data is trasferred to
a file buffer pack object, written out.
- can be useful for creating re-usable pack objects such as headers for
larger pack files.

## Python
# Bit Packed Suffix Array for Transcriptome Mapping
[https://bitbucket.org/daljeet_chhabra/rapmappacked.git]

This project entails programming a suffix array using binary encoding and the performance results of the same. This project is built on top of RapMap[https://github.com/COMBINE-lab/RapMap] and Libdivsufsort[https://github.com/y-256/libdivsufsort]. 

# Building the project

NOTE: Please checkout the BitPacked branch before running the code.

```
> git checkout BitPacked
```

RapMap is used as a wrapper to provide input and parse the arguments for suffix array library. RapMap binary is the main binary that must be built and executed to use the suffix array implementation. To build RapMap, you need a C++11 compliant compiler (g++ >= 4.7 and clang >= 3.4) and CMake.  RapMap is built with the following steps (assuming that `path_to_rapmap` is the toplevel directory where you have cloned this repository):

```
[path_to_rapmap] > mkdir build && cd build
[path_to_rapmap/build] > cmake ..
[path_to_rapmap/build] > make
[path_to_rapmap/build] > make install
[path_to_rapmap/build] > cd ../bin
[path_to_rapmap/bin] > ./rapmap -h
```
This should output the standard help message for rapmap.

# Using RapMap

To use RapMap to map reads, you first have to index your reference transcriptome.  Once the index is created, it can be used to map many different sets of reads.  Assuming that your reference transcriptome is in the file `ref.fa`, you can produce the index as follows:

```
> rapmap index -t ref.fa -i ref_index
```

The index itself will record whether it was built with the aid of compressed transcriptome or not, so no extra information concerning this need be provided when mapping. We can search the bit packed suffix array as follows :-

```
> rapmap map -i ref_index -p path_to_pattern_file
```

The pattern file is a plain text file containing new-line delimited patterns. The map command will print the transcript names and the index within the transcript where the match occurs.


# External dependencies

[tclap](http://tclap.sourceforge.net/)

[cereal](https://github.com/USCiLab/cereal)

[jellyfish](https://github.com/gmarcais/Jellyfish)


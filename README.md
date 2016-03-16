<!-- To read with Atom go to >Packages>Mardown Preview -->

### Projet 1 - Implementation of `malloc`, `calloc`, and `free`

For our course
[Systèmes Informatiques I](https://sites.uclouvain.be/SystInfo/), we had to
implement our own, simplified, versions of `malloc`, `calloc` et `free`, that
we will call `mymalloc`, `mycalloc` et `myfree`.

#### Usage

To modify the initial heap size go to line `#12` in file `./header.h`.

How to compile?

`$ make`

How to execute?

`$ ./exec`

How to clean?

`$ make clean`

#### Structure

Files without a comment have a descriptive name to understand what
they contain :

* `./header.h` contains the header used in each .c file
* `./LICENSE`
* `./Makefile`
* `./mycalloc.c`
* `./myfree.c`
* `./mymalloc.c`
* `./rapport.pdf`
* `./README.md`
* `./tests.c`

#### Known Issues

`./mymalloc.c` does not pass our `test_mymalloc_2` unit test. See document
`./rapport.pdf`.

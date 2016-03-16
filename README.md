<!-- To read with Atom go to >Packages>Mardown Preview -->

### Projet 1 - Implementation of `malloc`, `calloc`, and `free`

For our course
[Systèmes Informatiques I](https://sites.uclouvain.be/SystInfo/), we had to
implement our own, simplified, versions of `malloc`, `calloc` et `free`, that
we will call `mymalloc`, `mycalloc` et `myfree`.

#### Usage

To modify the initial heap size go to line `#12` in file `./header.h`

How to compile?

`$ make`

How to execute?

`$ ./exec`

How to clean?

`$ make clean`

#### Structure

Files without comments have a sufficient explicit name to understand what
they contain :

* `./header.c` contains the header used in each .c file
* `./LICENSE`
* `./Makefile`
* `./mycalloc.c`
* `./myfree.c`
* `./mymalloc.c`
* `./tests.c`

<!-- ### Known Issues -->

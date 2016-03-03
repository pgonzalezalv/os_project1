<!-- To read with Atom go to >Packages>Mardown Preview -->

# Projet 1 - Implémentation de `malloc` et `free`

Dans le cadre de notre cours des
[Systèmes Informatiques I](https://sites.uclouvain.be/SystInfo/),
nous devons implémenter notre propre version, simplifiée,
de  `malloc` et `free`, que nous appellerons `mymalloc` et `myfree`.
L'implémentation devra satisfaire les contraintes suivantes:

* **Séquences d’appels arbitraires.** Un programme qui utilise votre
implémentation peut effectuer des appels a `malloc`/`free` n’importe quand, et
dans n’importe quel ordre.
* **Réponse immédiate:** Votre implémentation doit répondre immédiatement aux
requêtes qui lui sont effectuées. Par exemple, il est interdit de réordonner
ou placer les requêtes dans un buffer.
* **Seul le heap doit etre utilisé.** Les structures contenant les
informations sur les blocs de memoire alloués doivent également se trouver
sur le heap.
* **Alignement**. Les blocs de memoire que votre implémentation alloue doivent
être alignés sur 32 bits (cela signifie notamment que le pointeur que
`mymalloc` retourne doit etre un multiple de 4).
* **Ne pas modifier les blocs alloués.** Il est interdit de modifier ou de
déplacer des blocs déjà alloués. Seuls les blocs libres peuvent être manipulés.

<!-- ### Compilation -->


### Arborescence

Les fichiers sans commentaires ont un nom suffisamment explicite pour savoir
ce qu'ils contiennent.

* `./header.h`
* `./main.c`
* `./MAKEFILE`
* `./myfree.c`
* `./mymalloc.c`

<!-- ### Known Issues -->

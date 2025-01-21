
#ifndef BITSET_H
    #define BITSET_H
    #include <stdio.h>
    #include <stdlib.h>
    #define ERR "allocation error"
    #define ERR1 "error, bad operator"

    typedef struct Bitset {
        size_t size;
        int *array;
    } Bitset;


    Bitset* create_bitset(size_t);
    Bitset* create_bitset_with_values(size_t, const int *, size_t);
    Bitset* create_bitset_with_range(size_t, int);
    void set_insert(Bitset *, int);
    void set_remove(Bitset *, int);
    int contains(Bitset *, int);
    void form_intersection(Bitset *, Bitset *);
    Bitset* set_intersection(Bitset *, Bitset *);
    void form_union(Bitset *, Bitset *);
    Bitset* set_union(Bitset *, Bitset *);
    void form_difference(Bitset *, Bitset *);
    Bitset* set_difference(Bitset *, Bitset *);
    int is_subset(Bitset *, Bitset *);
    int save_bitsets_to_file(char *, Bitset **, size_t);
    Bitset** load_bitsets(char *);
    Bitset** load_bitsets_if(int (*)(Bitset*), char *);

#endif
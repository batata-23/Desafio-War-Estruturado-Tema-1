#ifndef TERRITORIO_H
#define TERRITORIO_H

#include <stdbool.h>

typedef struct Territory {
    int id;
    char *name;
    char *color;
    int troops;
    int *neighbors; // array of neighbor ids
    int n_neighbors;
    int owner; // player id (not used extensively here)
} Territory;

Territory* create_territory(int id, const char* name, const char* color, int troops);
void free_territory(Territory *t);
void add_neighbor(Territory *t, int neighbor_id);
void print_territory(const Territory *t);

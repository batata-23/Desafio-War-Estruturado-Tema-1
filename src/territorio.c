#include "territorio.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Territory* create_territory(int id, const char* name, const char* color, int troops) {
    Territory *t = (Territory*) malloc(sizeof(Territory));
    if (!t) return NULL;
    t->id = id;
    t->name = strdup(name);
    t->color = strdup(color);
    t->troops = troops;
    t->neighbors = NULL;
    t->n_neighbors = 0;
    t->owner = -1;
    return t;
}

void free_territory(Territory *t) {
    if (!t) return;
    if (t->name) free(t->name);
    if (t->color) free(t->color);
    if (t->neighbors) free(t->neighbors);
    free(t);
}

void add_neighbor(Territory *t, int neighbor_id) {
    if (!t) return;
    int n = t->n_neighbors;
    int *arr = (int*) realloc(t->neighbors, sizeof(int)*(n+1));
    if (!arr) return;
    arr[n] = neighbor_id;
    t->neighbors = arr;
    t->n_neighbors = n+1;
}

void print_territory(const Territory *t) {
    if (!t) return;
    printf("ID: %d | %s | Cor: %s | Tropas: %d | Vizinhos:", t->id, t->name, t->color, t->troops);
    for (int i=0;i<t->n_neighbors;i++) {
        printf(" %d", t->neighbors[i]);
        if (i+1 < t->n_neighbors) printf(",");
    }
    printf("\n");
}

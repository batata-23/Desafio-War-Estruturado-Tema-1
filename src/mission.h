#ifndef MISSION_H
#define MISSION_H

#include "territorio.h"

typedef struct Mission {
    char *description;
    // For simplicity, mission is to control list of territory ids
    int *must_control_ids;
    int n_ids;
} Mission;

Mission* create_mission(const char *description, const int *ids, int n);
void free_mission(Mission *m);
int check_mission(const Mission *m, Territory **map, int map_n);


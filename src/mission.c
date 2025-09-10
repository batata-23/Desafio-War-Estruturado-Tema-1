#include "mission.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Mission* create_mission(const char *description, const int *ids, int n) {
    Mission *m = (Mission*) malloc(sizeof(Mission));
    if (!m) return NULL;
    m->description = strdup(description);
    m->n_ids = n;
    if (n>0) {
        m->must_control_ids = (int*) malloc(sizeof(int)*n);
        for (int i=0;i<n;i++) m->must_control_ids[i] = ids[i];
    } else m->must_control_ids = NULL;
    return m;
}

void free_mission(Mission *m) {
    if (!m) return;
    if (m->description) free(m->description);
    if (m->must_control_ids) free(m->must_control_ids);
    free(m);
}

// check if all territories in must_control_ids have owner == 0 (player 0)
// For this educational project we check troops > 0 and owner == 0
int check_mission(const Mission *m, Territory **map, int map_n) {
    int ok = 1;
    for (int i=0;i<m->n_ids;i++) {
        int id = m->must_control_ids[i];
        int found = 0;
        for (int j=0;j<map_n;j++) {
            if (map[j] && map[j]->id == id) {
                found = 1;
                // requirement: owner == 0 (player 0) or troops > 0 and owner==0
                if (map[j]->owner != 0) ok = 0;
                break;
            }
        }
        if (!found) ok = 0;
    }
    return ok;
}

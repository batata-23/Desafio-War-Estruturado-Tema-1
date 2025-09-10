#ifndef ATTACK_H
#define ATTACK_H

#include "territorio.h"

typedef struct BattleResult {
    int attacker_losses;
    int defender_losses;
} BattleResult;

// Simula um ataque de attacker -> defender. Modifica tropas nos territórios.
// Retorna 0 se ataque não pôde ocorrer, 1 se ocorreu.
int attack(Territory *attacker, Territory *defender);

#endif

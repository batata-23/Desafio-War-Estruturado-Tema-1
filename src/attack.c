#include "attack.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// Helper: roll n dice, store sorted descending in arr (caller allocates arr[n])
static void roll_dice(int n, int *arr) {
    for (int i=0;i<n;i++) arr[i] = (rand() % 6) + 1;
    // simple sort descending
    for (int i=0;i<n-1;i++) for (int j=i+1;j<n;j++) if (arr[j] > arr[i]) {
        int tmp = arr[i]; arr[i]=arr[j]; arr[j]=tmp;
    }
}

int attack(Territory *attacker, Territory *defender) {
    if (!attacker || !defender) return 0;
    if (attacker->troops < 2) {
        printf("Ataque impossível: o território atacante precisa ter ao menos 2 tropas.\n");
        return 0;
    }
    // número de dados
    int ad = attacker->troops - 1;
    if (ad > 3) ad = 3;
    int dd = defender->troops;
    if (dd > 2) dd = 2;

    int *ar = (int*) malloc(sizeof(int)*ad);
    int *dr = (int*) malloc(sizeof(int)*dd);
    roll_dice(ad, ar);
    roll_dice(dd, dr);

    int comparisons = (ad < dd) ? ad : dd;
    int attacker_losses = 0;
    int defender_losses = 0;
    for (int i=0;i<comparisons;i++) {
        if (ar[i] > dr[i]) defender_losses++;
        else attacker_losses++;
    }

    attacker->troops -= attacker_losses;
    defender->troops -= defender_losses;

    printf("Resultado da batalha: atacante perdeu %d, defensor perdeu %d\n", attacker_losses, defender_losses);

    // se defensor ficou sem tropas, atacante pode mover tropas para ocupar
    if (defender->troops <= 0) {
        printf("Território %s foi tomado por quem atacou. Movendo tropas...\n", defender->name);
        // mover ao menos ad - attacker_losses (até maximum attacker->troops -1)
        int movable = attacker->troops - 1;
        if (movable < 1) movable = 1;
        defender->troops = movable;
        attacker->troops -= movable;
        printf("Movidos %d tropas para o território %s\n", movable, defender->name);
    }

    free(ar);
    free(dr);
    return 1;
}

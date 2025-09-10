#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "territorio.h"
#include "attack.h"
#include "mission.h"

#define MAX_MAP 256

// mapa simples guardando ponteiros para territórios
Territory* map_store[MAX_MAP];
int map_n = 0;

Territory* find_territory_by_id(int id) {
    for (int i=0;i<map_n;i++) if (map_store[i] && map_store[i]->id == id) return map_store[i];
    return NULL;
}

void add_territory_interactive() {
    char name[128], color[64];
    int troops;
    printf("Nome do território: ");
    if (!fgets(name, sizeof(name), stdin)) return;
    name[strcspn(name, "\n")] = 0;
    printf("Cor do território: ");
    if (!fgets(color, sizeof(color), stdin)) return;
    color[strcspn(color, "\n")] = 0;
    printf("Tropas iniciais (int): ");
    if (scanf("%d", &troops) != 1) { while(getchar()!='\n'); printf("Entrada inválida\n"); return; }
    while(getchar()!='\n');
    int id = (map_n==0)?1:(map_store[map_n-1]->id + 1);
    Territory *t = create_territory(id, name, color, troops);
    if (!t) { printf("Erro alocando território\n"); return; }
    // default owner 0 (player) for simplicity
    t->owner = 0;
    map_store[map_n++] = t;
    printf("Território criado com id %d\n", id);
}

void list_territories() {
    printf("--- Lista de territórios (%d) ---\n", map_n);
    for (int i=0;i<map_n;i++) {
        if (map_store[i]) print_territory(map_store[i]);
    }
}

void connect_territories() {
    int a,b;
    printf("ID do primeiro território: ");
    if (scanf("%d", &a) != 1) { while(getchar()!='\n'); return; }
    printf("ID do segundo território: ");
    if (scanf("%d", &b) != 1) { while(getchar()!='\n'); return; }
    while(getchar()!='\n');
    Territory *ta = find_territory_by_id(a);
    Territory *tb = find_territory_by_id(b);
    if (!ta || !tb) { printf("IDs inválidos\n"); return; }
    add_neighbor(ta, b);
    add_neighbor(tb, a);
    printf("Conectados %d <-> %d\n", a, b);
}

void do_attack_interactive() {
    int aid, did;
    printf("ID atacador: "); if (scanf("%d", &aid)!=1) { while(getchar()!='\n'); return; }
    printf("ID defensor: "); if (scanf("%d", &did)!=1) { while(getchar()!='\n'); return; }
    while(getchar()!='\n');
    Territory *att = find_territory_by_id(aid);
    Territory *def = find_territory_by_id(did);
    if (!att || !def) { printf("Território não encontrado\n"); return; }
    // checar vizinhança
    int adjacent = 0;
    for (int i=0;i<att->n_neighbors;i++) if (att->neighbors[i]==def->id) adjacent=1;
    if (!adjacent) { printf("Territórios não são vizinhos, ataque não permitido\n"); return; }
    attack(att, def);
}

void setup_sample_map() {
    // cria alguns territórios de exemplo e missões simples
    Territory *t1 = create_territory(1, "Brasil", "Amarelo", 5);
    Territory *t2 = create_territory(2, "Argentina", "Azul", 3);
    Territory *t3 = create_territory(3, "Colombia", "Verde", 4);
    Territory *t4 = create_territory(4, "Peru", "Vermelho", 2);
    t1->owner = 0; t2->owner = 1; t3->owner = 1; t4->owner = 0;
    add_neighbor(t1, 2); add_neighbor(t1,3);
    add_neighbor(t2,1); add_neighbor(t2,3); add_neighbor(t2,4);
    add_neighbor(t3,1); add_neighbor(t3,2);
    add_neighbor(t4,2);
    map_store[map_n++] = t1;
    map_store[map_n++] = t2;
    map_store[map_n++] = t3;
    map_store[map_n++] = t4;
}

int main_menu() {
    printf("\n=== War (versão educacional) ===\n");
    printf("1) Listar territórios\n");
    printf("2) Adicionar território\n");
    printf("3) Conectar territórios\n");
    printf("4) Atacar\n");
    printf("5) Checar missão de exemplo\
");
    printf("0) Sair\n");
    printf("Escolha: ");
    int opt;
    if (scanf("%d", &opt)!=1) { while(getchar()!='\n'); return -1; }
    while(getchar()!='\n');
    return opt;
}

int main(void) {
    srand((unsigned) time(NULL));
    setup_sample_map();

    // criar missão de exemplo: controlar Brasil (1) e Peru (4)
    int ids[] = {1,4};
    Mission *m = create_mission("Controlar Brasil e Peru", ids, 2);

    int opt;
    while(1) {
        opt = main_menu();
        if (opt == -1) { printf("Entrada inválida\n"); continue; }
        if (opt == 0) break;
        switch(opt) {
            case 1: list_territories(); break;
            case 2: add_territory_interactive(); break;
            case 3: connect_territories(); break;
            case 4: do_attack_interactive(); break;
            case 5:
                if (check_mission(m, map_store, map_n)) printf("Missão cumprida!\n");
                else printf("Missão não cumprida ainda.\n");
                break;
            default: printf("Opção inválida\n");
        }
    }

    // limpeza
    free_mission(m);
    for (int i=0;i<map_n;i++) if (map_store[i]) free_territory(map_store[i]);
    return 0;
}

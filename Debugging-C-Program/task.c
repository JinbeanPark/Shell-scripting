#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct player {
    char *name, *team;
};
typedef struct player Player;

int compare(const void *p, const void *q) {
    char *pname = ((Player *)p)->name;
    char *qname = ((Player *)q)->name;
    char *pteam = ((Player *)p)->team;
    char *qteam = ((Player *)q)->team;

    int retname = strcmp(pname, qname);
    int retteam = strcmp(pteam, qteam);

    return retteam != 0 ? retteam : retname ? 0 : retname;
}

void printInfo(Player *players, int size) {
    for (int i = 0; i < size; ++i) {
        printf("Name: %s, Team: %s\n", players[i].name, players[i].team);
    }
}

int main() {
    Player players[3]; //access attributes using player[index].attributename
    char names[3][10] = {
        "Joe",
        "Alice",
        "Bob"
    };
    char teams[3][10] = {
        "TeamRed",
        "TeamBlue",
        "TeamYellow"
    };

    for (int i = 0; i < 3; ++i) {
        players[i].name = malloc(20 * sizeof(char));
        sprintf(players[i].name, names[i]);
        players[i].team = malloc(20 * sizeof(char));
        sprintf(players[i].team, teams[i]);
    }

    printf("Before sort\n");
    printInfo(players, 3);

    qsort(players, 3, sizeof(Player), compare);

    printf("After sort\n");
    printInfo(players, 3);

    for (int i = 0; i < 3; ++i) {
        free(players[i].name);
        free(players[i].team);
    }

    return 0;
}

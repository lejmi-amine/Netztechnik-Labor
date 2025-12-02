#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graph.h"
#include "sptree.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Nutzung: %s <Graph-Datei>\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    if (getGraph(argv[1]) < 1) {
        printf("Fehler beim Einlesen!\n");
        return 1;
    }

    printf("Graph erfolgreich eingelesen (%d Knoten)\n", nodeCnt);

    initMatrix();
    run_simulation(10);  
    print_spanning_tree();

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "sptree.h"


void sptree_step(int index)
{
    node *n = &pnode[index];
    n->msgCnt++;

    int currentRoot = n->nodeID;
    int currentCost = 0;

    
    for (int k = 0; k < nodeCnt; k++) {
        if (pnode[k].plink[index].kosten == 0) continue;

        int angebotRoot = pnode[k].plink[index].rootID;
        int angebotKosten = pnode[k].plink[index].summeKosten +
                            pnode[k].plink[index].kosten;

        
        if (angebotRoot < currentRoot ||
           (angebotRoot == currentRoot && angebotKosten < currentCost))
        {
            currentRoot = angebotRoot;
            currentCost = angebotKosten;
            n->nextHop = k;
        }
    }

    
    n->nodeID = currentRoot;

    
    for (int k = 0; k < nodeCnt; k++) {
        if (n->plink[k].kosten > 0) {
            n->plink[k].rootID = currentRoot;
            n->plink[k].summeKosten = currentCost;
        }
    }
}


void run_simulation(int min_iterations)
{
    int total = min_iterations * nodeCnt;
    int count = 0;

    while (count < total) {
        int r = rand() % nodeCnt;
        sptree_step(r);
        count++;
    }
}


void print_spanning_tree()
{
    printf("\nSpanning-Tree {\n");
    printf("  Root: %d\n", pnode[0].nodeID);

    for (int i = 0; i < nodeCnt; i++) {
        if (i != pnode[i].nextHop)
            printf("  %s - %s\n",
                pnode[i].name, pnode[pnode[i].nextHop].name);
    }

    printf("}\n");
}

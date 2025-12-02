#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "graph.h"
#include "utils.h"

node *pnode = NULL;
int nodeCnt = 0;

static void addEdge(const char *left, const char *right, int kosten);

int getIndex(const char *name)
{
    for (int i = 0; i < nodeCnt; i++)
        if (strcmp(pnode[i].name, name) == 0)
            return i;

    return -1;
}

int appendNode(const char *name)
{
    pnode = realloc(pnode, (nodeCnt + 1) * sizeof(node));

    strcpy(pnode[nodeCnt].name, name);
    pnode[nodeCnt].nodeID = 0;
    pnode[nodeCnt].msgCnt = 0;
    pnode[nodeCnt].nextHop = nodeCnt;

    pnode[nodeCnt].plink = calloc(nodeCnt + 1, sizeof(link));

    for (int i = 0; i < nodeCnt; i++)
        pnode[i].plink = realloc(pnode[i].plink, (nodeCnt + 1) * sizeof(link));

    nodeCnt++;
    return nodeCnt - 1;
}

static void addEdge(const char *left, const char *right, int kosten)
{
    int a = getIndex(left);
    int b = getIndex(right);

    if (a == -1) a = appendNode(left);
    if (b == -1) b = appendNode(right);

    pnode[a].plink[b].kosten = kosten;
    pnode[b].plink[a].kosten = kosten;
}

void initMatrix()
{
    for (int i = 0; i < nodeCnt; i++) {
        pnode[i].nextHop = i;

        for (int k = 0; k < nodeCnt; k++) {
            if (pnode[i].plink[k].kosten > 0) {
                pnode[i].plink[k].rootID = pnode[i].nodeID;
                pnode[i].plink[k].summeKosten = 0;
            }
        }
    }
}

int getGraph(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Fehler: Datei '%s' konnte nicht geöffnet werden.\n", filename);
        return -1;
    }

    char line[256];

    while (fgets(line, sizeof(line), fp)) {

        trim(line);
        if (checkline(line)) continue;

        if (strchr(line, '=') != NULL) {

            char left[64];
            int id;

            if (sscanf(line, "%s = %d;", left, &id) == 2) {

                if (!isValid(left)) continue;

                int idx = getIndex(left);
                if (idx == -1) idx = appendNode(left);

                pnode[idx].nodeID = id;
            }

        } else if (strchr(line, '-') != NULL) {

            char a[64], b[64];
            int kosten;

            if (sscanf(line, "%s - %s : %d;", a, b, &kosten) == 3) {

                if (isValid(a) && isValid(b))
                    addEdge(a, b, kosten);
            }
        }
    }

    fclose(fp);
    return nodeCnt;
}

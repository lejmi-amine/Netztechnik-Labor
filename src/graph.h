#ifndef GRAPH_H
#define GRAPH_H

#define MAX_IDENT 32

typedef struct {
    int kosten;         
    int rootID;         
    int summeKosten;   
} link;

typedef struct {
    char name[MAX_IDENT];
    int nodeID;
    link *plink;        
    int nextHop;        
    int msgCnt;         
} node;

extern node *pnode;     
extern int nodeCnt;     

int getGraph(const char *filename);
int getIndex(const char *name);
int appendNode(const char *name);
void appendLink();
void initMatrix();
void printGraph();

#endif

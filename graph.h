#ifndef PROGRAMMINGLAB5_GRAPH_H
#define PROGRAMMINGLAB5_GRAPH_H

struct Graph {
    int **matrix;
    int nodes;
};

struct Graph *inputGraph(int nodes, int **matrix);

void graphPrinting(struct Graph *graph);

void addNode(struct Graph *graph);

void deleteNode(struct Graph *graph, int index);

void addEdge(struct Graph *graph, int from, int to, int weight);

void deleteEdge(struct Graph *graph, int from, int to);

void clearMemory(struct Graph *graph);

#endif

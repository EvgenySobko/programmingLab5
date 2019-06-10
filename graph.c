#include <stdbool.h>
#include "stdio.h"
#include "stdlib.h"

struct Graph {
    int **matrix;
    int nodes;
};

void graphPrinting(struct Graph *graph) {
    FILE *file = fopen("output.txt", "w");
    for (int i = 0; i < graph->nodes; i++) {
        for (int j = 0; j < graph->nodes; j++) {
            fprintf(file, "%d ", graph->matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

struct Graph *inputGraph(int nodes, int **matrix) {
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->matrix = matrix;
    graph->nodes = nodes;
    return graph;
}

void addNode(struct Graph *graph) {
    graph->nodes++;

    int **newMatrix = malloc(graph->nodes * sizeof(int *));
    for (int i = 0; i < graph->nodes; i++) {
        newMatrix[i] = malloc(graph->nodes * sizeof(int));
    }

    for (int i = 0; i < graph->nodes - 1; i++) {
        for (int j = 0; j < graph->nodes - 1; j++) {
            newMatrix[i][j] = graph->matrix[i][j];
        }
    }

    for (int i = 0; i < graph->nodes; i++) {
        newMatrix[i][graph->nodes - 1] = 0;
        newMatrix[graph->nodes - 1][i] = 0;
    }

    graph->matrix = newMatrix;
}

void deleteNode(struct Graph *inputGraph, int index) {

    int **newMatrix = (int **) malloc((inputGraph->nodes - 1) * sizeof(int *));
    for (int i = 0; i < inputGraph->nodes - 1; i++) {
        newMatrix[i] = (int *) malloc((inputGraph->nodes - 1) * sizeof(int));
    }

    for (int i = 0; i <= index; i++)
        if (inputGraph->matrix[i][index] != 0) inputGraph->nodes--;

    for (int i = 0; i < index; i++)
        for (int j = 0; j < index; j++)
            newMatrix[i][j] = inputGraph->matrix[i][j];

    for (int i = 0; i < index; i++)
        for (int j = index + 1; j < inputGraph->nodes; j++) {
            newMatrix[i][j - 1] = inputGraph->matrix[i][j];
            newMatrix[j - 1][i] = inputGraph->matrix[j][i];
        }

    for (int i = index; i < inputGraph->nodes; i++)
        for (int j = index; j < inputGraph->nodes; j++)
            newMatrix[i - 1][j - 1] = inputGraph->matrix[i][j];

    inputGraph->nodes--;
    inputGraph->matrix = newMatrix;

}

void addEdge(struct Graph *graph, int from, int to, int weight) {
    for (int i = 0; i < graph->nodes; i++) {
        for (int j = 0; j < graph->nodes; j++) {
            if (i == from && j == to) {
                if (graph->matrix[i][j] == 0) {
                    graph->matrix[i][j] = weight;
                } else {
                    printf("Такой путь уже задан\n");
                }
            }
        }
    }
}

void deleteEdge(struct Graph *graph, int from, int to) {
    for (int i = 0; i < graph->nodes; i++) {
        for (int j = 0; j < graph->nodes; j++) {
            if (i == from && j == to) {
                if (graph->matrix[i][j] != 0) {
                    graph->matrix[i][j] = 0;
                } else {
                    printf("Такого пути и так не существует\n");
                }
            }
        }
    }
}

void clearMemory(struct Graph *graph) {
    for (int i = 0; i < graph->nodes; i++) {
        free(graph->matrix[i]);
    }
    free(graph->matrix);
    free(graph);
}

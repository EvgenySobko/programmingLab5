#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"
#include "math.h"
#include "string.h"

struct Graph *convert(FILE *file) {

    char *inputValues = (char *) malloc(sizeof(file) / sizeof(char));

    int nodes;
    int i = 0;

    while (((inputValues[i] = (char) getc(file)) != EOF)) {
        if (inputValues[i] != ' ' && inputValues[i] != '\n') {
            i++;
        }
    }

    nodes = (int) sqrt(i);

    int **matrix = (int **) malloc(nodes * sizeof(int *));
    for (int j = 0; j < nodes; j++) {
        matrix[j] = (int *) malloc(nodes * sizeof(int));
    }

    i = 0;
    for (int j = 0; j < nodes; j++) {
        for (int k = 0; k < nodes; k++) {
            matrix[j][k] = (inputValues[i]) % 48;
            i++;
        }
    }

    fclose(file);

    return inputGraph(nodes, matrix);
}

void equals(struct Graph *inputGraph, struct Graph *expectedGraph) {

    bool flag = true;

    for (int i = 0; i < inputGraph->nodes; i++) {
        for (int j = 0; j < inputGraph->nodes; j++) {
            if (inputGraph->matrix[i][j] != expectedGraph->matrix[i][j]) {
                flag = false;
            }
        }
    }
    if (flag) printf("true");
    else printf("false");

}

void edgeDeletionTest(struct Graph *inputGraph, struct Graph *expectedGraph) {
    deleteEdge(inputGraph, 0, 1);
    printf("Deletion of edge test is ");
    equals(inputGraph, expectedGraph);
    printf("\n");
}

void addEdgeTest(struct Graph *inputGraph, struct Graph *expectedGraph, int from, int to, int weight) {
    addEdge(inputGraph, from, to, weight);
    printf("Addition of edge test is ");
    equals(inputGraph, expectedGraph);
    printf("\n");
}

void nodeDeletionTest(struct Graph *inputGraph, struct Graph *expectedGraph, int index) {
    deleteNode(inputGraph, index);
    printf("Deletion of node test is ");
    equals(inputGraph, expectedGraph);
    printf("\n");
}

void addNodeTest(struct Graph *inputGraph, struct Graph *expectedGraph) {
    addNode(inputGraph);
    printf("Addition of node test is ");
    equals(inputGraph, expectedGraph);
    printf("\n");
}

int main(void) {

    FILE *input_0 = fopen("test_0.txt", "r");
    FILE *input_2 = fopen("test_2.txt", "r");
    FILE *input_3 = fopen("test_3.txt", "r");
    FILE *expected_0 = fopen("expected_0.txt", "r");
    FILE *expected_1 = fopen("expected_1.txt", "r");
    FILE *expected_2 = fopen("expected_2.txt", "r");
    FILE *expected_3 = fopen("expected_3.txt", "r");
    struct Graph *inputGraph0 = convert(input_0);
    struct Graph *inputGraph2 = convert(input_2);
    struct Graph *inputGraph3 = convert(input_3);
    struct Graph *expectedGraph0 = convert(expected_0);
    struct Graph *expectedGraph1 = convert(expected_1);
    struct Graph *expectedGraph2 = convert(expected_2);
    struct Graph *expectedGraph3 = convert(expected_3);

    edgeDeletionTest(inputGraph0, expectedGraph0);
    nodeDeletionTest(inputGraph2, expectedGraph2, 2);
    addEdgeTest(inputGraph3, expectedGraph3, 0, 2, 5);
    addNodeTest(inputGraph0, expectedGraph1);

    return 0;
}

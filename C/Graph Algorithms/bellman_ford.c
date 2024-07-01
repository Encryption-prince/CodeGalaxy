#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NUM_VERTICES 5  // Number of vertices in the graph
#define NUM_EDGES 8     // Number of edges in the graph

typedef struct {
    int source, destination, weight;
} Edge;

typedef struct {
    int num_vertices, num_edges;
    Edge* edges;
} Graph;

Graph* createGraph(int num_vertices, int num_edges) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->num_edges = num_edges;
    graph->edges = (Edge*)malloc(graph->num_edges * sizeof(Edge));
    return graph;
}

void printShortestPaths(int distances[], int num_vertices) {
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < num_vertices; ++i)
        printf("%d \t\t %d\n", i, distances[i]);
}

void BellmanFord(Graph* graph, int source) {
    int num_vertices = graph->num_vertices;
    int num_edges = graph->num_edges;
    int* distances = (int*)malloc(num_vertices * sizeof(int));  // Dynamically allocate memory

    for (int i = 0; i < num_vertices; i++)
        distances[i] = INT_MAX;
    distances[source] = 0;

    for (int i = 1; i <= num_vertices - 1; i++) {
        for (int j = 0; j < num_edges; j++) {
            int u = graph->edges[j].source;
            int v = graph->edges[j].destination;
            int weight = graph->edges[j].weight;
            if (distances[u] != INT_MAX && distances[u] + weight < distances[v])
                distances[v] = distances[u] + weight;
        }
    }

    for (int i = 0; i < num_edges; i++) {
        int u = graph->edges[i].source;
        int v = graph->edges[i].destination;
        int weight = graph->edges[i].weight;
        if (distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }

    printShortestPaths(distances, num_vertices);

    free(distances);  // Free allocated memory
}

int main() {
    int num_vertices = 5;
    int num_edges = 8;
    Graph* graph = createGraph(num_vertices, num_edges);

    graph->edges[0].source = 0;
    graph->edges[0].destination = 1;
    graph->edges[0].weight = -1;

    graph->edges[1].source = 0;
    graph->edges[1].destination = 2;
    graph->edges[1].weight = 4;

    graph->edges[2].source = 1;
    graph->edges[2].destination = 2;
    graph->edges[2].weight = 3;

    graph->edges[3].source = 1;
    graph->edges[3].destination = 3;
    graph->edges[3].weight = 2;

    graph->edges[4].source = 1;
    graph->edges[4].destination = 4;
    graph->edges[4].weight = 2;

    graph->edges[5].source = 3;
    graph->edges[5].destination = 2;
    graph->edges[5].weight = 5;

    graph->edges[6].source = 3;
    graph->edges[6].destination = 1;
    graph->edges[6].weight = 1;

    graph->edges[7].source = 4;
    graph->edges[7].destination = 3;
    graph->edges[7].weight = -3;

    BellmanFord(graph, 0);

    free(graph->edges);
    free(graph);

    return 0;
}

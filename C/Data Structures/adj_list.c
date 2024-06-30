#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the adjacency list
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

// Structure for the adjacency list
struct AdjList {
    struct AdjListNode* head;
};

// Structure for the graph
struct Graph {
    int numVertices;
    struct AdjList* array;
};

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with 'V' vertices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    if (graph == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    graph->numVertices = numVertices;

    // Create an array of adjacency lists. Size of the array will be 'V'
    graph->array = (struct AdjList*) malloc(numVertices * sizeof(struct AdjList));
    if (graph->array == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize each adjacency list as empty by making head as NULL
    for (int i = 0; i < numVertices; ++i) {
        graph->array[i].head = NULL;
    }

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to print the adjacency list representation of the graph
void printGraph(struct Graph* graph) {
    printf("Adjacency list representation of the graph:\n");
    for (int i = 0; i < graph->numVertices; ++i) {
        struct AdjListNode* current = graph->array[i].head;
        printf("Vertex %d -> ", i);
        while (current != NULL) {
            printf("%d -> ", current->dest);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Function to free memory allocated to the graph
void freeGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; ++i) {
        struct AdjListNode* current = graph->array[i].head;
        while (current != NULL) {
            struct AdjListNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
}

int main() {
    // Create a graph with 5 vertices
    int numVertices = 5;
    struct Graph* graph = createGraph(numVertices);

    // Add edges
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    // Print the adjacency list representation of the graph
    printGraph(graph);

    // Free memory allocated to the graph
    freeGraph(graph);

    return 0;
}

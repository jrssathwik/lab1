#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
};

// Function to find set of an element i (uses path compression technique)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Function that does union of two sets of x and y (uses union by rank)
void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Comparison function to sort edges by their weight
int compare(const void* a, const void* b) {
    struct Edge* a_edge = (struct Edge*)a;
    struct Edge* b_edge = (struct Edge*)b;
    return a_edge->weight - b_edge->weight;
}

// Function to construct MST using Kruskal's algorithm
void KruskalMST(struct Edge* edges, int V, int E) {
    // Allocate memory for subsets
    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));

    // Initialize each subset with its parent and rank
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Initialize variables for the resulting MST
    struct Edge resultMST[V - 1];
    int e = 0;  // Index variable for resultMST
    int i = 0;  // Index variable for sorted edges array

    // Sort all edges in non-decreasing order of their weight
    qsort(edges, E, sizeof(edges[0]), compare);

    // Iterate through all the edges
    while (e < V - 1 && i < E) {
        struct Edge next_edge = edges[i++];

        // Check if adding the next edge creates a cycle or not
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
        if (x != y) {
            resultMST[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Print the resulting MST
    printf("Edges in the Minimum Cost Spanning Tree:\n");
    for (int j = 0; j < e; ++j)
        printf("%d -- %d == %d\n", resultMST[j].src, resultMST[j].dest, resultMST[j].weight);

    // Free dynamically allocated memory
    free(subsets);
}

// Driver program
int main() {
    int V = 4;  // Number of vertices
    int E = 5;  // Number of edges

    struct Edge edges[] = { {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4} };

    KruskalMST(edges, V, E);

    return 0;
}

#include <stdio.h>
#include <stdbool.h>

#define V 4 // Number of vertices

// Function to check if it's safe to color the vertex with the given color
bool isSafe(int vertex, int graph[V][V], int colors[V], int color) {
    for (int i = 0; i < V; i++) {
        if (graph[vertex][i] && colors[i] == color) {
            return false;
        }
    }
    return true;
}

// Recursive function to assign colors to vertices
bool graphColoringUtil(int graph[V][V], int m, int colors[V], int vertex) {
    if (vertex == V) {
        return true; // All vertices are colored
    }

    for (int color = 1; color <= m; color++) {
        if (isSafe(vertex, graph, colors, color)) {
            colors[vertex] = color; // Assign color to the vertex

            if (graphColoringUtil(graph, m, colors, vertex + 1)) {
                return true; // Color successfully assigned to all vertices
            }

            colors[vertex] = 0; // Backtrack
        }
    }

    return false; // Unable to color the graph with m colors
}

// Function to solve the graph coloring problem
void graphColoring(int graph[V][V], int m) {
    int colors[V];
    for (int i = 0; i < V; i++) {
        colors[i] = 0; // Initialize all colors as unassigned
    }

    if (!graphColoringUtil(graph, m, colors, 0)) {
        printf("Solution does not exist\n");
        return;
    }

    printf("Solution exists: The colors assigned to vertices are\n");
    for (int i = 0; i < V; i++) {
        printf("Vertex %d: Color %d\n", i, colors[i]);
    }
}

// Driver function
int main() {
    int graph[V][V] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };
    int m = 3; // Number of colors

    graphColoring(graph, m);

    return 0;
}

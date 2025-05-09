#include <stdio.h>

#define INF 99999  // Define a large value as infinity
#define V 4        // Number of vertices

// Function to print the final shortest distance matrix
void printSolution(int dist[V][V]) {
    printf("The shortest distances between every pair of vertices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
           
            printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

// Floyd-Warshall Algorithm
void floydWarshall(int graph[V][V]) {
    int dist[V][V];

    // Initialize the distance matrix with the given graph
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    // Updating distances by considering each vertex as an intermediate
    for (int k = 0; k < V; k++) {  // k is the intermediate vertex
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                // Update dist[i][j] if a shorter path is found via vertex k
                if (dist[i][k] != INF && dist[k][j] != INF && 
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print the shortest path matrix
    printSolution(dist);
}

int main() {
    int graph[V][V] = {
        {0,   3,   INF, 5},
        {2,   0,   INF, 4},
        {INF, 1,   0,   INF},
        {INF, INF, 2,   0}
    };

    floydWarshall(graph);
    return 0;
}

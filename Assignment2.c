#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 10000000

typedef struct{
    int vertices;
    int **matrix;
}Graphmatrix;

typedef struct Node{
    int vertex;
    int weight;
    struct Node *next;
}Node;

typedef struct{
    int vertices;
    int **list;
}Graphlist;

Graphmatrix *createGraphmatrix(int vertices){
    Graphmatrix *graph = (Graphmatrix *)malloc(sizeof(Graphmatrix));
    graph->vertices = vertices;
    graph->matrix = (int **)malloc(vertices * sizeof(int *));
    for(int i=0; i<vertices; i++){
        graph->matrix[i] = (int *)malloc(vertices * sizeof(int));
        for(int j=0; j<vertices; j++){
            graph->matrix[i][j] = (i==j) ? 0 : INF;
        }
    }
    return graph;
}

void addedgematrix(Graphmatrix *graph, int src, int dest, int weight){
    graph->matrix[src][dest] = weight;
    graph->matrix[dest][src] = weight;
}

Graphlist *createGraphlist(int vertices){
    Graphlist *graph = (Graphlist *)malloc(sizeof(Graphlist));
    graph->vertices = vertices;
    graph->list = (Node **)malloc(vertices * sizeof(Node  *));
    for(int i=0; i<vertices; i++){
        graph->list[i] = NULL;
    }
    return graph;
}

void addedgelist(Graphlist *graph, int src, int dest, int weight){
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->vertex = dest;
    newnode->weight = weight;
    newnode->next = graph->list[src];
    graph->list[src] = newnode;

    newnode = (Node *)malloc(sizeof(Node));
    newnode->vertex = src;
    newnode->weight = weight;
    newnode->next = graph->list[dest];
    graph->list[dest] = newnode;
}

void primsalgo (Graphmatrix *graph){
    int vertices = graph->vertices;
    int *key = (int *)malloc(vertices * sizeof(int));
    int *parent = (int *)malloc(vertices * sizeof(int));
    int *inMST = (int *)malloc(vertices * sizeof(int));

    for(int i=0; i<vertices; i++){
        key[i] = INF;
        inMST[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for(int count=0; count<vertices-1; count++){
        int minkey = INF, u;
        for(int v=0; v<vertices; v++){
            if(!inMST[v] && key[v]<minkey){
                minkey = key[v];
                u = v;
            }
        }

        inMST[u] = 1;

        for(int v=0; v<vertices; v++){
            if(graph->matrix[u][v] && !inMST[v] && graph->matrix[u][v] < key[v]){
                key[v] = graph->matrix[u][v];
                parent[v] = u;
            }
        }
    }

    printf("Edge \tWeight\n");
    for(int i=1; i<vertices; i++){
        printf("%d - %d \t%d\n", parent[i], i, graph->matrix[i][parent[i]]);
    }

    free(key);
    free(parent);
    free(inMST);
}

typedef struct{
    int src, dest, weight;
}edge;

int compareedges(const void *a, const void *b){
    edge *edgeA = (edge *)a;
    edge *edgeB = (edge *)b;
    return edgeA->weight - edgeB->weight; 
}

int find(int *parent, int i){
    if(parent[i] != i){
        parent[i] = find(parent, parent[i]);
    }
    return parent[i];
}

void unionsets(int *parent, int *rank, int x, int y){
    int xRoot = find(parent, x);
    int yRoot = find(parent, y);

    if(rank[xRoot] < rank[yRoot])
        parent[xRoot] = yRoot;
    else if (rank[xRoot] > rank[yRoot])
        parent[yRoot] = xRoot;
    else{
        parent[yRoot] = xRoot;
        rank[xRoot]++;
    }
}

void kruskalalgo(Graphmatrix *graph){
    int vertices = graph->vertices;
    edge *edges = (edge *)malloc(vertices * vertices * sizeof(edge));
    int edgecount = 0;

    for(int i=0; i<vertices; i++){
        for(int j=i+1; j<vertices; j++){
            if(graph->matrix[i][j] != INF){
                edges[edgecount].src = i;
                edges[edgecount].dest = j;
                edges[edgecount].weight = graph->matrix[i][j];
                edgecount++;
            }
        }
    }

    qsort(edges, edgecount, sizeof(edge), compareedges);

    int *parent = (int *)malloc(vertices * sizeof(int));
    int *rank = (int *)malloc(vertices * sizeof(int));

    for(int i=0; i<vertices; i++){
        parent[i] = i;
        rank[i] = 0;
    }

    printf("Edge \tWeight\n");
    for(int i=0, e=0; e<vertices-1 && i<edgecount; i++){
        int u = find(parent, edges[i].src);
        int v = find(parent, edges[i].dest);

        if(u != v){
            printf("%d - %d \t%d\n", edges[i].src, edges[i].dest, edges[i].weight);
            unionsets(parent, rank, u, v);
            e++;
        }
    }
    free(edges);
    free(parent);
    free(rank);
}

int main(){
    srand(time(NULL));

    int vertices = 5;
    Graphmatrix *graph = createGraphmatrix(vertices);

    for(int i=0; i<vertices; i++){
        for(int j=i+1; j<vertices; j++){
            int weight = rand()%100 + 1;
            addedgematrix(graph, i, j, weight);
        }
    }

    printf("\nPrim's Algorithm\n");
    primsalgo(graph);

    printf("\nKruskal's Algorithm\n");
    kruskalalgo(graph);

    return 0;
}


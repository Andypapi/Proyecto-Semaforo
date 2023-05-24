#ifndef GRAPH_H
#define GRAPH_H

// Estructuras para el grafo
typedef struct Node {
  char name[5];      // Nombre del nodo, por ejemplo 'AO', 'AE', 'CS', 'CN'
  struct Node *next; // Array de punteros a los nodos vecinos
} Node;

typedef struct Graph {
  int numVertices;
  Node **adjacencyList;
} Graph;

// Funciones a implementar en graph.c
Node *createNode(char *name);
Graph *createGraph(int numVertices);
Graph *readGraphFromFile(char *filename);
void addEdge(Graph *graph, char *source, char *destination);
void printGraph(Graph *graph);
void freeGraph(Graph *graph);
int getIndex(Graph *graph, char *label);
int isEdge(Graph *graph, char *label1, char *label2);
#endif

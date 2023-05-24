#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Función: createNode
 * Crea un nuevo nodo con el nombre especificado.
 *
 * Descripción:
 * Esta función crea un nuevo nodo con el nombre especificado y lo devuelve.
 * El nodo se inicializa con un puntero siguiente nulo.
 *
 * Parámetros:
 * - name: Nombre del nodo.
 *
 * Retorna:
 * - Puntero al nodo recién creado.
 *
 * Precondiciones:
 * - El nombre del nodo (name) debe ser una cadena de caracteres válida.
 *
 * Postcondiciones:
 * - Se crea y se devuelve un nuevo nodo con el nombre especificado.
 * - El nodo se inicializa con un puntero siguiente nulo.
 */

Node *createNode(char *name) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  strcpy(newNode->name, name);
  newNode->next = NULL;
  return newNode;
}

/*
 * Función: createGraph
 * Crea un nuevo grafo con el número especificado de vértices.
 *
 * Descripción:
 * Esta función crea un nuevo grafo con el número especificado de vértices.
 * El grafo se inicializa con una lista de adyacencia vacía para cada vértice.
 *
 * Parámetros:
 * - numVertices: Número de vértices que tendrá el grafo.
 *
 * Retorna:
 * - Puntero al grafo recién creado.
 *
 * Precondiciones:
 * - El número de vértices (numVertices) debe ser un valor no negativo.
 *
 * Postcondiciones:
 * - Se crea y se devuelve un nuevo grafo con el número especificado de
 * vértices.
 * - Cada lista de adyacencia del grafo se inicializa como una lista vacía.
 */

Graph *createGraph(int numVertices) {
  Graph *graph = (Graph *)malloc(sizeof(Graph));
  graph->numVertices = numVertices;

  // Asignar memoria para la adjacency list
  graph->adjacencyList = (Node **)malloc(numVertices * sizeof(Node *));

  // Inicializar cada adjacency list como vacía
  for (int i = 0; i < numVertices; i++) {
    graph->adjacencyList[i] = NULL;
  }
  // Asignar memoria para cada Node en la adjacency list
  for (int i = 0; i < numVertices; i++) {
    graph->adjacencyList[i] = (Node *)malloc(sizeof(Node));
    graph->adjacencyList[i]->next = NULL;
  }

  return graph;
}

/*
 * Función: addEdge
 * Añade un nuevo arco (edge) desde el nodo fuente (source) hasta el nodo
 * destino (destination) en el grafo especificado.
 *
 * Descripción:
 * Esta función busca los nodos correspondientes a los nombres de origen
 * (source) y destino (destination) en el grafo y añade un nuevo arco (edge)
 * desde el nodo fuente hasta el nodo destino.
 *
 * Parámetros:
 * - graph: Puntero al grafo al que se añadirá el arco.
 * - source: Nombre del nodo fuente (origen).
 * - destination: Nombre del nodo destino.
 *
 * Precondiciones:
 * - El grafo (graph) debe ser un puntero válido a una estructura de grafo.
 * - Los nombres de origen (source) y destino (destination) deben ser cadenas de
 * caracteres válidas.
 *
 * Postcondiciones:
 * - Se añade un nuevo arco (edge) desde el nodo fuente (source) hasta el nodo
 * destino (destination) en el grafo especificado.
 * - Si el arco ya existe, no se realiza ninguna acción.
 * - Si alguno de los nodos source o destination no se encuentra en el grafo, no
 * se añade el arco.
 */

void addEdge(Graph *graph, char *source, char *destination) {
  // Encuentra los nodos correspondientes a `source` y a `destination`
  Node *sourceNode = NULL;
  Node *destinationNode = NULL;

  for (int i = 0; i < graph->numVertices; i++) {
    if (strcmp(graph->adjacencyList[i]->name, source) == 0) {
      sourceNode = graph->adjacencyList[i];
    }
    if (strcmp(graph->adjacencyList[i]->name, destination) == 0) {
      destinationNode = graph->adjacencyList[i];
    }
    // Exit the loop if both source and destination nodes are found
    if (sourceNode != NULL && destinationNode != NULL) {
      break;
    }
  }

  // Si cualquiera de los Nodes `source` y `destination` no se encuentra
  // retorna sin añadir un `edge`
  if (sourceNode == NULL || destinationNode == NULL) {
    return;
  }

  // Checa si el edge ya existe
  if (isEdge(graph, sourceNode->name, destinationNode->name)) {
    return;
  }

  // Crea un nuevo `edge` desde el Node `source` hacía el Node `destination`
  Node *newEdge = createNode(destination);
  newEdge->next = sourceNode->next;
  sourceNode->next = newEdge;
}

/*
 * Función: printGraph
 * Imprime por pantalla la representación del grafo especificado.
 *
 * Descripción:
 * Esta función recorre cada nodo del grafo y muestra por pantalla su nombre
 * seguido de los nodos adyacentes a él.
 *
 * Parámetros:
 * - graph: Puntero al grafo que se imprimirá.
 *
 * Precondiciones:
 * - El grafo (graph) debe ser un puntero válido a una estructura de grafo.
 *
 * Postcondiciones:
 * - Se muestra por pantalla la representación del grafo especificado,
 * imprimiendo cada nodo y sus nodos adyacentes.
 */

void printGraph(Graph *graph) {
  for (int i = 0; i < graph->numVertices; i++) {
    Node *currentNode = graph->adjacencyList[i];
    printf("Node %s: ", graph->adjacencyList[i]->name);
    while (currentNode != NULL) {
      printf("%s ", currentNode->name);
      currentNode = currentNode->next;
    }
    printf("\n");
  }
}

/*
 * Función: freeGraph
 * Libera la memoria asignada al grafo y sus nodos.
 *
 * Descripción:
 * Esta función libera la memoria asignada al grafo y a todos sus nodos, liberando cada nodo de la lista de adyacencia.
 *
 * Parámetros:
 * - graph: Puntero al grafo que se liberará de memoria.
 *
 * Precondiciones:
 * - El grafo (graph) debe ser un puntero válido a una estructura de grafo.
 *
 * Postcondiciones:
 * - Se libera la memoria asignada al grafo y sus nodos, dejándolos en un estado inválido.
 */

void freeGraph(Graph *graph) {
  if (graph) {
    for (int i = 0; i < graph->numVertices; i++) {
      Node *currentNode = graph->adjacencyList[i];
      while (currentNode != NULL) {
        Node *temp = currentNode;
        currentNode = currentNode->next;
        free(temp);
      }
    }
  }
}

/*
 * Función: readGraphFromFile
 * Lee un grafo desde un archivo de texto y lo construye en memoria.
 *
 * Descripción:
 * Esta función lee un grafo desde un archivo de texto, donde se especifica el número de vértices, los nombres de los vértices
 * y los bordes incompatibles. Luego, construye el grafo en memoria utilizando las funciones auxiliares.
 *
 * Parámetros:
 * - filename: Nombre del archivo de texto que contiene la descripción del grafo.
 *
 * Precondiciones:
 * - El archivo de texto debe estar en el formato correcto y ser accesible para lectura.
 *
 * Postcondiciones:
 * - Se crea un grafo en memoria a partir de la descripción del archivo de texto y se devuelve como resultado.
 * - Si ocurre algún error durante la lectura del archivo o la construcción del grafo, se devuelve NULL.
 */

Graph *readGraphFromFile(char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error: No se pudo abrir el archivo.\n");
    return NULL;
  }
  int numVertices;
  fscanf(file, "%d\n", &numVertices);

  Graph *graph = createGraph(numVertices);

  char line[100];
  char *token;

  // Leer los nombres de los vertices
  fgets(line, sizeof(line), file);
  token = strtok(line, " \n");
  int vertexIndex = 0;
  while (token != NULL) {
    strcpy(graph->adjacencyList[vertexIndex]->name, token);
    token = strtok(NULL, " \n");
    vertexIndex++;
  }

  // Leer los `edges` incompatibles
  while (fgets(line, sizeof(line), file)) {
    token = strtok(line, " -\n");
    char *source = token;
    token = strtok(NULL, " -\n");
    char *destination = token;

    if (strcmp(source, destination) != 0) {
      addEdge(graph, source, destination);
    }
  }

  fclose(file);
  return graph;
}

/*
 * Función: getIndex
 * Busca el índice de un vértice en el grafo dado su nombre (etiqueta).
 *
 * Descripción:
 * Esta función busca el índice de un vértice en el grafo dado su nombre (etiqueta).
 * Recorre la lista de adyacencia del grafo y compara la etiqueta de cada vértice
 * con el nombre dado hasta encontrar una coincidencia. Devuelve el índice del vértice
 * si se encuentra, o -1 si no se encuentra.
 *
 * Parámetros:
 * - graph: Puntero al grafo en el que se realizará la búsqueda.
 * - label: Etiqueta (nombre) del vértice que se desea buscar.
 *
 * Retorno:
 * - El índice del vértice si se encuentra.
 * - -1 si el vértice no se encuentra en el grafo.
 */

int getIndex(Graph *graph, char *label) {
  for (int i = 0; i < graph->numVertices; i++) {
    if (strcmp(graph->adjacencyList[i]->name, label) == 0) {
      return i;
    }
  }
  return -1;
}


/*
 * Función: isEdge
 * Verifica si existe una arista (edge) entre dos vértices en el grafo.
 *
 * Descripción:
 * Esta función verifica si existe una arista entre dos vértices en el grafo.
 * Primero, obtiene los índices de los vértices correspondientes a las etiquetas dadas.
 * Si alguno de los vértices no se encuentra en el grafo, se devuelve 0.
 * Luego, se recorre la lista de adyacencia del primer vértice y se busca el segundo vértice.
 * Si se encuentra, se devuelve 1 indicando que existe una arista entre ellos.
 * En caso contrario, se devuelve 0.
 *
 * Parámetros:
 * - graph: Puntero al grafo en el que se realizará la verificación.
 * - label1: Etiqueta (nombre) del primer vértice.
 * - label2: Etiqueta (nombre) del segundo vértice.
 *
 * Retorno:
 * - 1 si existe una arista entre los vértices.
 * - 0 si no existe una arista entre los vértices o alguno de los vértices no se encuentra en el grafo.
 */

int isEdge(Graph *graph, char *label1, char *label2) {

  int index1 = getIndex(graph, label1);
  int index2 = getIndex(graph, label2);

  if (index1 == -1 || index2 == -1) {
    return 0; // Uno o ambos nodos no fueron encontrados
  }

  Node *node = graph->adjacencyList[index1];
  Node *current = node->next;
  while (current != NULL) {
    if (strcmp(current->name, label2) == 0) {
      return 1; // `Edge` encontrado
    }
    current = current->next;
  }

  return 0; // `Edge` no encontrado
}

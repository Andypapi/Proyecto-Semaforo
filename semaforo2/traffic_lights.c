#include "graph.h"
#include "user_interface.h"

#include "traffic_lights.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * Función: createQueueNode
 * Crea un nuevo nodo de cola.
 *
 * Descripción:
 * Esta función crea y devuelve un nuevo nodo de cola. Asigna memoria para la estructura del nodo utilizando malloc()
 * y verifica si se pudo asignar memoria correctamente. Asigna los datos proporcionados al nuevo nodo y establece el
 * puntero "next" como NULL. Si no se puede asignar memoria para el nodo, se imprime un mensaje de error y se devuelve NULL.
 *
 * Parámetros:
 * - data: Puntero al nodo que se asignará como dato del nuevo nodo de cola.
 *
 * Retorno:
 * - Puntero al nuevo nodo de cola creado.
 * - NULL si no se puede asignar memoria para el nodo.
 */
QueueNode *createQueueNode(Node *data) {
  QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
  if (newNode == NULL) {
    printf("Error: No se pudo asignar `QueueNode` en memoria.\n");
    return NULL;
  }
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

/*
 * Función: createQueue
 * Crea una nueva cola.
 *
 * Descripción:
 * Esta función crea y devuelve una nueva cola. Asigna memoria para la estructura de la cola utilizando malloc()
 * y verifica si se pudo asignar memoria correctamente. Inicializa los punteros front y rear como NULL, indicando
 * que la cola está vacía. Si no se puede asignar memoria para la cola, se imprime un mensaje de error y se devuelve NULL.
 *
 * Parámetros: Ninguno.
 *
 * Retorno:
 * - Puntero a la nueva cola creada.
 * - NULL si no se puede asignar memoria para la cola.
 */
Queue *createQueue() {
  Queue *queue = (Queue *)malloc(sizeof(Queue));
  if (queue == NULL) {
    printf("Error: No se pudo asignar la cola en memoria.\n");
    return NULL;
  }
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
}

/*
 * Función: isQueueEmpty
 * Verifica si la cola está vacía.
 *
 * Descripción:
 * Esta función verifica si la cola especificada está vacía. Comprueba si el puntero front de la cola es NULL,
 * lo cual indica que no hay nodos en la cola. Devuelve true si la cola está vacía y false si no lo está.
 *
 * Parámetros:
 * - queue: Puntero a la cola que se desea verificar.
 *
 * Retorno:
 * - true si la cola está vacía.
 * - false si la cola no está vacía.
 */
bool isQueueEmpty(Queue *queue) { return queue->front == NULL; }

/*
 * Función: enqueue
 * Inserta un nodo al final de la cola.
 *
 * Descripción:
 * Esta función inserta un nuevo nodo al final de la cola especificada. Crea un nuevo nodo de cola utilizando la función
 * createQueueNode() y asigna los datos proporcionados al nuevo nodo. Si la cola está vacía (front y rear son NULL),
 * asigna el nuevo nodo tanto a front como a rear. De lo contrario, enlaza el nuevo nodo al final de la cola ajustando los
 * punteros next de rear y asignando el nuevo nodo como el nuevo rear.
 *
 * Parámetros:
 * - queue: Puntero a la cola a la que se agregará el nuevo nodo.
 * - data: Puntero al nodo que se agregará a la cola.
 *
 * Retorno: Ninguno.
 */
void enqueue(Queue *queue, Node *data) {
  QueueNode *newNode = createQueueNode(data);
  if (isQueueEmpty(queue)) {
    queue->front = newNode;
    queue->rear = newNode;
  } else {
    queue->rear->next = newNode;
    queue->rear = newNode;
  }
}

/*
 * Función: isPartOfQueue
 * Verifica si un nodo se encuentra en la cola.
 *
 * Descripción:
 * Esta función verifica si un nodo específico se encuentra en la cola especificada. Recorre la cola desde el frente (front)
 * hasta el final (rear). Compara el nombre del nodo actual con el nombre del nodo buscado utilizando la función strcmp().
 * Si encuentra una coincidencia, devuelve true indicando que el nodo se encuentra en la cola. Si se recorre toda la cola
 * sin encontrar una coincidencia, devuelve false indicando que el nodo no se encuentra en la cola.
 *
 * Parámetros:
 * - queue: Puntero a la cola en la que se realizará la búsqueda.
 * - node: Puntero al nodo que se desea buscar en la cola.
 *
 * Retorno:
 * - true si el nodo se encuentra en la cola.
 * - false si el nodo no se encuentra en la cola.
 */
bool isPartOfQueue(Queue *queue, Node *node) {
  QueueNode *current = queue->front;
  while (current != NULL) {
    if (strcmp(current->data->name, node->name) == 0) {
      return true; // Node found in the queue
    }
    current = current->next;
  }
  return false; // Node not found in the queue
}


/*
 * Función: createNewGroup
 * Crea un nuevo grupo.
 *
 * Descripción:
 * Esta función crea y devuelve un nuevo grupo. Asigna memoria para la estructura del grupo utilizando malloc() y
 * verifica si se pudo asignar memoria correctamente. Inicializa el número de turnos en 0, el arreglo de nombres de
 * vértices (turns) en NULL y establece el puntero "next" como NULL. Si no se puede asignar memoria para el grupo,
 * se imprime un mensaje de error y se devuelve NULL.
 *
 * Parámetros: Ninguno.
 *
 * Retorno:
 * - Puntero al nuevo grupo creado.
 * - NULL si no se puede asignar memoria para el grupo.
 */
Group *createNewGroup() {
  Group *group = (Group *)malloc(sizeof(Group));
  if (group == NULL) {
    printf("Error: Failed to allocate memory for Group\n");
    return NULL;
  }

  group->numTurns = 0;
  group->turns = NULL;
  group->next = NULL;

  return group;
}

/*
 * Función: addGroup
 * Agrega un grupo a la lista de grupos.
 *
 * Descripción:
 * Esta función agrega un nuevo grupo a la lista de grupos proporcionada. Crea un nuevo grupo utilizando la función
 * createNewGroup(), asigna el número de vértices del grupo y el arreglo de nombres de vértices al nuevo grupo.
 * A continuación, establece el puntero "next" del nuevo grupo como NULL. Si la lista de grupos está vacía (head es NULL),
 * asigna el nuevo grupo tanto a head como a tail. De lo contrario, enlaza el nuevo grupo al final de la lista ajustando los
 * punteros next de tail y asignando el nuevo grupo como el nuevo tail.
 *
 * Parámetros:
 * - groupList: Puntero a la lista de grupos a la que se agregará el nuevo grupo.
 * - groupNodes: Arreglo de nombres de vértices que forman el nuevo grupo.
 * - groupCount: Número de vértices en el nuevo grupo.
 *
 * Retorno: Ninguno.
 */
void addGroup(GroupList *groupList, char **groupNodes, int groupCount) {
  Group *newGroup = createNewGroup();
  newGroup->numTurns = groupCount;
  newGroup->turns = groupNodes;
  newGroup->next = NULL;

  if (groupList->head == NULL) {
    groupList->head = newGroup;
    groupList->tail = newGroup;
  } else {
    groupList->tail->next = newGroup;
    groupList->tail = newGroup;
  }
}

/*
 * Función: isStringInGroups
 * Verifica si una cadena de texto se encuentra en alguno de los grupos.
 *
 * Descripción:
 * Esta función verifica si una cadena de texto específica se encuentra en alguno de los grupos de la lista de grupos
 * proporcionada. Recorre la lista de grupos desde el inicio hasta el final. Dentro de cada grupo, itera sobre el arreglo
 * de nombres de vértices ("turns") y compara cada nombre con la cadena de texto buscada utilizando la función strcmp().
 * Si encuentra una coincidencia, devuelve true indicando que la cadena de texto se encuentra en algún grupo. Si se recorren
 * todos los grupos sin encontrar una coincidencia, devuelve false indicando que la cadena de texto no se encuentra en
 * ningún grupo.
 *
 * Parámetros:
 * - groupList: Puntero a la lista de grupos en la que se realizará la búsqueda.
 * - searchString: Cadena de texto que se desea buscar en los grupos.
 *
 * Retorno:
 * - true si la cadena de texto se encuentra en algún grupo.
 * - false si la cadena de texto no se encuentra en ningún grupo.
 */
bool isStringInGroups(GroupList *groupList, const char *searchString) {
  Group *currentGroup = groupList->head;
  while (currentGroup != NULL) {
    for (int i = 0; i < currentGroup->numTurns; i++) {
      if (strcmp(currentGroup->turns[i], searchString) == 0) {
        return true; // String found in a group
      }
    }
    currentGroup = currentGroup->next;
  }
  return false; // String not found in any group
}

/*
 * Función: printGroupList
 * Imprime la lista de grupos.
 *
 * Descripción:
 * Esta función imprime la lista de grupos generados anteriormente. Recorre la lista de grupos desde el inicio
 * hasta el final, imprimiendo el número de grupo y los nombres de los vértices que pertenecen a cada grupo.
 * Dentro de cada grupo, se itera sobre el arreglo de nombres de vértices ("turns") y se imprime cada nombre en
 * una línea separada. Al final de cada grupo, se imprime una línea en blanco para separar los grupos visualmente.
 *
 * Parámetros:
 * - groupList: Puntero a la lista de grupos que se imprimirá.
 *
 * Retorno: Ninguno.
 */
void printGroupList(GroupList *groupList) {
  Group *currentGroup = groupList->head;
  int groupCount = 1;

  printf("Grupos de cruces:\r\n\n");
  while (currentGroup != NULL) {
    printf("Fase %d:\r\n", groupCount);
    for (int i = 0; i < currentGroup->numTurns; i++) {
      printf(" %s\r\n", currentGroup->turns[i]);
    }
    printf("\r\n");
    currentGroup = currentGroup->next;
    groupCount++;
  }
}

/*
    Función: createGroups
    Crea grupos de vértices en el grafo.
    Descripción:
    Esta función crea grupos de vértices en el grafo utilizando un algoritmo de
   búsqueda y asignación de nodos. Inicialmente, se crea una lista de grupos
   vacía. Luego, se itera hasta que todos los vértices hayan sido agregados a
   los grupos o hasta que se haya recorrido todos los nodos del grafo. Durante
   cada iteración, se crea un arreglo dinámico de nodos llamado "groupNodes"
   para almacenar los nombres de los vértices que serán parte de un grupo. Se
   inicializa un contador de nodos agregados ("groupNodesCount") y se crea una
   cola de nodos incompatibles
    ("incompatibleNodes"). A continuación, se recorren los vértices restantes en
   el grafo a partir del último nodo buscado ("searchedNodes"). Si un vértice ya
   se encuentra en un grupo existente, se omite y se pasa a la siguiente
    iteración. De lo contrario, se agrega el vértice al grupo actual si no está
   en la cola de nodos incompatibles, incrementando el contador de nodos
   agregados. Luego, se agregan los nodos adyacentes al vértice actual a la cola
    de nodos incompatibles. Después de procesar todos los vértices restantes, se
   guarda el grupo actual en la lista de grupos. El proceso continúa hasta que
   se hayan agregado todos los vértices al menos una vez, o hasta que se haya
   recorrido todos los nodos del grafo. Finalmente, se imprime la lista de
   grupos y se liberan los recursos utilizados por los grupos y el grafo.
    Parámetros:
        graph: Puntero al grafo en el que se crearán los grupos.
    Retorno: Ninguno.
    */
void createGroups(Graph *graph) {

  GroupList groupList;
  groupList.head = NULL;
  groupList.tail = NULL;

  bool allVerticesAdded = false;

  int vertexAdded = 0;
  int searchedNodes = 0;
  while (!allVerticesAdded && searchedNodes < graph->numVertices) {
    char **groupNodes =
        (char **)malloc((graph->numVertices + 1) * sizeof(char *));
    memset(groupNodes, 0, (graph->numVertices + 1) * sizeof(char *));

    int groupNodesCount = 0;
    Queue *incompatibleNodes = createQueue();
    for (int i = searchedNodes; i < graph->numVertices; i++) {
      // Si graph->adjacencyList[i]->name existe en un grupo, continuar
      // con la siguiente iteracion
      if (isStringInGroups(&groupList, graph->adjacencyList[i]->name)) {
        continue;
      }

      // Añadir vertice al grupo
      if (!isPartOfQueue(incompatibleNodes, graph->adjacencyList[i])) {
        groupNodes[groupNodesCount] = strdup(graph->adjacencyList[i]->name);
        groupNodesCount++;
        vertexAdded++;
      }

      // Añadir los nodos adjacentes
      Node *currentNode = graph->adjacencyList[i]->next;
      while (currentNode != NULL) {
        enqueue(incompatibleNodes, currentNode);
        currentNode = currentNode->next;
      }
    }
    // guardar Grupo
    addGroup(&groupList, groupNodes, groupNodesCount);
    allVerticesAdded = (vertexAdded == graph->numVertices);

    searchedNodes++;
    free(incompatibleNodes);
  }
  printGroupList(&groupList);

  Group *currentGroup = groupList.head;
  while (currentGroup != NULL) {
    for (int i = 0; i < currentGroup->numTurns; i++) {
      free(currentGroup->turns[i]);
    }
    free(currentGroup->turns);

    Group *nextGroup = currentGroup->next;
    free(currentGroup);
    currentGroup = nextGroup;
  }
}

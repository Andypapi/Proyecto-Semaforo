#ifndef TRAFFIC_LIGHTS_H
#define TRAFFIC_LIGHTS_H

#include "graph.h"
#include <stdbool.h>

// Estructuras
typedef struct Group {
  int numTurns;
  char **turns;
  struct Group *next;
} Group;

typedef struct GroupList {
  Group *head;
  Group *tail;
} GroupList;

typedef struct QueueNode {
  Node *data;
  struct QueueNode *next;
} QueueNode;

typedef struct Queue {
  QueueNode *front;
  QueueNode *rear;
} Queue;

// Funciones a implementar en traffic_lights.c
void createGroups(Graph *graph);
void addGroup(GroupList *groupList, char **groupNodes, int groupCount);
bool isStringInGroups(GroupList *groupList, const char *searchString);
void printGroupList(GroupList *groupList);
int isCompatible(Group *group, Node *node, Graph *graph);

QueueNode *createQueueNode(Node *data);
Queue *createQueue();
void enqueue(Queue *queue, Node *data);
Node *dequeue(Queue *queue);
bool isQueueEmpty(Queue *queue);
bool isPartOfQueue(Queue *queue, Node *node);

#endif

#include "graph.h"
#include "traffic_lights.h"
#include "user_interface.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  iniciarMenu();
  return 0;
}
/*
int main(int argc, char *argv[]) {
  char filename[15];
  printf("Enter the name of the data file: ");
  scanf("%s", filename);
  Graph *graph = readGraphFromFile(filename);

  if (graph == NULL) {
    printf("Error: couldn't read from file.\n");
    return 1;
  }

  TrafficLights *trafficLights = createTrafficLights();
  trafficLights->graph = graph;
  buildGroups(trafficLights);

  printf("----------------------------------------\n");
  printTrafficLights(trafficLights);
  printf("----------------------------------------\n");

  destroyTrafficLights(trafficLights);
  return 0;
}
*/

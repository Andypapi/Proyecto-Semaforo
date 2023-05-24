#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "graph.h"

void disableRawMode();
void enableRawMode();
void drawGraph(Graph *graph);
void drawMenu();
void processKeypress(char c);

void clearScreen();

int iniciarMenu();
#endif

#include "user_interface.h"
#include "graph.h"
#include "traffic_lights.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>

#include <ctype.h>

// Macros
#define CTRL_KEY(k) ((k)&0x1f)
#define SEQUENCE(k, p) write(STDOUT_FILENO, (k), (p))

// Colores
#define RESALTAR "\x1b[30m\x1b[47m"
#define RESET_COLOR "\x1b[0m"

struct termios orig_terminal;


// Variables globales para el menu
Graph *graph;
char *option[] = {"Imprimir grafo", "Mostrar Cruces"};
int numOptions = 2;
int selectedOption = 0;
bool inMenu = true;

void disableRawMode() {
  SEQUENCE("\x1b[?25h", 6); // Muestra el cursor en la terminal
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_terminal);
}

void enableRawMode() {

  SEQUENCE("\x1b[?25l", 6); // Oculta el cursor en la terminal

  tcgetattr(STDIN_FILENO, &orig_terminal);
  atexit(disableRawMode);

  struct termios raw = orig_terminal;
  raw.c_iflag &= ~(ICRNL | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void clearScreen() {
  SEQUENCE("\x1b[2J", 4);
  SEQUENCE("\x1b[H", 3);
}


void processKeypress(char c) {
  if (c == '\x1b') { // Revisa si la tecla presionada es una `Escape sequence`
                     // Indicando la posibilidad de una sequencia de flecha
    char seq[3];
    if (read(STDIN_FILENO, &seq[0], 1) != 1 ||
        read(STDIN_FILENO, &seq[1], 1) != 1)
      return;

    if (seq[0] == '[') {
      switch (seq[1]) {
      // Flecha hacia arriba
      case 'A':
        if (selectedOption > 0) {
          selectedOption--;
        }
        break;
      // Flecha hacia abajo
      case 'B':
        if (selectedOption < 2 - 1) {
          selectedOption++;
        }
        break;
      }
    }
  } else {
    switch (c) {
    case CTRL_KEY('q'):
      clearScreen();
      exit(0);
      break;
    case 13:
      if (selectedOption == 0) {
        drawGraph(graph);
        inMenu = false;
      }
      if (selectedOption == 1) {
        createGroups(graph);
        inMenu = false;
      }
      break;
    }
  }
}

void drawMenu() {
  // Opciones
  printf("╔═══════════════════╗\r\n");
  for (int i = 0; i < 2; i++) {
    printf("║");
    if (i == selectedOption) {
      printf(">> ");
    } else {
      printf("   ");
    }
    printf("%s  ║\r\n", option[i]);
  }
  printf("╚═══════════════════╝\r\n");
}

void drawGraph(Graph *graph) {
  printf("        Grafo     \r\n");
  printf("═════════════════════════════════════════════════════════════════════"
         "═══\r\n");
  for (int i = 0; i < graph->numVertices; i++) {
    Node *currentNode = graph->adjacencyList[i];
    printf("╔══════╗\r\n");
    printf("║");
    printf(" %s ", graph->adjacencyList[i]->name);
    printf("║\r\n");

    printf("╚═══╦══╝\r\n");
    printf("    ╚═══════");
    while (currentNode != NULL) {
      printf("════");
      printf("║ %s ║", currentNode->name);
      currentNode = currentNode->next;
    }
    printf("\r\n");
  }
  printf("\nPresione " RESALTAR "Esc" RESET_COLOR
         " para regresar al menu.\r\n");
}


int iniciarMenu() {
  char filename[15];
  clearScreen();
  printf("Ingrese el nombre del archivo de datos: ");
  scanf("%s", filename);
  graph = readGraphFromFile(filename);
  enableRawMode();
  printf("Guia: Use las flechas para moverse por el menu | Presione Enter para "
         "seleccionar\r\n\n");
  drawMenu();
  char c;
  while (read(STDIN_FILENO, &c, 1) == 1) {
    clearScreen();
    printf("Guia: Use las flechas para moverse por el menu | Presione Enter "
           "para seleccionar\r\n\n");
    drawMenu();
    if (inMenu) {
      processKeypress(c);
    } else {
      if (c == 27) {
        clearScreen();
        inMenu = true;
      }
    }
  }
  for (int i = 0; i < graph->numVertices; i++) {
    Node *currentNode = graph->adjacencyList[i];
    Node *nextNode;
    while (currentNode != NULL) {
      nextNode = currentNode->next;
      free(currentNode);
      currentNode = nextNode;
    }
  }
  free(graph->adjacencyList);

  return 0;
}

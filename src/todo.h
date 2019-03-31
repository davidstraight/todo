#ifndef TODO_H
#define TODO_H
typedef struct state {
  sqlite3 *database;
  char *filename;
  int command;
  char *todoText;
  char *todoID;
  char *message;
} state;

enum COMMANDS {
  ADD_TODO,
  DELETE_TODO,
  LIST_TODOS
};

void die(char *format, ...);
void parseForCommandLineOptions(state *stateIn, int argc, char **argv);
void setFilenameFromEnvironment(state *stateIn);

void doCommand(state *stateIn);

void printHelp();

#endif

#ifndef TODO_H
#define TODO_H
typedef struct {
  int id;
  char *title;
  char *notes;
  char *due;

} Todo ;

typedef struct {
  sqlite3 *database;
  char *filename;
  int command;
  Todo todo;
} State;

enum COMMANDS {
  ADD_TODO,
  DELETE_TODO,
  LIST_TODOS
};

void die(char *format, ...);
void parseForCommandLineOptions(State *state, int argc, char **argv);
void setFilenameFromEnvironment(State *state);

void doCommand(State *state);

void printHelp();

#endif

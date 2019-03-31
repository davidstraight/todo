#include <stdio.h>
#include <sqlite3.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

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
void openDB(state *stateIn);
void doCommand(state *stateIn);
void addTodo(state *stateIn);
void deleteTodo(state *stateIn);
void listTodos(state *stateIn);
void printHelp();

int main(int argc, char **argv)
{
  struct state appState = {0};
  parseForCommandLineOptions(&appState, argc, argv);
  if (!appState.filename) {
    setFilenameFromEnvironment(&appState);
  }
  openDB(&appState);
  doCommand(&appState);
  sqlite3_close(appState.database);
  return 0;
}

void doCommand(state *stateIn)
{
  switch (stateIn->command)
  {
    case ADD_TODO:
      addTodo(stateIn);
      break;
    case DELETE_TODO:
      deleteTodo(stateIn);
      break;
    case LIST_TODOS:
      listTodos(stateIn);
      break;
    default:
      printf("not a valid command\n");
      printHelp();
      break;
  }
}

void openDB(state *stateIn)
{
  int returnCode = sqlite3_open(stateIn->filename, &(stateIn->database));
  if (returnCode){
    sqlite3_close(stateIn->database);
    die("Can't open database: %s\n", sqlite3_errmsg(stateIn->database));
  }
}

void die(char* format, ...)
{
  va_list vargs;
  va_start (vargs, format);
  vfprintf (stderr, format, vargs);
  fprintf (stderr, ".\n");
  va_end (vargs);
  exit (1);
}

void parseForCommandLineOptions(state *stateIn, int argc, char** argv)
{
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i],"--help") == 0) {
      printHelp();
    }

    if (strcmp(argv[i], "-f") == 0 && argc > i + 1) {
      stateIn->filename = argv[i + 1];
      i++;
      break;
    }

    if (strcmp(argv[i], "add") == 0 && argc > i + 1) {
      stateIn->command = ADD_TODO;
      stateIn->todoText = argv[i + 1];
      return;
    }

    if (strcmp(argv[i], "delete") == 0 && argc > i + 1) {
      stateIn->command = DELETE_TODO;
      stateIn->todoID = argv[i + 1];
      return;
    }

    if (strcmp(argv[i], "list") == 0) {
      stateIn->command = LIST_TODOS;
      return;
    }
  }
    printHelp();
}

void setFilenameFromEnvironment(state *stateIn)
{
  char *envPath = NULL;
  char *openFile = NULL;
  char filename[] = "/.todo.sql";
  envPath = getenv("HOME");
  if (envPath == NULL) {
    die("Cannot get HOME directory from environment");
  }

  openFile = (char*) malloc(strlen(envPath) + strlen(filename) + 1);
  if (!openFile) {
    die("Cannot allocate memory");
  }
  openFile = strcat(openFile, envPath);
  openFile = strcat(openFile, filename);
  stateIn->filename = openFile;

}

void addTodo(state *stateIn)
{
  /*returnCode = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);
  if( rc!=SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  */
  printf("added todo: %s\n", stateIn->todoText);
}

void deleteTodo(state *stateIn)
{
  printf("delete todo: %s\n", stateIn->todoID);
}

void listTodos(state *stateIn)
{
  printf("list todos\n");
}

void printHelp()
{
  char *helpMessage =
  "Usage: todo [-h --help] [-f <filename>] \n"
  "<command> [<arg>]\n";
  printf("%s", helpMessage);
  exit(0);
}

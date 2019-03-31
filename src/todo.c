#include <stdio.h>
#include <sqlite3.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "todo.h"
#include "database.h"



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



void printHelp()
{
  char *helpMessage =
  "Usage: todo [-h --help] [-f <filename>] \n"
  "<command> [<arg>]\n";
  printf("%s", helpMessage);
  exit(0);
}

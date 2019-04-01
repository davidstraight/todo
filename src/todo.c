#include <stdio.h>
#include <sqlite3.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "todo.h"
#include "database.h"



int main(int argc, char **argv)
{
  State state = {0};
  parseForCommandLineOptions(&state, argc, argv);
  if (!state.filename) {
    setFilenameFromEnvironment(&state);
  }
  openDB(&state);
  createTables(&state);
  doCommand(&state);
  sqlite3_close(state.database);
  return 0;
}

void doCommand(State *state)
{
  switch (state->command)
  {
    case ADD_TODO:
      addTodo(state);
      break;
    case DELETE_TODO:
      deleteTodo(state);
      break;
    case LIST_TODOS:
      listTodos(state);
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

void parseForCommandLineOptions(State *state, int argc, char** argv)
{
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i],"--help") == 0) {
      printHelp();
    }

    if (strcmp(argv[i], "-f") == 0 && argc > i + 1) {
      state->filename = argv[i + 1];
      i++;
      continue;
    }

    if (strcmp(argv[i], "add") == 0 && argc > i + 1) {
      state->command = ADD_TODO;
      state->todo.title = argv[i + 1];
      return;
    }

    if (strcmp(argv[i], "delete") == 0 && argc > i + 1) {
      state->command = DELETE_TODO;
      state->todo.id = atoi(argv[i + 1]);
      return;
    }

    if (strcmp(argv[i], "list") == 0) {
      state->command = LIST_TODOS;
      return;
    }
  }
    printHelp();
}

void setFilenameFromEnvironment(State *state)
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
  state->filename = openFile;

}



void printHelp()
{
  char *helpMessage =
  "Usage: todo [-h --help] [-f <filename>] \n"
  "<command> [<arg>]\n"
  "commands are:\n"
  "  add\n"
  "  list\n"
  "  delete\n";
  printf("%s", helpMessage);
  exit(0);
}

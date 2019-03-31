#include <stdio.h>
#include <sqlite3.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "todo.h"


void openDB(state *stateIn)
{
  int returnCode = sqlite3_open(stateIn->filename, &(stateIn->database));
  if (returnCode){
    sqlite3_close(stateIn->database);
    die("Can't open database: %s\n", sqlite3_errmsg(stateIn->database));
  }
}



void createTables(state *stateIn)
{
  char tableExistsQuery[] = "SELECT name FROM sqlite_master WHERE type='table' AND name=?";
  int result = 0;
  sqlite3_stmt *statement = NULL;
  const char *tail = NULL;
  result = sqlite3_prepare_v2(stateIn->database, tableExistsQuery, strlen(tableExistsQuery), &statement, &tail);

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

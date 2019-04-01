#include <stdio.h>
#include <sqlite3.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "todo.h"


void openDB(State *state)
{
  int returnCode = sqlite3_open(state->filename, &(state->database));
  if (returnCode){
    sqlite3_close(state->database);
    die("Can't open database: %s\n", sqlite3_errmsg(state->database));
  }
}



void createTables(State *state)
{
  int result = 0;
  sqlite3_stmt *statement = NULL;
  const char *tail = NULL;
  char createTableQuery[] = "CREATE TABLE IF NOT EXISTS todo (id INTEGER PRIMARY KEY, title TEXT NOT NULL, notes TEXT, due DATETIME)";
  result = sqlite3_prepare_v2(state->database, createTableQuery, -1, &statement, &tail);
  if (result != SQLITE_OK) {
    die("error preparing query\n");
  }
  result = sqlite3_step(statement);
  if (result != SQLITE_DONE) {
    die("error executing statement\n");
  }
}

void addTodo(State *state)
{
  int result = 0;
  sqlite3_stmt *statement = NULL;
  const char *tail = NULL;
  char addTodoQuery[] = "INSERT INTO todo (title, notes, due) VALUES (?,?,?)";
  result = sqlite3_prepare_v2(state->database, addTodoQuery, -1, &statement, &tail);
  if (result != SQLITE_OK) {
    die("error preparing query\n");
  }
  result = sqlite3_bind_text(statement, 1, state->todo.title, -1, SQLITE_STATIC);
  if (result != SQLITE_OK) {
    die("error binding text\n");
  }
  result = sqlite3_bind_text(statement, 2, state->todo.notes, -1, SQLITE_STATIC);
  if (result != SQLITE_OK) {
    die("error binding text\n");
  }
  result = sqlite3_bind_text(statement, 3, state->todo.due, -1, SQLITE_STATIC);
  if (result != SQLITE_OK) {
    die("error binding text\n");
  }
  result = sqlite3_step(statement);
  if (result != SQLITE_DONE) {
    die("error executing statement\n");
  }

  printf("added todo: %s\n", state->todo.title);
}

void deleteTodo(State *state)
{
  char deleteTodoQuery[] = "DELETE FROM todo WHERE id = ?";
  printf("delete todo: %d\n", state->todo.id);
}

void listTodos(State *state)
{
  char listTodoQuery[] = "SELECT * FROM todo";
  printf("list todos\n");
}

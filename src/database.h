#ifndef TODO_DATABASE_H
#define TODO_DATABASE_H

#include "todo.h"

void openDB(State *state);
void addTodo(State *state);
void deleteTodo(State *state);
void listTodos(State *state);
void createTables(State *state);
#endif

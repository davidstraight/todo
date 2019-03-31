#ifndef TODO_DATABASE_H
#define TODO_DATABASE_H
/*extern struct state;*/
#include "todo.h"

void openDB(state *stateIn);
void addTodo(state *stateIn);
void deleteTodo(state *stateIn);
void listTodos(state *stateIn);
#endif

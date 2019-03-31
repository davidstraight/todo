CC=gcc
CFLAGS=
OUTPUT=todo
LINK=-lsqlite3
OBJS= database.o todo.o

database.o: database.c
	$(CC) -c -o database.o database.c

todo.o: todo.c
	$(CC) -c -o todo.o todo.c

debug:$(OBJS)
	$(CC) -o $(OUTPUT) -g $(OBJS) $(LINK)

clean:
	@echo "Cleaning up..."
	rm *.o a.out todo

CC=g++
CFLAGS=-Wall -O2 -std=c++11
OBJECTS=main.o validity.o string_funcs.o parser.o shell_commands.o process.o
DIR1=src/helpers/
DIR2=src/objs/
INC=$(DIR1)
INC+=$(DIR2)
INC_PARAMS=$(foreach d, $(INC), -I$d)

shell379: $(OBJECTS)
	$(CC) -o shell379 $(OBJECTS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp $(INC_PARAMS) -o main.o

validity.o: $(DIR1)validity.cpp
	$(CC) $(CFLAGS) -c $(DIR1)validity.cpp $(INC_PARAMS) -o validity.o

string_funcs.o: $(DIR1)string_funcs.cpp
	$(CC) $(CFLAGS) -c $(DIR1)string_funcs.cpp -o string_funcs.o

parser.o: $(DIR1)parser.cpp
	$(CC) $(CFLAGS) -c $(DIR1)parser.cpp $(INC_PARAMS) -o parser.o

shell_commands.o: $(DIR1)shell_commands.cpp
	$(CC) $(CFLAGS) -c $(DIR1)shell_commands.cpp $(INC_PARAMS) -o shell_commands.o

process.o: $(DIR2)process.cpp
	$(CC) $(CFLAGS) -c $(DIR2)process.cpp $(INC_PARAMS) -o process.o

clean:
	$(RM) shell379 *.o

CC=g++
CFLAGS=-Wall -O2
OBJECTS=main.o validity.o string_funcs.o
DIR1=src/helpers/
INC=$(DIR1)
INC_PARAMS=$(foreach d, $(INC), -I$d)

shell379: $(OBJECTS)
	$(CC) -o shell379 $(OBJECTS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp $(INC_PARAMS) -o main.o

validity.o: $(DIR1)validity.cpp
	$(CC) $(CFLAGS) -c $(DIR1)validity.cpp $(INC_PARAMS) -o validity.o

string_funcs.o: $(DIR1)string_funcs.cpp
	$(CC) $(CFLAGS) -c $(DIR1)string_funcs.cpp -o string_funcs.o

clean:
	rm shell379 *.o

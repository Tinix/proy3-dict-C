CC       = gcc
TARGET   = dictionary
CFLAGS   = -Wall -Werror -Wextra -pedantic -std=c99 -g
VALGRIND = valgrind --leak-check=full --show-reachable=yes
SOURCES  = $(wildcard *.c)
HEADERS  = $(wildcard *.h)
OBJECTS  = $(SOURCES:.c=.o)

.PHONY : clean cleanall indent programa tar valgrind

$(TARGET) :
	$(CC) $(CFLAGS) -c $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

clean :
	rm -f $(TARGET) $(OBJECTS)

valgrind : $(TARGET)
	$(VALGRIND) ./$(TARGET)

# Antes de entregar, cambiar .PHONY, borrar HEADERS y borrar lo que sigue:
cleanall : clean
	rm -rf _original _indent
	rm -f *.c~ *.h~ *.dic jaime.tar.gz

indent :
	mkdir _original _indent
	cp $(SOURCES) $(HEADERS) _original
	cp $(SOURCES) $(HEADERS) _indent
	indent -kr -nut -brf -cli4 -l79 _indent/*
	meld _original _indent &

tar :
	tar czfv jaime.tar.gz bst.c list.c dict.c pair.c main.c

CC       = gcc
TARGET   = dictionary
CFLAGS   = -Wall -Werror -Wextra -pedantic -std=c99 -g
VALGRIND = valgrind --leak-check=full --show-reachable=yes
SOURCES  = $(wildcard *.c)
HEADERS  = $(wildcard *.h)
OBJECTS  = $(SOURCES:.c=.o)

.PHONY : valgrind tar indent clean cleanall

$(TARGET) :
	$(CC) $(CFLAGS) -c $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

clean :
	rm -f $(TARGET) $(OBJECTS)

valgrind : $(TARGET)
	$(VALGRIND) ./$(TARGET)

# Antes de entregar, cambiar .PHONY y borrar HEADERS, tar, indent y cleanall.
tar :
	tar czfv jaime.tar.gz bst.c list.c dict.c pair.c main.c

indent :
	mkdir _original _indent
	cp $(SOURCES) $(HEADERS) _original
	cp $(SOURCES) $(HEADERS) _indent
	indent -kr -nut -brf -cli4 -l79 _indent/*
	meld _original _indent &

cleanall : clean
	rm -rf _original _indent
	rm -f *.c~ *.h~ *.dic jaime.tar.gz

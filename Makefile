CC = gcc
CFLAGS = -march=native -Ofast

LIBDIR = libs
OBJDIR = obj

all: main

main: $(OBJDIR)/main.o
	$(CC) $(OBJDIR)/main.o -o main $(CFLAGS) -I$(LIBDIR)

$(OBJDIR)/main.o: main.c $(LIBDIR)/*.h
	$(CC) main.c -o $(OBJDIR)/main.o -c $(CFLAGS) -I$(LIBDIR)

run: all
	./main.exe

.PHONY: clean
clean:
	rm $(OBJDIR)/*
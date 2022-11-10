ROOTNAME=main
OUTPUT=$(ROOTNAME)
RUNOPTIONS=
CC=gcc
CFLAGS= -g -I.
# To add libraries, add "-l <libname>", for multiple repeat prior for each lib.
LIBS = -lpigpio -lrt -lpthread -lm
DEPS = 
ADDOBJ= sensor.o
OBJ = $(OUTPUT).o $(ADDOBJ)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTPUT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f *.o $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT) $(RUNOPTIONS)

ROOTNAME=main
OUTPUT=$(ROOTNAME)
RUNOPTIONS=
CC=gcc
CFLAGS= -g -I. -DUSE_DEV_LIB
# To add libraries, add "-l <libname>", for multiple repeat prior for each lib.
LIBS = -lpigpio -lrt -lpthread -lm
DEPS = 
ADDOBJ= sensor.o DEV_Config.o PCA9685.o dev_hardware_i2c.o sysfs_gpio.o 
OBJ = $(OUTPUT).o $(ADDOBJ)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTPUT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f *.o $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT) $(RUNOPTIONS)

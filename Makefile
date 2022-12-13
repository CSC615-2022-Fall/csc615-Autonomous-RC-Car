# Root MakeFile
# ----------------- Configurations -----------------
# 
# ROOTNAME is the main c file.
ROOTNAME   = main
# OUTPUT is the executable file.
OUTPUT     = $(ROOTNAME)
RUNOPTIONS =
CC         = gcc
CFLAGS     = -g -I. -DUSE_DEV_LIB
# To add libraries, add "-l <libname>", for multiple repeat prior for each lib.
LIBS       = -lpigpio -lrt -lpthread -lm

DIR_O      = $(CURDIR)/bin

# Modify DEPS based on what main needs
# For example: Let's say that the main file requires sensor.c
# DEPS       = sensor
# NOTE: This DEPS isn't compiled here. DEPS files should be compiled in subdir
DEPS       = MotorDriver DEV_Config dev_hardware_i2c sysfs_gpio PCA9685 MotorDriver \
				SensorDriver ThreadSensor

ADD_FILE   = $(OUTPUT)
#
# ----------------- End of Configurations -----------------

# Exports environment variables and pass it to subdirectories' makefile
# This way, we don't need to worry about it setting them again there.
export CC
export CFLAGS
export LIBS
export DIR_O
export RUNOPTIONS
export DEPS

# Appends object directory and also appends .o extension to ADD_FILE
O_FILE = $(patsubst %,$(DIR_O)/%.o,$(ADD_FILE))
OBJ = $(O_FILE)

# Converts DEPS path to DIR_O/{input}.o
# Same way as O_FILE
DEPS_PATH = $(patsubst %,$(DIR_O)/%.o,$(DEPS))

# Compiles dependencies first(subdir) and the the current folder
all: deps $(OUTPUT)

# Compiles dependencies from subdirectories
# NOTE: add/delete subdirectories
# For example: if you want to add a ./src folder in the current directory
# Then you should append this line below
# $(MAKE) -C ./src
deps:
	$(MAKE) -C ./src

$(DIR_O)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTPUT): $(OBJ) $(DEPS_PATH)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

turncal: deps TurnCalibrate

TurnCalibrate: $(patsubst %,$(DIR_O)/%.o,TurnCalibrate) $(DEPS_PATH)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(DIR_O)/*.o $(OUTPUT)

run: deps $(OUTPUT)
	./$(OUTPUT) $(RUNOPTIONS)

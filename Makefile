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
DEPS       = 

DIR_O      = $(PWD)/bin

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

# Compiles dependencies first(subdir) and the the current folder
all: deps $(OBJ)

# Compiles dependencies from subdirectories
# NOTE: add/delete subdirectories
# For example: if you want to add a ./src folder in the current directory
# Then you should append this line below
# $(MAKE) -C ./src
deps:
	$(MAKE) -C ./src

$(DIR_O)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTPUT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(DIR_O)/*.o $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT) $(RUNOPTIONS)


# TODO: https://stackoverflow.com/questions/1277685/organize-project-and-specify-directory-for-object-files-in-makefile
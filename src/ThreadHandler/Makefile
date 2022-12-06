# Instructions:
# This is a template for compiling the c files to object
# You can copy this file to the subdirectories that you want
#
# NOTE: If you're modifying  the main.c file' depencencies,
# then you should also modify the makefile in the main directory.
# This is because this file doesn't handle linking.
# Linking is done in the main directory.
#
# -- Prerequisites --
# Make sure to name this file as Makefile
#
# -- Adding Files for compilation --
# Add your file names to ADD_FILE for compilation
#   * NOTE: don't add extensions(.c)
#
# -- Adding/deleting subdirectories to compile --
# 1) Copy this template to the subdirectories.
# 2) If you want to add subdirectories checkout deps
#
# ----------------- Configurations -----------------
#
# Example, let's say we want to add foo.c and bar.c
# ADD_FILE   = foo bar
ADD_FILE   = ThreadSensor
#
# ----------------- End of Configurations -----------------

# Appends object directory and also appends .o extension to ADD_FILE
O_FILE = $(patsubst %,$(DIR_O)/%.o,$(ADD_FILE))
OBJ = $(O_FILE)

# Compiles dependencies first(subdir) and the the current folder
all: deps $(OBJ)

# Compiles dependencies from subdirectories
# NOTE: add/delete subdirectories
# For example: if you want to add a ./src folder in the current directory
# Then you should append this line below deps:
# $(MAKE) -C ./src
deps:

$(DIR_O)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(DIR_O)/*.o $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT) $(RUNOPTIONS)
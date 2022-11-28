# Instructions:
# You can copy this file to the subdirectories that you want
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
ADD_FILE   =  DEV_Config PCA9685 dev_hardware_i2c
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
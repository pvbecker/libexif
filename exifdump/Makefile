# specifies the compiler.
$(CC)=gcc
# specifies the archiver (for static libraries)
$(AR)=ar

# specifies names for easier work
SRC_DIR=src
OUT_DIR=build
C_FLAGS=-fPIC

INCPATH=inc/

# By looking into https://www.gnu.org/software/make/manual/html_node/index.html#SEC_Contents, one
# finds a bunch of Makefile utilities that have already been implemented by make that makes life a
# lot easier. For instance, instead of keeping track of every single file to be created and added to
# a list, one can simply define a directory that will contain all implementation files (.c in this
# case) and place them all in a variable as below
SRCS=$(wildcard $(SRC_DIR)/*.c)

# The result of this call will be a bunch of relative paths to the Makefile's location to .c files
# as space-separated values. This is shown in the @echo $(SRCS). Now, looking at the same documenta-
# tion listed above, one stumbles on this pattern substitution rule, which can come in handy.
OBJS=$(subst $(SRC_DIR), $(OUT_DIR), $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRCS)))

EXECUTABLE=$(OUT_DIR)/exifdump


all: $(EXECUTABLE)
	@echo All done!

clean:
	@echo Removing build/ directory...
	@rm -rf build
	@echo Done with clean.

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
# 	used this '-p' argument here in order to always create a directory and not fail in case the dir
# 	already exists, even tho this was explicitly defined as a 'don't' in the official documentation.
	@mkdir -p $(OUT_DIR)
	@echo compiling $^...
	$(CC) -c $< $(C_FLAGS) -o $@

$(EXECUTABLE): $(OBJS)
	@echo compiling $@...
	$(CC) -L$(LIBPATH) -I$(INCPATH) -lexif $^ -o $@
# This is a possibility, but a bad one. It will require the file to search for the shared library at
# the path in which we specify to the linker (goes into the elf header). -Wl is to send commands to
# the linker via comma-separated strings/values,
# 	$(CC) -L$(LIBPATH) -lexif -Wl,-rpath=$(LIBPATH) $^ -o $@


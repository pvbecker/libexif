# specifies the compiler.
$(CC)=gcc
# specifies the archiver (for static libraries)
$(AR)=ar

# specifies names for easier work
SRC_DIR=src
OUT_DIR=build
C_FLAGS=-fPIC

# By looking into https://www.gnu.org/software/make/manual/html_node/index.html#SEC_Contents, one
# finds a bunch of Makefile utilities that have already been implemented by make that makes life a
# lot easier. For instance, instead of keeping track of every single file to be created and added to
# a list, one can simply define a directory that will contain all implementation files (.c in this
# case) and place them all in a variable as below
SRCS=$(wildcard $(SRC_DIR)/*.c)

# The result of this call will be a bunch of relative paths to the Makefile's location to .c files
# as space-separated values. This is shown in the @echo $(SRCS). Now, looking at the same documenta-
# tion listed above, one stumbles on this pattern substitution rule, which can come in handy.
# OBJS=$(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRCS))
OBJS=$(subst $(SRC_DIR), $(OUT_DIR), $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRCS)))
# only considering source files that are related to the exif library, i.e., remove main.c (test app
# source file).
LIB_OBJS=$(filter-out $(SRC_DIR)/main.o, $(OBJS))

EXECUTABLE=$(OUT_DIR)/test


all: $(EXECUTABLE)
	@echo All done!

# According to the official GNU Make reference manual (https://www.gnu.org/software/make/manual/make.html),
#  since the rule 'clean' does not operate over any files, one should note that if ever a file named
# 'clean' is created, this recipe would never operate properly. By invoking '$ make clean' over the
# terminal with a file named clean in the path, since the recipe has no prerequisites, it would
# always be considered up-to-date with the file and would not be executed. In order to circumvent
# this issue, we can declare the recipe as a phony recipe, meaning that it does not demands a
# filename to be triggered.
.PHONY: clean
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
	$(CC) $^ -o $@

# use archiver to create a static library. Options to be used are found in the manual page of the ar
# application:
# r: insert the files fed as input arguments (named 'members' on the manual page) into the archive
#    that will be created.
# c: creates archive. Archive is always created.
# s: add an index to the archive  or update it if already exists.
static: $(LIB_OBJS)
	@echo creating static library libexif.a...
	$(AR) rcs $(OUT_DIR)/libexif.a $^

# shared libraries are to be composed of objects compiled with the flag -fpic (position independent
# code), meaning that these will behave as expected for shared libraries: an given object will be
# loaded to memory and their symbol table will be loaded to be used by the requesting program /
# resource.
shared: $(LIB_OBJS)
	@echo creating dynamic library libexif.so...
	$(CC) -shared $^ -o $(OUT_DIR)/libexif.so

binary: $(OBJS)
	@echo creating test executable...
	$(CC) $^ -o $(OUT_DIR)/test


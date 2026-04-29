# Compiler & tools
CC      = gcc
FLEX    = flex
YACC    = yacc
CFLAGS  = -Wall -Wextra -g

# Filenames
LEX_SRC = task1.l
YAC_SRC = task1.y
TREE_SRC = tree.c
TREE_HDR = tree.h
REGISTER_SRC = register.c
REGISTER_HDR = register.h
MEMORY_SRC = memory.c
MEMORY_HDR = memory.h
LABEL_SRC = labels.c
LABEL_HDR = labels.h
CODEGENERATION_SRC = codegeneration.c
CODEGENERATION_HDR = codegeneration.h
HELPER_SRC = yacc-helper.c
HELPER_HDR = yacc-helper.h
TYPE_TABLE_SRC = typetable.c
TYPE_TABLE_HDR = typetable.h
CLASS_TABLE_SRC = classtable.c
CLASS_TABLE_HDR = classtable.h

# Executable
TARGET  = stage-final

# Generated
LEX_OUT = lex.yy.c
YAC_OUT = y.tab.c
YAC_HDR = y.tab.h


# Default build
all: $(TARGET)

# Build the parser executable
$(TARGET): $(LEX_OUT) $(YAC_OUT) $(TREE_SRC) $(TREE_HDR) $(MEMORY_SRC) $(MEMORY_HDR) $(REGISTER_SRC) $(REGISTER_HDR) $(LABEL_SRC) $(LABEL_HDR) $(CODEGENERATION_SRC) $(CODEGENERATION_HDR) $(HELPER_SRC) $(HELPER_HDR) $(TYPE_TABLE_SRC) $(TYPE_TABLE_HDR) $(CLASS_TABLE_SRC) $(CLASS_TABLE_HDR) 
	$(CC) $(CFLAGS) $(LEX_OUT) $(YAC_OUT) $(TREE_SRC) $(MEMORY_SRC) $(REGISTER_SRC) $(LABEL_SRC) $(CODEGENERATION_SRC) $(HELPER_SRC) $(TYPE_TABLE_SRC) $(CLASS_TABLE_SRC) -o $(TARGET)


# Generate lex.yy.c from the lexer
$(LEX_OUT): $(LEX_SRC) $(YAC_HDR)
	$(FLEX) $(LEX_SRC)

# Generate y.tab.c and y.tab.h from the parser
$(YAC_OUT) $(YAC_HDR): $(YAC_SRC)
	$(YACC) -d $(YAC_SRC)

# Clean generated and compiled files
clean:
	rm -f $(TARGET) \
	      $(LEX_OUT) \
	      $(YAC_OUT) \
	      $(YAC_HDR) \
	      *.o \
		  *.xsm


# Phony targets
.PHONY: all clean

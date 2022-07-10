#ifndef _NTR_DEFAULTS_H_
#define _NTR_DEFAULTS_H_ 1

const char *MakefileDef =
		"CC = clang\n"
		"\n"
		"PNAME = c\n"
		"\n"
		"SRC  = $(shell find src -name \"*.c\")\n"
		"OBJ  = $(SRC:.c=.o)\n"
		"BIN_DIR = build\n"
		"BIN = $(BIN_DIR)/                \n"
		"\n"
		"INCFLAGS  = -Isrc/\n"
		"\n"
		"CCFLAGS += $(INCFLAGS)\n"
		"CCFLAGS += -O0\n"
		"CCFLAGS += -Wall\n"
		"\n"
		"LDFLAGS  = $(INCFLAGS)\n"
		"\n"
		"all: build\n"
		"\n"
		"run: build\n"
		"\t$(BIN) $*\n"
		"\n"
		"build: $(OBJ)\n"
		"\t$(CC) $(CCFLAGS) -ggdb -o $(BIN) $(filter %.o,$^) $(LDFLAGS)\n"
		"\n"
		"clean:\n"
		"\trm $(BIN_DIR)/* $(OBJ)\n"
		"\n"
		"%.o: %.c\n"
		"\t$(CC) -ggdb -o $@ -c $< $(CCFLAGS)\n";


#endif //_NTR_DEFAULTS_H_

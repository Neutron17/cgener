CC = clang

PNAME = c

SRC  = $(shell find src -name "*.c")
OBJ  = $(SRC:.c=.o)
BIN_DIR = build
BIN = $(BIN_DIR)/cgener

INCFLAGS  = -Isrc/

CCFLAGS += $(INCFLAGS)
CCFLAGS += -O0
CCFLAGS += -Wall

LDFLAGS  = $(INCFLAGS)
LDFLAGS += -ldebug

all: build

run: build
	$(BIN) $*

build: $(OBJ)
	$(CC) $(CCFLAGS) -ggdb -o $(BIN) $(filter %.o,$^) $(LDFLAGS)

clean:
	rm $(BIN_DIR)/* $(OBJ)

%.o: %.c
	$(CC) -ggdb -o $@ -c $< $(CCFLAGS)


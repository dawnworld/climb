CC = gcc
CFLAGS = -g -I./include
TOP = ..
OUT = $(TOP)/out
THIRD_PARTY = $(TOP)/third_party
GTEST = $(THIRD_PARTY)/googletest/googletest/

TEST_INCLUDE = ./include/test 

CHECK_API = $(OUT)/check/include
CHECK_LIB = $(OUT)/check/libcheck.a $(OUT)/check/libcompat.a

#OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRC))

CFLAGS += -I$(TEST_INCLUDE) -I$(CHECK_API)

# ------------------- Queue --------------------
OBJS = queue/queue.o 
TEST_OBJS = tests/queue/test_queue.o
BIN = test_queue

TEST_MAIN = tests/test_main.c

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(TEST_MAIN) $(OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) $^ $(CHECK_LIB) -o $(BIN)

all:test

run:test
	./$(BIN)

clean:
	rm -rf $(OBJS) $(TEST_OBJS) $(BIN) *.dSYM

#QUEUE_READY:
#    @mkdir -p $(OUT)/queue

#OUT_QUEUE = $(OUT)/queue
#queue: $(QUEUE_OBJ)

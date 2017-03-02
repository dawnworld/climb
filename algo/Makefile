CC = gcc
CPP = g++
CFLAGS = -g -I./include
TOP = ..
OUT = $(TOP)/out
THIRD_PARTY = $(TOP)/third_party
GTEST_DIR = $(THIRD_PARTY)/googletest/googletest
GTEST_LIB = $(OUT)/googletest/libgtest.a

#OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRC))

CFLAGS += -I$(GTEST_DIR)/include

# ------------------- Queue --------------------
#OBJS = queue/queue.o 
#TEST_SRC = tests/queue/test_queue.cc
#BIN = test_queue

# ------------------- Knapsack -----------------
OBJS = dp/knapsack.o 
TEST_SRC = tests/dp/test_knapsack.cc
BIN = test_ks

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJS) $(TEST_SRC)
	$(CPP) $(CFLAGS) $^ $(GTEST_LIB) -o $(BIN)

all:test

run:test
	./$(BIN)

clean:
	rm -rf $(OBJS) $(TEST_OBJS) $(BIN) *.dSYM


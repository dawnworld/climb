CC = gcc
CPP = g++

TOP = ..
OUT = $(TOP)/out

# ------------------- Google Test --------------
THIRD_PARTY = $(TOP)/third_party
GTEST_DIR = $(THIRD_PARTY)/googletest/googletest
GTEST_LIB = $(OUT)/googletest/libgtest.a

#OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRC))

CFLAGS = -g -I./include
CFLAGS += -I$(GTEST_DIR)/include

BUILDDIR = $(OUT)/obj

# ------------------- GDSL ---------------------
GDSL_SRC_DIR = gdsl
GDSL_SRCS := $(shell find $(GDSL_SRC_DIR) -name '*.c')
GDSL_OBJS := $(addprefix $(BUILDDIR)/,$(GDSL_SRCS:%.c=%.o))

# ------------------- Queue --------------------
QUEUE_OBJS := queue/queue.o 
TEST_SRC = tests/queue/test_queue.cc

# ------------------- Knapsack -----------------
KS_SRCS := dp/knapsack.c
KS_TEST_SRC = tests/dp/test_knapsack.cc
KS_BIN = $(BUILDDIR)/test_ks

# ------------------- Graph --------------------
GRAPH_SRCS := graph/graph.c graph/graph_search.c
GRAPH_TEST_SRC = tests/graph/test_graph.cc
GRAPH_BIN = $(BUILDDIR)/test_graph

SRCS := $(GRAPH_SRCS)
TEST_SRC := $(GRAPH_TEST_SRC)
BIN := $(GRAPH_BIN)
OBJS := $(addprefix $(BUILDDIR)/,$(SRCS:%.c=%.o))
OUT_BIN = test_bin

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(dir $<) -c $< -o $@

gdsl: $(GDSL_OBJS)

test: $(OBJS) $(GDSL_OBJS) $(TEST_SRC)
	$(CPP) $(CFLAGS) $^ $(GTEST_LIB) -o $(BIN)
	$(shell ln -s $(BIN) $(OUT_BIN))

all:test

run:test
	./$(OUT_BIN)

clean:
	rm -rf $(BUILDDIR)/* $(OUT_BIN) *.dSYM


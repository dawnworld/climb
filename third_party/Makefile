CC = g++
GTEST_DIR = googletest/googletest

lib:
	g++ -isystem ${GTEST_DIR}/include -I${GTEST_DIR} \
		-pthread -c ${GTEST_DIR}/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

all:lib

clean:
	@rm -rf gtest-all.o libgtest.a

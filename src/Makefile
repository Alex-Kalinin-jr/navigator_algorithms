CC=g++
CXXFLAGS=-c -std=c++17 -Werror -Wall -Wextra -Wpedantic -g -O0
LDFLAGS=-lgtest -pthread
TESTSRC=tests.cc

LIBSRC=lib/s21_graph.cc lib/s21_graph_algorithms.cc

SRCFILES=main.cc view/console_view.cc controller/controller.cc
SRCOBJ=$(SRCFILES:.cc=.o)
TESTOBJ=$(TESTSRC:.cc=.o)
LIBOBJ=$(LIBSRC:.cc=.o)
LIBSTATIC=$(LIBSRC:.cc=.a)
EXECUTABLE=SimpleNavigator
EXECUTABLE_TEST=SimpleNavigatorTest

.PHONY: all build clean tests build_tests

# all: build

%.o: %.cc
	$(CC) $(CXXFLAGS) $^ -o $@

%.a: $(LIBOBJ)
%.a: %.o
	ar rcs $@ $^

s21_graph.a: lib/s21_graph.a

# s21_graph_algorithms.a: lib/s21_graph_algorithms.a

# cppcheck:
# 	cppcheck --language=c++ --std=c++17 --enable=all $(SRCFILES) $(LIBSRC) main.cc

# build: clean $(SRCOBJ) $(LIBSTATIC)
# 	$(CC) $(SRCOBJ) $(LIBSTATIC) -o $(EXECUTABLE) $(LDFLAGS)

clean:
	@rm -f $(TESTOBJ) $(SRCOBJ) $(LIBOBJ) $(LIBSTATIC) $(EXECUTABLE) $(EXECUTABLE_TEST)

test: clean $(TESTOBJ) $(LIBSTATIC)
	$(CC) $(TESTOBJ) $(LIBSTATIC) -g -o $(EXECUTABLE_TEST) $(LDFLAGS)
	./$(EXECUTABLE_TEST)

style:
	clang-format -i -style=file *.cc *.h lib/*.cc lib/*.h


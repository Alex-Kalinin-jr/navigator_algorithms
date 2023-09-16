CC=g++
CXXFLAGS=-c -std=c++17 -Werror -Wall -Wextra -g
LDFLAGS=-lgtest -pthread
TESTSRC=tests.cc

LIBSRC=lib/s21_graph.cc lib/s21_graph_algorithms.cc

SRCFILES=main.cc view/console_view.cc controller/controller.cc
HDRFILES=controller/controller.h lib/s21_graph.h lib/s21_graph_algorithms.h lib/s21_queue.h lib/s21_stack.h view/choice.h view/console_view.h
SRCOBJ=$(SRCFILES:.cc=.o)
TESTOBJ=$(TESTSRC:.cc=.o)
LIBOBJ=$(LIBSRC:.cc=.o)
LIBSTATIC=$(LIBSRC:.cc=.a)
EXECUTABLE=SimpleNavigator
EXECUTABLE_TEST=SimpleNavigator
REPORTDIR=.
LEAKS_REPORT_FILE=leaks_report.txt

OPEN=xdg-open

.PHONY: all build clean tests build_tests

all: build

%.o: %.cc
	$(CC) $(CXXFLAGS) $^ -o $@

%.a: $(LIBOBJ)
%.a: %.o
	ar rcs $@ $^

s21_graph.a: lib/s21_graph.a

s21_graph_algorithms.a: lib/s21_graph_algorithms.a

build: clean $(SRCOBJ) $(LIBSTATIC)
	$(CC) $(SRCOBJ) $(LIBSTATIC) -o $(EXECUTABLE) $(LDFLAGS)

clean:
	@rm -f $(TESTOBJ) $(SRCOBJ) $(LIBOBJ) $(LIBSTATIC) $(EXECUTABLE) $(EXECUTABLE_TEST)

test: clean $(TESTOBJ) $(LIBSTATIC)
	$(CC) $(TESTOBJ) $(LIBSTATIC) -g -o $(EXECUTABLE_TEST) $(LDFLAGS)
	./$(EXECUTABLE_TEST)
	
dvi:
	cd ./docs/; rm -rf *.aux *.log *.pdf
	cd ./docs/; pdflatex manual.tex
	$(OPEN) ./docs/manual.pdf

style:
	-@clang-format -i -style=file *.cc lib/*.cc lib/*.h
	
cppcheck:
	cppcheck --language=c++ --std=c++17 --enable=all --suppress=unusedFunction \
	--suppress=missingInclude --suppress=unusedStructMember $(SRCFILES) $(HDRFILES) main.cc

leaks:
	valgrind --leak-check=full --verbose --log-file=$(REPORTDIR)/$(LEAKS_REPORT_FILE) ./$(EXECUTABLE_TEST)

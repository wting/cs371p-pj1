# macro definitions
PROJ = Collatz

MAIN = main
EXT = c++
TEST = Test$(PROJ)
IN_PROF = in_profile

# compiler definitions
CC = g++
CFLAGS = -ansi -pedantic -Wall -Werror

# make options
main: $(MAIN).$(EXT)
	$(CC) $(CFLAGS)	-O2 -o $(MAIN).app $(MAIN).$(EXT)
	valgrind $(MAIN).app <$(PROJ).in >$(PROJ).out 2>&1
	cat $(PROJ).out

profile: $(MAIN).$(EXT)
	$(CC) $(CFLAGS) -pg -O2 -DONLINE_JUDGE -DPROFILE -o $(MAIN).app $(MAIN).$(EXT)
	./$(MAIN).app <$(IN_PROF) >/dev/null
	gprof ./$(MAIN).app >gprof.out
	#less gprof.out
	head -n20 gprof.out

test: $(TEST).h 
	$(CC) $(CFLAGS) -lcppunit -ldl -DTEST -o $(MAIN).app $(MAIN).$(EXT)
	valgrind main.app >$(TEST).out 2>&1
	cat $(TEST).out

docs: Doxyfile
	doxygen Doxyfile

doxyfile:
	doxygen -g

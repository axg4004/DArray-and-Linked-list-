SRCLIST = TestList.c LinkedLists.c
SRCSEARCH = TestSearch.c LinkedLists.c
SRCTIME = TestTime.c DynamicArrays.c LinkedLists.c 
DARRAY = DynamicArrays.c
PROG1 = TestList
PROG2 = TestSearch
PROG3 = TestTime
TXT = us-eng-words.txt
OUT = out.txt
MEM = mem.txt
TIME = time.txt
SEARCH = search.txt
MEM = mem.txt
SEARCHWORD = space
CFLG = gcc -Wall -std=c99 -pedantic 
TIMEFLG = gcc -Wall -std=c99 -pedantic -DEN_TIME
VALGRIND = valgrind --tool=memcheck --leak-check=yes 
 

.SILENT:
all: $(PROG1) $(PROG2) $(PROG3)
$(PROG1) : $(SRCLIST)
	@echo "Compiling TestList.c"
	$(CFLG) $(SRCLIST) -o $(PROG1)

$(PROG2) : $(SRCSEARCH)
	@echo "Compiling TestSearch.c"
	$(CFLG) $(SRCSEARCH) -o $(PROG2)

$(PROG3) : $(SRCTIME)
	@echo "Compiling TestTime.c"
	$(TIMEFLG) $(SRCTIME) -o $(PROG3)

.PHONY: test
test: all
	@echo "Testing LinkedLists.c"
	./$(PROG1) $(TXT) > $(OUT)
		
.PHONY: search
search: all
	@echo "Testing LinkedLists.c (TestSearch)"
	./$(PROG2) $(TXT) $(SEARCHWORD) > $(SEARCH)

.PHONY: time
time: all
	@echo "Testing LinkedLists.c (TestTime)"
	./$(PROG3) $(TXT) $(SEARCHWORD) > $(TIME)

.PHONY: mem
mem: $(PROG1)
	@echo "Valgrind memory Report"
	$(VALGRIND) ./$(PROG1) $(TXT) > $(MEM) 2>&1

.PHONY: help
help:
	@echo "All makefile targets: all, test, search, time, mem, clean, help"

.PHONY: clean 
clean:
	@echo "Removing temp file"
	rm -f $(PROG1)
	rm -f $(PROG2)
	rm -f $(PROG3)
	rm -f $(OUT)
	rm -f $(SEARCH)
	rm -f $(TIME)
	rm -f $(MEM)

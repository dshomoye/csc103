objects = fsm.o cpp2html.o cpp2html_ans.o
CC = g++
CFLAGS = -Wall -std=c++0x

cpp2html : fsm.o cpp2html.o
	$(CC) $(CFLAGS) -o cpp2html $^

ans : fsm.o cpp2html_ans.o
	$(CC) $(CFLAGS) -o cpp2html $^

$(objects) : %.o: %.cpp fsm.h
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY : clean
clean :
	rm -f cpp2html $(objects)


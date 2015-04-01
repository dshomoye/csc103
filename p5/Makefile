objects = fsm.o fsm_ans.o main.o
CC = g++
CFLAGS = -Wall

fsm : main.o fsm.o
	$(CC) $(CFLAGS) $^ -o fsm

ans : main.o fsm_ans.o
	$(CC) $(CFLAGS) $^ -o fsm

$(objects) : %.o: %.cpp fsm.h
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY : clean
clean :
	rm -f fsm $(objects)

main = towers
CC = g++
CFLAGS = -Wall -O2

$(main) : $(main).cpp
	$(CC) $(CFLAGS) $< -o $(main)

ans : $(main)_ans.cpp
	$(CC) $(CFLAGS) $< -o $(main)


.PHONY : clean
clean :
	rm -f $(main) output


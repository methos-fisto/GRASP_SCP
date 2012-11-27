OPTS  = -Wall -Wextra -O3 -pipe
FILES = *.cpp
OBJS  = *.o
EXE   = scp

launch : head
	g++ $(OBJS) $(OPTS) -o $(EXE)

head : *.h
	g++ $(FILES) -c $(OPTS)

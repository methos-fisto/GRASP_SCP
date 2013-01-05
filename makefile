#DEBUG = -O3
DEBUG = -g
OPTS  = -Wall -Wextra -pipe -Iinc
FILES = src/*.cpp
OBJS  = *.o
EXE   = scp

launch : head
	g++ $(OBJS) $(OPTS) $(DEBUG) -o $(EXE)

head : inc/*.h src/*.cpp
	g++ $(FILES) -c $(OPTS) $(DEBUG)

clean :
	rm *.o scp

cleaner :
	rm *.o scp *~ */*~

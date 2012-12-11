OPTS  = -Wall -Wextra -O3 -pipe -Iinc -g
FILES = src/*.cpp
OBJS  = *.o
EXE   = scp

launch : head
	g++ $(OBJS) $(OPTS) -o $(EXE)

head : inc/*.h src/*.cpp
	g++ $(FILES) -c $(OPTS)

clean :
	rm *.o scp

cleaner :
	rm *.o scp *~ */*~

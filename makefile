CMazeOut.out: CMaze_main.o SetLimits.o CMaze.o
	g++ -g -o CMazeOut.out CMaze_main.o SetLimits.o CMaze.o

CMaze_main.o: CMaze_main.cpp SetLimits.h CMaze.h
	g++ -g -c Cmaze_main.cpp

SetLimits.o: SetLimits.cpp SetLimits.h
	g++ -g -c SetLimits.cpp

CMaze.o: CMaze.cpp CMaze.h
	g++ -g -c CMaze.cpp

clean:
	rm *.o CMazeOut.out

run : CMazeOut.out
	clear
	CMazeOut.out

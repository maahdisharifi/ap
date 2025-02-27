
main: main.o duplicationId.o invalidArg.o mission.o CountMission.o DistanceMission.o Driver.o TimeMission.o 
	g++ -std=c++11 main.o duplicationId.o invalidArg.o CountMission.o DistanceMission.o Driver.o mission.o TimeMission.o -o main

1.o: main.cpp
	g++ -c -std=c++11 main.cpp

invalidArg.o: invalidArg.cpp
	g++ -c -std=c++11 invalidArg.cpp

duplicationId.o: duplicationId.cpp
	g++ -c -std=c++11 duplicationId.cpp

mission.o: mission.cpp mission.hpp invalidArg.hpp
	g++ -c -std=c++11 mission.cpp

DistanceMission.o: DistanceMission.cpp DistanceMission.hpp mission.hpp invalidArg.hpp
	g++ -c -std=c++11 DistanceMission.cpp

CountMission.o: CountMission.cpp CountMission.hpp mission.hpp invalidArg.hpp
	g++ -c -std=c++11 CountMission.cpp

Driver.o: Driver.cpp Driver.hpp mission.hpp
	g++ -c -std=c++11 Driver.cpp

TimeMission.o: TimeMission.cpp TimeMission.hpp mission.hpp invalidArg.hpp
	g++ -c -std=c++11 TimeMission.cpp

clean:
	rm *.o main

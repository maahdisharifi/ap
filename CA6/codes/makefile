futballFantasy.out: main.o Game.o Admin.o Df.o FFPlayer.o funcs.o Gk.o Md.o St.o RealPlayer.o RealTeam.o 
	g++ -std=c++11 main.o Game.o Admin.o Df.o FFPlayer.o funcs.o Gk.o Md.o St.o RealPlayer.o RealTeam.o -o futballFantasy.out

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

Game.o: Game.cpp 
	g++ -c -std=c++11 Game.cpp

Admin.o: Admin.cpp err.hpp
	g++ -c -std=c++11 Admin.cpp

Df.o: Df.cpp RealPlayer.hpp
	g++ -c -std=c++11 Df.cpp

FFPlayer.o: FFPlayer.cpp Gk.hpp St.hpp Df.hpp Md.hpp
	g++ -c -std=c++11 FFPlayer.cpp

funcs.o: funcs.cpp RealTeam.hpp Game.hpp err.hpp Admin.hpp
	g++ -c -std=c++11 funcs.cpp

Gk.o: Gk.cpp RealPlayer.hpp
	g++ -c -std=c++11 Gk.cpp

Md.o: Md.cpp RealPlayer.hpp
	g++ -c -std=c++11 Md.cpp

St.o: St.cpp RealPlayer.hpp 
	g++ -c -std=c++11 St.cpp

RealPlayer.o: RealPlayer.cpp Gk.hpp St.hpp Df.hpp Md.hpp
	g++ -c -std=c++11 RealPlayer.cpp

RealTeam.o: RealTeam.cpp RealPlayer.hpp funcs.hpp
	g++ -c -std=c++11 RealTeam.cpp

clean:
	rm *.o A7

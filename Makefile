
FLAGS = -O2 -std=c++14

main: sol_all.cpp
	g++ -o main sol_all.cpp $(INCLUDEFILES) $(FLAGS)
	
cl: 
	rm main.exe
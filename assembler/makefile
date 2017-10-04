.PHONY: all assembler.exe clean run

all: assembler.exe

assembler.exe : test_runner.cpp wordcount.cpp wordcount.h
	g++ -g -O0 -o assembler.exe -mavx -mavx2 -std=c++11 test_runner.cpp wordcount.cpp wordcount.h memcpy.cpp memcpy.h
	
run: assembler.exe
	./assembler.exe
	
clean:
	rm -f *.o *.exe *.so
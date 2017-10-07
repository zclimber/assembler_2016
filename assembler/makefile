.PHONY: all assembler.exe clean run assembler.exe_opt run_opt

all: assembler.exe

assembler.exe : test_runner.cpp wordcount.cpp wordcount.h
	g++ -g -O0 -o assembler.exe -mavx -mavx2 -std=c++11 test_runner.cpp wordcount.cpp wordcount.h memcpy.cpp memcpy.h

assembler.exe_opt : test_runner.cpp wordcount.cpp wordcount.h
	g++ -O2 -o assembler.exe -mavx -mavx2 -std=c++11 test_runner.cpp wordcount.cpp wordcount.h memcpy.cpp memcpy.h

	
run: assembler.exe
	./assembler.exe
	
run_opt: assembler.exe_opt
	./assembler.exe
	
clean:
	rm -f *.o *.exe *.so
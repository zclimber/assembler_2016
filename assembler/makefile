.PHONY: all assembler.exe clean run

all: assembler.exe

assembler.exe : test_runner.cpp wordcount.cpp wordcount.h
	g++ -g -O0 -o assembler.exe -mavx -maxv2 test_runner.cpp wordcount.cpp wordcount.h
	
run: assembler.exe
	./assembler.exe
	
clean:
rm -f *.o *.exe *.so
#CXX=clang++
CXX=g++

CXXFLAGS= -g -O3 -std=c++14 

BINARIES=dataProj 

all: ${BINARIES}

tests: ${BINARIES}


dataProj: dataAQ.o demogState.o demogData.o raceDemogData.o psData.o psState.o parse.o main.o
	${CXX} $^ -o $@


clean:
	/bin/rm -f ${BINARIES} *.o 

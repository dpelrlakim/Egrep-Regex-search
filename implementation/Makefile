CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = main-egrep
OBJECTS = parsing.o matching.o search.o egrep.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

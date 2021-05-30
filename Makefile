CXX = clang++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = countdown-solver
OBJECTS = src/countdown-solver.o expression-node.cc
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
CXX = clang++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = countdown-solver
OBJECTS = src/countdown-solver.o src/utils.o src/expression-node.o src/expression.o \
src/int-node.o src/op-node.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
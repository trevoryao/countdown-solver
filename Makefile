CXX = clang++
CXXFLAGS = -std=c++14 -Wall -MMD -g -I /usr/local/boost_1_76_0/include
EXEC = countdown-solver
OBJECTS = src/countdown-solver.o src/utils.o src/expression-node.o src/expression.o \
src/int-node.o src/op-node.o src/config.o src/problem.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lboost_program_options

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

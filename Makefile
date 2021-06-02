CXX = clang++
CXXFLAGS = -std=c++14 -Wall -MMD -I /usr/local/boost_1_76_0/include
EXEC = countdown-solver
LDFLAGS = -lboost_program_options

SOURCES = $(shell find src -type f -name '*.cc')
OBJECTS = ${SOURCES:src/%.cc=bin/%.o}
DEPENDS = ${OBJECTS:.o=.d}

bin/%.o: src/%.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} ${LDFLAGS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

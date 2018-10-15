curr_dir := ${shell pwd}
SRCS := ${shell echo *.cc}
OBJS := $(SRCS:.cc=.o)

CXX := g++ -std=c++11
CXXFLAGS := -O -Wall

hello: ${OBJS}
	${CXX} ${CXXFLAGS} $^ -o $@

*.o: ${SRCS}
	${CXX} ${CXXFLAGS} -c $^

.PHONY: clean
clean:
	${RM} *.o

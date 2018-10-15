curr_dir := ${shell pwd}
SRCS := ${shell echo *.cc}
OBJS := $(SRCS:.cc=.o)

CXX := g++ -std=c++11
CXXFLAGS := -O -Wall

.PHONY: hello
hello: ${OBJS}
	${CXX} ${CXXFLAGS} $^ -o $@

.PHONY: hello_clear
hello: ${OBJS}
	${CXX} ${CXXFLAGS} $^ -o $@
	@${RM} -rv *.o
	@echo "------Done!------"

*.o: ${SRCS}
	${CXX} ${CXXFLAGS} -c $^

.PHONY: clean
clean:
	@${RM} -v *.o

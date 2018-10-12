
curr_dir := ${shell pwd}
files := ${shell echo *.cc}

CXX ?= g++ -std=c++11
CXXFLAGS := -O -Wall

hello: *.o
	${CXX} ${CXXFLAGS} $^ -o $@

*.o: ${files}
	${CXX} ${CXXFLAGS} -c $^

.PHONY: clean
clean:
	${RM} *.o

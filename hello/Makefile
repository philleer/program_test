
LIBS_ROOT := /home/cvnewbee/foldertest/git/program_test/hello/libs

SRCS := ${shell echo *.cc}
SRCS += ${shell echo ${LIBS_ROOT}/*.cc}
OBJS += $(SRCS:.cc=.o)

CXX := g++
CXXFLAGS := -Wall -Wextra -Wundef
CXXFLAGS += -std=c++11
CXXFLAGS += -pthread

hello: ${OBJS}
	${CXX} ${CXXFLAGS} $^ -o $@
	@${RM} -rv *.o ${LIBS_ROOT}/*.o
	@echo "------Done!------"

*.o: ${SRCS} 
	${CXX} ${CXXFLAGS} -c $^

clean:
	@${RM} -v *.o ${LIBS_ROOT}/*.o

.PHONY: clean

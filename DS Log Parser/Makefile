
TEST_LOGFILE = test.dsevents

CXXFLAGS += -Wall -Werror

all : eventParser initClean test.csv

test.csv : eventParser
	./eventParser $(TEST_LOGFILE) messages.txt test.csv

eventParser : Main.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY : clean
clean :
	rm -f eventParser test.csv messages.txt

.PHONY : initClean
initClean :
	rm -f test.csv messages.txt

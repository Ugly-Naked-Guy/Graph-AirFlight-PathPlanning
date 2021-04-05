EXENAME = main
OBJS = pattern.o main.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

.PHONY: all test 
all : $(EXENAME)


$(EXENAME): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp pattern.cpp pattern.h
	$(CXX) $(CXXFLAGS) main.cpp pattern.cpp
	
pattern.o: pattern.cpp pattern.h
	$(CXX) $(CXXFLAGS) pattern.cpp


test : catch/catchmain.cpp tests/test1.cpp tests/test2.cpp pattern.cpp
	$(LD) catch/catchmain.cpp tests/test1.cpp tests/test2.cpp pattern.cpp $(LDFLAGS) -o test

clean:
		-rm -f *.o $(EXENAME) test








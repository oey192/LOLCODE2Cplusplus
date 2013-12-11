CXX = g++
DEBUG = -g
CXXFLAGS = -std=c++0x -Wall -Iinclude -fPIC $(DEBUG)
LDFLAGS = 
ifeq ($(shell uname),Darwin)
	LDFLAGS += -ll
else
	LDFLAGS = -lfl
endif
#tmp/lolcode.yy.cpp tmp/lolcode.tab.cpp 
OBJS = bin/lolcode.tab.o bin/lolcode.yy.o bin/ast.o bin/translator.o

all : dirs bin/lolcode $(OUTPUT)

tmp/lolcode.yy.cpp: src/lolcode4.l
	flex -o $@ $^
	#flex -o src/lolcode.yy.c src/lolcode.l
	
tmp/lolcode.tab.cpp: src/lolcode4.y
	bison -d -o $@ $^
	#bison -d -o tmp/lolcode.tab.cpp src/lolcode.y

bin/lolcode.yy.o: tmp/lolcode.yy.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $^
	#$(CXX) -c -o $@ $<

bin/lolcode.tab.o: tmp/lolcode.tab.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $^
	#$(CXX) -c -o $@ $<

bin/translator.o: src/translator.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $^

bin/ast.o: src/ast.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $^

bin/lolcode: $(OBJS)
	$(CXX) -o $@ $(CXXFLAGS) $(OBJS) $(LDFLAGS)

#lolcode: bin/lolcode.tab.o bin/lolcode.tab.o
#	$(CXX) -o $@ $^

dirs :
	mkdir -p bin
	mkdir -p tmp	
clean:
	rm -rf tmp/* bin/*


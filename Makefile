CXX = g++
DEBUG = -g
CXXFLAGS = -Wall -Iinclude -fPIC $(DEBUG)
LDFLAGS = -lfl

OBJS = tmp/lolcode.yy.cpp tmp/lolcode.tab.cpp bin/lolcode.tab.o bin/lolcode.yy.o

tmp/lolcode.yy.cpp: src/lolcode3.l
	flex -o $@ $^
	#flex -o src/lolcode.yy.c src/lolcode.l

tmp/lolcode.tab.cpp: src/lolcode3.y
	bison -d -o $@ $^
	#bison -d -o tmp/lolcode.tab.cpp src/lolcode.y
	
bin/lolcode.yy.o: tmp/lolcode.yy.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $^
	#$(CXX) -c -o $@ $<

bin/lolcode.tab.o: tmp/lolcode.tab.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $^
	#$(CXX) -c -o $@ $<
	
bin/lolcode : $(OBJS)
	$(CXX) -o $@ $(CXXFLAGS) $(OBJS) $(LDFLAGS)

#lolcode: bin/lolcode.tab.o bin/lolcode.tab.o
#	$(CXX) -o $@ $^

all : dirs bin/lolcode $(OUTPUT)
	
dirs :
	mkdir -p bin
	mkdir -p tmp
	
clean:
	rm -rf tmp/* bin/*


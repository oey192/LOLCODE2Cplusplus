
src/lolcode.yy.c: src/lolcode.l
	flex -o src/lolcode.yy.c src/lolcode.l

src/lolcode.yy.o: src/lolcode.yy.cpp
	$(CXX) -c -o $@ $<

src/lolcode.tab.cpp: src/lolcode.l
	bison -d -o src/lolcode.tab.cpp src/lolcode.y

src/lolcode.tab.o: src/lolcode.tab.cpp
	$(CXX) -c -o $@ $<

lolcode: src/lolcode.tab.o src/lolcode.tab.o
	$(CXX) -o $@ $^


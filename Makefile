all:oh-my-db btree
.PHONY : all

CXX=clang++
FLAG=-g -o2 -std=c++14


%.o : %.c
	$(CXX) -c $(FLAG) $< -o $@

oh-my-db:main.o db.o
	$(CXX) $(FLAG) $^ -o $@
btree:mBtree_test.cpp mBTree.h
	$(CXX) $(FLAG) $< -o $@ 
.PHONY:clean
clean:
	rm *.o oh-my-db

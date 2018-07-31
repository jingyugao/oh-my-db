

all:oh-my-db
.PHONY : all

test:btree_test parser_test
.PHONY : test
CXX=clang++
FLAG=-g -o2 -std=c++14


%.o : %.cpp
	$(CXX) $(FLAG) -c $< -o $@

oh-my-db:main.o db.o
	$(CXX) $(FLAG) $^ -o $@
btree_test:b_tree_test.cpp b_tree.h
	$(CXX) $(FLAG) $< -o $@ 
parser_test:parser_test.cpp json_parser.h
	$(CXX) $(FLAG) $< -o $@ 
.PHONY:clean
clean:
	rm *.o oh-my-db btree_test

all:oh-my-db
.PHONY : all

CXX=clang++
FLAG=-g -std=c++14


%.o : %.c
	$(CXX) -c $(FLAG) $< -o $@

oh-my-db:main.o db.o
	$(CXX) $(FLAG) $^ -o $@

.PHONY:clean
clean:
	rm *.o oh-my-db

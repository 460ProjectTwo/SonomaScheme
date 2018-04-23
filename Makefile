P2.out : Project2.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o
	g++ -g -o P2.out Project2.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o

Project2.o : Project2.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -g -c -std=c++11 Project2.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -g -c -std=c++11 SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h
	g++ -g -c -std=c++11 LexicalAnalyzer.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h firsts.hpp follows.hpp
	g++ -g -c -std=c++11 SyntacticalAnalyzer.cpp

firsts.hpp follows.hpp: tablegen.py
	python3 tablegen.py

clean :
	rm -rf *.o P2.out *.gch

test : P2.out
	mypy tablegen.py
	. ./test-env && kyua test

submit : test do-submit

do-submit : Project2.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp tablegen.py firsts.hpp follows.hpp Makefile README.txt
	rm -rf TeamSP2
	mkdir TeamSP2
	cp $^ TeamSP2
	tar cfvz TeamSP2.tgz TeamSP2
	cp TeamSP2.tgz ~tiawatts/cs460drop

.PHONY: clean test submit do-submit

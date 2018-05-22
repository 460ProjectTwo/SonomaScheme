CXXFLAGS = -g -std=c++14 -Wall -Werror -pedantic

P3.out : Project3.o SetLimits.o LexicalAnalyzer.o CodeGenerator.o SyntacticalAnalyzer.o
	$(CXX) $(CXXFLAGS) -o $@ $^

Project3.o : Project3.cpp SetLimits.h SyntacticalAnalyzer.h
	$(CXX) $(CXXFLAGS) -c $<

SetLimits.o : SetLimits.cpp SetLimits.h
	$(CXX) -g -c $<

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h
	$(CXX) $(CXXFLAGS) -c $<

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h firsts.hpp follows.hpp
	$(CXX) $(CXXFLAGS) -c $<

firsts.hpp follows.hpp: tablegen.py
	python3 tablegen.py

clean :
	rm -rf *.o P3.out *.gch

test : P3.out
	. ./_test-env && kyua test

check-python :
	mypy tablegen.py

submit : test do-submit

do-submit : Project3.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp CodeGenerator.h CodeGenerator.cpp Object.h Object.cpp tablegen.py firsts.hpp follows.hpp Makefile README.txt README.md
	rm -rf Team2P3
	mkdir Team2P3
	cp $^ Team2P3
	tar cvzf Team2P3.tgz Team2P3
	cp Team2P3.tgz ~tiawatts/cs460drop

.PHONY: clean test check-python submit do-submit

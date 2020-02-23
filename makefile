

ctak: ctak.cc
	clang++ -std=c++11 -o ctak ctak.cc


clean:
	rm -f ctak *~

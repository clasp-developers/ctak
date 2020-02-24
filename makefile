CXXFLAGS = $(shell $(LLVM_CONFIG) --cxxflags)


ctak: ctak.cc
	echo $(CXXFLAGS)
	clang++ $(CXXFLAGS) -std=c++11 -o ctak ctak.cc


clean:
	rm -f ctak *~

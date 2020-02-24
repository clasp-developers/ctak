CXXFLAGS = $(shell $(LLVM_CONFIG) --cxxflags)
LDFLAGS = $(shell $(LLVM_CONFIG) --ldflags)
CXXDIR = $(shell $(LLVM_CONFIG) --bindir)
CXX = $(CXXDIR)/clang++


# linux-ctak
linux-ctak: ctak.cc
	echo $(CXXFLAGS)
	$(CXX) -std=c++11 -stdlib=libc++ -nostdinc++ \
		-I/opt/llvm-tot/include/c++/v1 \
		-L/opt/llvm-tot/lib \
		-Wl,-rpath,/opt/llvm-tot/lib \
		-lc++abi -lc++ -lpthread \
		ctak.cc -o linux-ctak

#-I/usr/include/c++/9 -I/usr/include/x86_64-linux-gnu/c++/9 $(CXXFLAGS) -std=c++11 -stdlib=libc++ -o ctak ctak.cc $(LDFLAGS) -L/usr/lib -L/usr/lib/x86_64-linux-gnu -lc++ -lc++abi


clean:
	rm -f ctak *~

CXX = g++
CXXFLAGS = -std=c++11 -static-libgcc -static-libstdc++

.PHONY: all clean

all: fso

fso: fileSystemOrganiser.cpp
	$(CXX) $(CXXFLAGS) -o fso fileSystemOrganiser.cpp

clean:
	rm -f fso


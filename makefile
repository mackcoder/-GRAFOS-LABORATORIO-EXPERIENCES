CXX = g++
CXXFLAGS = -std=c++17

CXXSRC = src/TGrafo.cpp src/maintTeste.cpp
CXXTARGET = programa

all:
	$(CXX) $(CXXFLAGS) $(CXXSRC) -o $(CXXTARGET)

run: all
	./$(CXXTARGET)
	rm $(CXXTARGET)

clean:
	rm $(CXXTARGET)
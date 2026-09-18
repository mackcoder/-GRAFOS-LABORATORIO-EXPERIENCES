CXX = g++

CXXFLAGS = -std=c++17

CXXSRC = src/TGrafo.cpp src/maintTeste.cpp
CXXTARGET = programa.out

CXXSRC_ND = src/TGrafo_ND.cpp src/maintTeste_ND.cpp
CXXTARGET_ND = programa_nd.out

all: _src _src_nd

_src:
	$(CXX) $(CXXFLAGS) $(CXXSRC) -o $(CXXTARGET)

_src_nd:
	$(CXX) $(CXXFLAGS) $(CXXSRC_ND) -o $(CXXTARGET_ND)

run: _src
	./$(CXXTARGET)
	rm $(CXXTARGET)

runnd: _src_nd
	./$(CXXTARGET_ND)
	rm $(CXXTARGET_ND)

clean:
	rm -f *.out

.PHONY: all _src _src_nd run runnd clean
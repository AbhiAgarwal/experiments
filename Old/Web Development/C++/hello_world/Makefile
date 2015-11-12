LIBS=-lcppcms -lbooster


all: hello

hello: hello_world.cpp
	$(CXX) -O2 -Wall -g hello_world.cpp -o hello ${LIBS}

clean:
	rm -fr hello hello.exe cppcms_rundir

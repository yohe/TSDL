
#CC=clang++-mp-3.1
CC=g++
#CC=g++-mp-4.5
BOOST_INCLUDE = /opt/local/include
BOOST_LIB = /opt/local/lib
TSDL_LIB = ..

all: test

test: $(TSDL_LIB)/libtsdl.dylib main.cc 
	cp $(TSDL_LIB)/libtsdl.dylib ./
	$(CC) -g -O0 main.cc -o test -I ../ -I /opt/local/include -I $(BOOST_INCLUDE) -L $(BOOST_LIB) -lboost_system -L $(TSDL_LIB) -ltsdl

clean:
	rm test

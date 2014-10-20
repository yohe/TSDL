
BOOST_INCLUDE = /opt/local/include
BOOST_LIB = /opt/local/lib
TSDL_LIB = .

all: test echo_test server client
	cp ../libtsdl.dylib ./

test: test.cc $(ALL_SOURCE)
	g++ -o test -g -ggdb test.cc $(ALL_SOURCE) -I ../ -I $(BOOST_INCLUDE) -L $(TSDL_LIB) -ltsdl

echo_test: tcp_echo_test.cc $(ALL_SOURCE)
	g++ -o echo_test -g -ggdb tcp_echo_test.cc $(ALL_SOURCE) -I ../ -I $(BOOST_INCLUDE) -L $(BOOST_LIB) -lboost_system-mt -L $(TSDL_LIB) -ltsdl

server: server.cc
	g++ -o server server.cc -I ../ -I $(BOOST_INCLUDE) -L $(BOOST_LIB) -lboost_system-mt -L $(TSDL_LIB) -ltsdl
client: client.cc
	g++ -o client client.cc -I ../ -I $(BOOST_INCLUDE) -L $(BOOST_LIB) -lboost_system-mt -L $(TSDL_LIB) -ltsdl


clean:
	rm test
	rm echo_test
	rm server
	rm client

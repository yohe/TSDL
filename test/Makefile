
BOOST_INCLUDE = /opt/local/include
BOOST_LIB = /opt/local/lib

SOURCE_DIR = ../src
ALL_SOURCE = $(SOURCE_DIR)/init_node.cc \
			 $(SOURCE_DIR)/setup_node.cc \
			 $(SOURCE_DIR)/program_node.cc \
			 $(SOURCE_DIR)/teardown_node.cc \
			 $(SOURCE_DIR)/context.cc \
			 $(SOURCE_DIR)/execute_list_node.cc \
			 $(SOURCE_DIR)/post_condition_node.cc
all: test echo_test server client

test: test.cc $(ALL_SOURCE)
	g++ -o test -g -ggdb test.cc $(ALL_SOURCE) -I ../include -I $(BOOST_INCLUDE)

echo_test: tcp_echo_test.cc $(ALL_SOURCE)
	g++ -o echo_test -g -ggdb tcp_echo_test.cc $(ALL_SOURCE) -I ../include -I $(BOOST_INCLUDE) -L $(BOOST_LIB) -lboost_system

server: server.cc
	g++ -o server server.cc -I ../include -I $(BOOST_INCLUDE) -L $(BOOST_LIB) -lboost_system
client: client.cc
	g++ -o client client.cc -I ../include -I $(BOOST_INCLUDE) -L $(BOOST_LIB) -lboost_system

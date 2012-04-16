
BOOST_INCLUDE = /opt/local/include

SOURCE_DIR = ../src
ALL_SOURCE = $(SOURCE_DIR)/init_node.cc \
			 $(SOURCE_DIR)/setup_node.cc \
			 $(SOURCE_DIR)/program_node.cc \
			 $(SOURCE_DIR)/teardown_node.cc \
			 $(SOURCE_DIR)/context.cc \
			 $(SOURCE_DIR)/execute_list_node.cc \
			 $(SOURCE_DIR)/post_condition_node.cc

test: test.cc
	g++ -o test test.cc $(ALL_SOURCE) -I ../include -I $(BOOST_INCLUDE)

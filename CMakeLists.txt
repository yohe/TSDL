cmake_minimum_required(VERSION 2.6)

PROJECT(tsdl)

IF(UNIX)
    include_directories(/usr/include ./)
    link_directories(/usr/lib)
ENDIF(UNIX)
IF(APPLE)
    include_directories(/opt/local/include /usr/include ./)
    link_directories(/opt/local/lib /usr/lib)
ENDIF(APPLE)

add_library(tsdl SHARED
    tsdl/lang/context.cc 
    tsdl/lang/execute_list_node.cc 
    tsdl/lang/init_node.cc 
    tsdl/lang/post_condition_node.cc 
    tsdl/lang/program_node.cc 
    tsdl/lang/setup_node.cc 
    tsdl/lang/teardown_node.cc
    tsdl/outputter/format_outputter.cc
    tsdl/outputter/junit_outputter.cc
    tsdl/outputter/text_outputter.cc
    tsdl/outputter/xml_outputter.cc
    tsdl/scenario/scenario_case.cc
    tsdl/scenario/scenario_entry.cc
    tsdl/scenario/scenario_group.cc
    tsdl/scenario/scenario_manager.cc
    tsdl/scenario/scenario_result.cc
    tsdl/scenario/scenario_result_collector.cc
    )


#set_target_properties(tsdl LINK_FLAGS -lboost_system)

#set_target_properties(tsdl PROPERTIES COMPILE_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")



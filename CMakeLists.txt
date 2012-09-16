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
    tsdl/scenario/scenario_case.cc
    tsdl/scenario/scenario_entry.cc
    tsdl/scenario/scenario_group.cc
    tsdl/scenario/scenario_manager.cc
    tsdl/scenario/scenario_result.cc
    tsdl/scenario/scenario_result_collector.cc
    tsdl/scenario/scenario_timer.cc
    )


set_target_properties(tsdl PROPERTIES LINK_FLAGS -lboost_date_time)

#set_target_properties(tsdl PROPERTIES COMPILE_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

INSTALL(TARGETS tsdl LIBRARY DESTINATION lib)

INSTALL(FILES
    tsdl/lang.h 
    tsdl/scenario.h 
    tsdl/outputter.h 
    DESTINATION include/tsdl)
INSTALL(FILES
    tsdl/lang/condition_checker.h
    tsdl/lang/context.h 
    tsdl/lang/execute_exception.h
    tsdl/lang/execute_list_node.h 
    tsdl/lang/executor.h
    tsdl/lang/init_node.h 
    tsdl/lang/parse_exception.h
    tsdl/lang/post_condition_node.h 
    tsdl/lang/program_node.h 
    tsdl/lang/setup_node.h 
    tsdl/lang/teardown_node.h
    DESTINATION include/tsdl/lang)

INSTALL(FILES
    tsdl/scenario/scenario_case.h
    tsdl/scenario/scenario_entry.h
    tsdl/scenario/scenario_group.h
    tsdl/scenario/scenario_manager.h
    tsdl/scenario/scenario_result.h
    tsdl/scenario/scenario_result_collector.h
    tsdl/scenario/scenario_timer.h
    DESTINATION include/tsdl/scenario)

INSTALL(FILES
    tsdl/outputter/format_outputter.h
    tsdl/outputter/junit_outputter.h
    tsdl/outputter/text_outputter.h
    DESTINATION include/tsdl/outputter)

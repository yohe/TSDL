SHELL = /bin/sh

### メイク環境
CC = g++
#CC = clang++-mp-3.1
#CC = g++-mp-4.5
LINKER = 
ARCHIVE = ar
ARCHIVE_OPTION = cr
MKDIR = mkdir
MKDIR_OPTION = -p
RM = rm
RM_OPTION = -rf

### ディレクトリ指定変数
TOP = .
SOURCE_DIR = $(TOP)/tsdl
OBJECT_DIR = $(TOP)/obj
LIB_DIR = $(TOP)/lib
LANG_OBJECT_DIR = $(OBJECT_DIR)/lang
SCENARIO_OBJECT_DIR = $(OBJECT_DIR)/scenario
OUTPUTTER_OBJECT_DIR = $(OBJECT_DIR)/outputter

### コンパイルオプション
DEBUG = -g
OPT_FLAG = -O0

INCLUDES = -I ./ -I /opt/local/include
CLIB =  
CFLAGS = -Wall -pedantic $(DEBUG) $(OPT_FLAG) $(INCLUDES)
MAKE_LIB_OP = -shared -o libtsdl.dylib

#### ディレクトリ作成用
MAKE_DIR = $(OBJECT_DIR) \
		   $(LANG_OBJECT_DIR) \
		   $(SCENARIO_OBJECT_DIR) \
		   $(OUTPUTTER_OBJECT_DIR) \
		   $(LIB_DIR)

### ターゲット
LIB_TYPE = shared
TARGET = lib/libtsdl.dylib

LANG_OBJECT = $(LANG_OBJECT_DIR)/context.o \
			  $(LANG_OBJECT_DIR)/program_node.o \
			  $(LANG_OBJECT_DIR)/init_node.o \
			  $(LANG_OBJECT_DIR)/setup_node.o \
			  $(LANG_OBJECT_DIR)/execute_list_node.o \
			  $(LANG_OBJECT_DIR)/teardown_node.o \
			  $(LANG_OBJECT_DIR)/post_condition_node.o 

SCENARIO_OBJECT = $(SCENARIO_OBJECT_DIR)/scenario_entry.o \
			      $(SCENARIO_OBJECT_DIR)/scenario_case.o \
			      $(SCENARIO_OBJECT_DIR)/scenario_group.o \
			      $(SCENARIO_OBJECT_DIR)/scenario_result.o \
			      $(SCENARIO_OBJECT_DIR)/scenario_result_collector.o \
			      $(SCENARIO_OBJECT_DIR)/scenario_manager.o

OUTPUTTER_OBJECT = $(OUTPUTTER_OBJECT_DIR)/format_outputter.o \
			       $(OUTPUTTER_OBJECT_DIR)/text_outputter.o \
			       $(OUTPUTTER_OBJECT_DIR)/xml_outputter.o

ALL_OBJECT = $(LANG_OBJECT) \
			 $(SCENARIO_OBJECT) \
			 $(OUTPUTTER_OBJECT) 

DEPENDS := $(ALL_OBJECT:%.o=%.d)


#################################################################################################
### ディレクトリ作成　後　ターゲット作成
all:
	@echo "###################################################"
	@echo "#       Test Scenario Description Language        #"
	@echo "#                  compile start                  #"
	@echo "###################################################"
	make $(MAKE_DIR)
	make $(TARGET)

-include $(DEPENDS)

### ディレクトリ作成用ルール
$(OBJECT_DIR):
	$(MKDIR) $(MKDIR_OPTION) $@
$(LANG_OBJECT_DIR):
	$(MKDIR) $(MKDIR_OPTION) $@
$(SCENARIO_OBJECT_DIR):
	$(MKDIR) $(MKDIR_OPTION) $@
$(OUTPUTTER_OBJECT_DIR):
	$(MKDIR) $(MKDIR_OPTION) $@
$(LIB_DIR):
	$(MKDIR) $(MKDIR_OPTION) $@

all_compile:
	@echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	@echo "####################################"
	@echo "#               lang               "
	@echo "####################################"
	make lang 
	@echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	@echo "####################################"
	@echo "#             scenario             "
	@echo "####################################"
	make scenario
	@echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	@echo "####################################"
	@echo "#            outputter             "
	@echo "####################################"
	make outputter

lang: $(LANG_OBJECT)
scenario: $(SCENARIO_OBJECT)
outputter: $(OUTPUTTER_OBJECT)

$(TARGET): all_compile Makefile
	@echo ""
	@echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	@echo "|"
	@echo "|                Create Target($(TARGET))"
	@echo "|"
	@echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

ifeq ($(LIB_TYPE),shared)
		$(CC) $(DEBUG) $(CLIB) $(ALL_OBJECT) $(MAKE_LIB_OP)
		mv libtsdl.dylib lib/
else
		$(ARCHIVE) $(ARCHIVE_OPTION) libtsdl.a $(ALL_OBJECT)
		ranlib libtsdl.a
		mv libtsdl.a lib/
endif
	@echo "--------------"
	@echo "  SUCCESS!!!"
	@echo "--------------"


##### 全オブジェクト作成用ルール
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cc
	@echo "-------------------------------------------------------------"
	@echo "-" $< "-"
	$(call make-depend, $<, $@, $(subst .o,.d,$@))
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@


### ターゲット、オブジェクトファイル削除用ルール
.PHONY : clean
clean:
	$(RM) $(RM_OPTION) obj
	$(RM) $(RM_OPTION) bin
	$(RM) $(RM_OPTION) $(TARGET)
# DO NOT DELETE


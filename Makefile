SHELL = /bin/sh

### メイク環境
#CC = g++
CC = g++-mp-4.5
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
LANG_OBJECT_DIR = $(OBJECT_DIR)/lang
SCENARIO_OBJECT_DIR = $(OBJECT_DIR)/scenario
OUTPUTTER_OBJECT_DIR = $(OBJECT_DIR)/outputter

### コンパイルオプション
DEBUG = -g -ggdb
OPT_FLAG = 
#-O2

INCLUDES = -I ./ -I /opt/local/include
CLIB =  
CFLAGS = -Wall -pedantic $(DEBUG) $(OPT_FLAG) $(INCLUDES)

###### define
# $(call make-depend, src-file, object-file, $(subst .o,.d,object-file))
define make-depend
	@$(CC) $(INCLUDES) -MM -MF $3 -MP -MT $2 $1
endef

#### ディレクトリ作成用
MAKE_DIR = $(OBJECT_DIR) \
		   $(LANG_OBJECT_DIR) \
		   $(SCENARIO_OBJECT_DIR) \
		   $(OUTPUTTER_OBJECT_DIR)

### ターゲット
TARGET_BIN = 

SUB_TARGET = lang \
			 scenario \
			 outputter 

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

### ディレクトリ作成　後　ターゲット作成
all: $(MAKE_DIR) 
	make target


### ディレクトリ作成用ルール
$(OBJECT_DIR):
	$(MKDIR) $(MKDIR_OPTION) $@
$(LANG_OBJECT_DIR):
	$(MKDIR) $(MKDIR_OPTION) $@
$(SCENARIO_OBJECT_DIR):
	$(MKDIR) $(MKDIR_OPTION) $@
$(OUTPUTTER_OBJECT_DIR):
	$(MKDIR) $(MKDIR_OPTION) $@


### ターゲット作成用ルール
target: $(SUB_TARGET) Makefile
	@echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	@echo "####################################"
	@echo "#          Create TestBin          #"
	@echo "####################################"
	make test_bin

	@echo "--------------"
	@echo "  SUCCESS!!!"
	@echo "--------------"

test_bin: $(TARGET_BIN)

lang: $(LANG_OBJECT)
scenario: $(SCENARIO_OBJECT)
outputter: $(OUTPUTTER_OBJECT)

##### 全オブジェクト作成用ルール こちらを使用する
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cc
	@echo "-------------------------------------------------------------"
	@echo "-" $< "-"
	$(call make-depend, $<, $@, $(subst .o,.d,$@))
	$(CC) $(CFLAGS) -c $< -o $@


### ターゲット、オブジェクトファイル削除用ルール
.PHONY : clean
clean:
	$(RM) $(RM_OPTION) obj
	$(RM) $(RM_OPTION) bin
# DO NOT DELETE


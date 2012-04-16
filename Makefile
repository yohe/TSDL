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
INCLUDE_DIR = $(TOP)/include
SOURCE_DIR = $(TOP)/src
OBJECT_DIR = $(TOP)/obj

### コンパイルオプション
DEBUG = -g -ggdb
OPT_FLAG = 
#-O2

INCLUDES = -I ./include -I /opt/local/include
CLIB =  
CFLAGS = -Wall -pedantic $(DEBUG) $(OPT_FLAG) $(INCLUDES)

###### define
# $(call make-depend, src-file, object-file, $(subst .o,.d,object-file))
define make-depend
	@$(CC) $(INCLUDES) -MM -MF $3 -MP -MT $2 $1
endef

#### ディレクトリ作成用
MAKE_DIR = $(OBJECT_DIR)

### ターゲット
TARGET_BIN = 

ALL_OBJECT = $(OBJECT_DIR)/context.o \
			 $(OBJECT_DIR)/program_node.o \
			 $(OBJECT_DIR)/init_node.o \
			 $(OBJECT_DIR)/setup_node.o \
			 $(OBJECT_DIR)/execute_list_node.o \
			 $(OBJECT_DIR)/teardown_node.o \
			 $(OBJECT_DIR)/post_condition_node.o 


### ディレクトリ作成　後　ターゲット作成
all: 
	make $(MAKE_DIR)
	make prepare
	make target


### ディレクトリ作成用ルール
$(OBJECT_DIR):
	$(MKDIR) $(MKDIR_OPTION) $(OBJECT_DIR)

prepare:


### ターゲット作成用ルール
target: $(ALL_OBJECT) Makefile
	@echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	@echo "####################################"
	@echo "#          Create TestBin          #"
	@echo "####################################"
	make test_bin

	@echo "--------------"
	@echo "  SUCCESS!!!"
	@echo "--------------"

test_bin: $(TARGET_BIN)


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


+.PHONY: compile
WARN = -Wall -W -Wno-missing-field-initializers

MAKEFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
CURRENT_DIR := $(patsubst %/,%,$(dir $(MAKEFILE_PATH)))


ifneq (,$(findstring test-,$(MAKECMDGOALS)))
	PROP ?= -DMOON_TEST
endif

SRC_DIR = $(CURRENT_DIR)/src
UTIL_PATH = $(SRC_DIR)/util/
CLASSPATH_PATH = $(SRC_DIR)/classpath/
CLASSFILE_PATH = $(SRC_DIR)/classfile/

TEST_PATH = $(CURRENT_DIR)/tests/
TEST_OUT_PATH = /tmp/
TEST_RESOURCE_PATH = $(TEST_PATH)resources/

DEP_DIR = $(CURRENT_DIR)/dep
DEP_ADLIST_PATH = $(DEP_DIR)/adlist/
DEP_SDS_PATH = $(DEP_DIR)/sds/

FINAL_LIBS = -lzip

OS_UNAME :=  $(shell sh -c 'uname -s 2>/dev/null || echo not')

# Compile flags for linux / osx
ifeq ($(OS_UNAME),Linux)
	SHOBJ_CFLAGS ?=  -Wall -W -O3 -fno-common -g -ggdb -std = c99
	SHOBJ_LDFLAGS ?=  -shared
else
	SHOBJ_CFLAGS ?=   -dynamic -fno-common -std = gnu99 -g -ggdb
	SHOBJ_LDFLAGS ?=  -bundle -undefined dynamic_lookup
endif

CC = gcc -g
LD = ld
TCC = $(CC)
JCC = javac -d $(TEST_OUT_PATH)

ALL_HEADER = $(UTIL_PATH)%.h $(CLASSFILE_PATH)%.h

$(UTIL_PATH)%.o : $(UTIL_PATH)%.c
	$(CC) $(PROP) -c $< -o $@
$(CLASSPATH_PATH)%.o : $(CLASSPATH_PATH)%.c
	$(CC) -I$(SRC_DIR) $(PROP) -c $< -o $@
$(CLASSFILE_PATH)%.o : $(CLASSFILE_PATH)%.c
	$(CC) -I$(SRC_DIR) $(PROP) -c $< -o $@

$(TEST_PATH)%.o :  $(TEST_PATH)%.c
	$(CC) -I$(SRC_DIR) $(PROP) -c $< -o $@		

test-util: $(UTIL_PATH)util.o $(TEST_PATH)test_util.o
	$(TCC) $(FINAL_LIBS) -o $(TEST_OUT_PATH)$@ $^
	$(TEST_OUT_PATH)$@

test-classpath: $(UTIL_PATH)util.o $(CLASSPATH_PATH)classpath.o $(TEST_PATH)test_classpath.o 
	$(TCC) -I$(SRC_DIR) $(FINAL_LIBS) -o $(TEST_OUT_PATH)$@ $^
	$(JCC) $(TEST_RESOURCE_PATH)MySimple.java
	$(TEST_OUT_PATH)$@

test-classfile: $(UTIL_PATH)util.o $(CLASSPATH_PATH)classpath.o $(CLASSFILE_PATH)classfile.o $(TEST_PATH)test_classfile.o
	$(TCC) -I$(SRC_DIR) $(FINAL_LIBS) -o $(TEST_OUT_PATH)$@ $^
	$(JCC) $(TEST_RESOURCE_PATH)MySimple.java
	$(TEST_OUT_PATH)$@

test-encoding: $(TEST_PATH)test_encoding.o
	$(TCC) -o $(TEST_OUT_PATH)$@ $^
	$(TEST_OUT_PATH)$@

clean:
	rm -rf $(UTIL_PATH)*.o
	rm -rf $(CLASSFILE_PATH)*.o
	rm -rf $(CLASSPATH_PATH)*.o
	rm -rf $(TEST_PATH)*.o

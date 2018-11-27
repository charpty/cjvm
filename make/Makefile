+.PHONY: compile
WARN=-Wall -W -Wno-missing-field-initializers

CC = gcc
LD = ld

MAKEFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
CURRENT_DIR := $(patsubst %/,%,$(dir $(MAKEFILE_PATH)))

SRC_DIR=$(CURRENT_DIR)/../src
UTIL_PATH=$(SRC_DIR)/util/
CLASSFILE_PATH=$(SRC_DIR)/classfile/

TEST_PATH=$(CURRENT_DIR)/../tests/

DEP_DIR=$(CURRENT_DIR)/../dep
DEP_ADLIST_PATH=$(DEP_DIR)/adlist/
DEP_SDS_PATH=$(DEP_DIR)/sds/

FINAL_LIBS=-lzip

OS_UNAME := $(shell sh -c 'uname -s 2>/dev/null || echo not')

# Compile flags for linux / osx
ifeq ($(OS_UNAME),Linux)
	SHOBJ_CFLAGS ?= -Wall -W -O3 -fno-common -g -ggdb -std=c99
	SHOBJ_LDFLAGS ?= -shared
else
	SHOBJ_CFLAGS ?=  -dynamic -fno-common -std=gnu99 -g -ggdb
	SHOBJ_LDFLAGS ?= -bundle -undefined dynamic_lookup
endif

.SUFFIXES: .c .so .xo .o

.c.xo:
	$(CC) -c $< -o $@

TEST_UTIL_FILE=$(UTIL_PATH)util.h $(UTIL_PATH)util.c $(TEST_PATH)test_util.c
test-util: 
	$(CC) $(TEST_UTIL_FILE) $(FINAL_LIBS)

test-classfile:
	@echo "test-classfile"


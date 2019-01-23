cmake_minimum_required(VERSION 3.9)
project(cjvm)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(cjvm
        dep/adlist/adlist.c
        dep/adlist/adlist.h
        dep/sds/sds.c
        dep/sds/sds.h
        dep/sds/sdsalloc.h
        src/classfile/attribute_info.h
        src/classfile/classfile.c
        src/classfile/classfile.h
        src/classfile/classpath.c
        src/classfile/classpath.h
        src/classfile/classreader.h
        src/classfile/constant_pool.h
        src/classfile/member_info.h
        src/interpreter/bytecode_interpreter.c
        src/interpreter/bytecode_interpreter.h
        src/interpreter/bytecode_stream.h
        src/interpreter/ins_compare.h
        src/interpreter/ins_constant.h
        src/interpreter/ins_control.h
        src/interpreter/ins_convert.h
        src/interpreter/ins_extend.h
        src/interpreter/ins_load.h
        src/interpreter/ins_math.h
        src/interpreter/ins_opcode.h
        src/interpreter/ins_reference.h
        src/interpreter/ins_reserved.h
        src/interpreter/ins_stack.h
        src/interpreter/ins_store.h
        src/native/jni.h
        src/runtime/class.c
        src/runtime/class.h
        src/runtime/classloader.c
        src/runtime/classloader.h
        src/runtime/frame.c
        src/runtime/frame.h
        src/runtime/oop.h
        src/runtime/rcp.h
        src/runtime/thread.c
        src/runtime/thread.h
        src/util/util.c
        src/util/util.h
        src/jvm.c
        tests/test_classfile.c
        tests/test_classpath.c
        tests/test_encoding.c
        tests/test_simple.c
        tests/test_util.c)

target_link_libraries(cjvm -lzip)

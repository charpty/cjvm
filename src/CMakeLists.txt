cmake_minimum_required(VERSION 3.9)
project(cjvmSrc)

set(CMAKE_CXX_STANDARD 11)

add_executable(cjvm
        classfile/attribute_info.h
        classfile/classfile.c
        classfile/classfile.h
        classfile/classpath.c
        classfile/classpath.h
        classfile/classreader.h
        classfile/constant_pool.h
        classfile/member_info.h
        interpreter/bytecode_interpreter.c
        interpreter/bytecode_interpreter.h
        interpreter/bytecode_stream.h
        interpreter/ins_compare.h
        interpreter/ins_constant.h
        interpreter/ins_control.h
        interpreter/ins_convert.h
        interpreter/ins_extend.h
        interpreter/ins_load.h
        interpreter/ins_math.h
        interpreter/ins_opcode.h
        interpreter/ins_reference.h
        interpreter/ins_reserved.h
        interpreter/ins_stack.h
        interpreter/ins_store.h
        native/jni.h
        runtime/class.c
        runtime/class.h
        runtime/classloader.c
        runtime/classloader.h
        runtime/frame.c
        runtime/frame.h
        runtime/oop.h
        runtime/rcp.h
        runtime/thread.c
        runtime/thread.h
        util/util.c
        util/util.h
        jvm.c)

target_link_libraries(cjvm -lzip)
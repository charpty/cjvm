#ifndef MOON_JNI_H
#define MOON_JNI_H

#include <stdlib.h>
#include <stdarg.h>

// https://docs.oracle.com/javase/9/docs/specs/jni/index.html

// TODO JNI相关的结构体
typedef const struct JNINativeInterface *JNIEnv;
#define JNI_INT int
#define JNI_SHORT short
#define JNI_LONG long
#define JNI_BOOLEAN int8_t
#define JNI_BYTE char
#define JNI_CHAR char
#define JNI_SIZE uint32_t
#define JNI_OBJECT void *
#define JNI_CLASS void *
#define JNI_METHOD_ID void *
#define JNI_FIELD_ID void *
#define JNI_THROWABLE void *
#define JNI_VALUE void *
#define JNI_STRING void *
#define JNI_FLOAT void *
#define JNI_DOUBLE double
#define JNI_ARRAY void **
#define JNI_OBJECT_ARRAY void **
#define JNI_CLASS_ARRAY void **
#define JNI_CHAR_ARRAY void **
#define JNI_BYTE_ARRAY void **
#define JNI_INT_ARRAY void **
#define JNI_SHORT_ARRAY void **
#define JNI_BOOLEAN_ARRAY void **
#define JNI_LONG_ARRAY void **
#define JNI_FLOAT_ARRAY void **
#define JNI_DOUBLE_ARRAY void **
#define JNI_WEAK void *

typedef struct JNINativeMethod
{

} JNINativeMethod;

typedef struct JavaVM
{

} JavaVM;

/*
 * 为何JNI规范中的示例保持一直，函数指针使用大写风格
 */
typedef const struct JNINativeInterface
{
    // Note that the first three entries are reserved for future compatibility with COM
    // 前3个NULL是为了兼容COM标准
    void *reserved0;
    void *reserved1;
    void *reserved2;
    // we reserve a number of additional NULL entries near the beginning of the function table
    // 保留一个NULL是为了后续扩展，添加函数时能够加到正确位置而不是尾部
    void *reserved3;
    // Returns the version of the native method interface.
    // 获取当前JNI接口的版本号
    JNI_INT(*GetVersion)
    (JNIEnv *env);
    // Loads a class from a buffer of raw class data.
    // 从指定位置加载class文件
    JNI_CLASS(*DefineClass)
    (JNIEnv *env, char *name, JNI_OBJECT loader, JNI_BYTE *buf,
     JNI_SIZE len);

    // In JDK release 1.1, this function loads a locally-defined class.
    // 在JDK1.1版本中，这个函数用来加载一个本地定义的class
    // Since Java 2 SDK release 1.2, the Java security model allows non-system classes to load and call native methods.
    // 在JDK1.2以后，Java安全模型允许第三方类加载器，所以它也可以用来使用第三方类加载器加载class
    JNI_CLASS(*FindClass)
    (JNIEnv *env, char *name);
    // to call Java methods or access Java fields if they know the name and type of the methods or fields.
    // Java程序可以通过方法名或者属性名访问方法或属性（反射）
    // 方法 -> 方法ID
    JNI_METHOD_ID(*FromReflectedMethod)
    (JNIEnv *env, JNI_OBJECT method);
    // 属性 -> 属性ID
    JNI_FIELD_ID(*FromReflectedField)
    (JNIEnv *env, JNI_OBJECT field);
    // 方法ID -> 方法
    JNI_OBJECT(*ToReflectedMethod)
    (JNIEnv *env, JNI_CLASS cls, JNI_METHOD_ID methodID, JNI_BOOLEAN isStatic);
    // 获取类的父类，接口或Object的父类为NULL
    JNI_CLASS(*GetSuperclass)
    (JNIEnv *env, JNI_CLASS sub);
    // Determines whether an object of clazz1 can be safely cast to clazz2
    // 判断class1能否转换为class2，java.lang.Class.isAssignableFrom的实现
    JNI_BOOLEAN(*IsAssignableFrom)
    (JNIEnv *env, JNI_CLASS sub, JNI_CLASS sup);
    // 属性ID -> 属性
    JNI_OBJECT(*ToReflectedField)
    (JNIEnv *env, JNI_CLASS cls, JNI_FIELD_ID fieldID, JNI_BOOLEAN isStatic);
    // Causes a java.lang.Throwable object to be thrown
    // 抛出异常
    JNI_INT(*Throw)
    (JNIEnv *env, JNI_THROWABLE obj);
    // Constructs an exception object from the specified class with the message specified by message and causes that exception to be thrown.
    // 根据原异常构建一个新的异常
    JNI_INT(*ThrowNew)
    (JNIEnv *env, JNI_CLASS clazz, char *msg);
    // Determines if an exception is being thrown
    // 判断是否抛出异常了
    JNI_THROWABLE(*ExceptionOccurred)
    (JNIEnv *env);
    // Prints an exception and a backtrace of the stack to a system error-reporting channel
    // 打印异常堆栈
    void (*ExceptionDescribe)(JNIEnv *env);
    // Clears any exception that is currently being thrown
    // 清理当前异常
    void (*ExceptionClear)(JNIEnv *env);
    // Raises a fatal error and does not expect the VM to recover.
    // 抛出一个不可恢复的异常
    void (*FatalError)(JNIEnv *env, char *msg);

    // Creates a new local reference frame, in which at least a given number of local references can be created
    // 创建一个局部引用的栈帧
    JNI_INT(*PushLocalFrame)
    (JNIEnv *env, JNI_INT capacity);
    // Pops off the current local reference frame
    // 弹出局部栈帧
    JNI_OBJECT(*PopLocalFrame)
    (JNIEnv *env, JNI_OBJECT result);

    // Creates a new global reference to the object referred to by the obj argument
    // 为对象场景一个全局引用，主要用于在执行本地方法后防止被回收
    JNI_OBJECT(*NewGlobalRef)
    (JNIEnv *env, JNI_OBJECT lobj);
    // Deletes the global reference pointed to by globalRef.
    // 删除一个全局引用
    void (*DeleteGlobalRef)(JNIEnv *env, JNI_OBJECT gref);
    // Deletes the local reference pointed to by localRef.
    // 删除本地引用
    void (*DeleteLocalRef)(JNIEnv *env, JNI_OBJECT obj);
    // 判断两个引用指向的Java对象是否相同
    // Tests whether two references refer to the same Java object
    JNI_BOOLEAN(*IsSameObject)
    (JNIEnv *env, JNI_OBJECT obj1, JNI_OBJECT obj2);
    // Creates a new local reference that refers to the same object as ref
    // 为当前引用创建一个本地方法栈引用
    JNI_OBJECT(*NewLocalRef)
    (JNIEnv *env, JNI_OBJECT ref);
    // Ensures that at least a given number of local references can be created in the current thread
    // 检查当前线程是否支持创建这么多个本地引用
    JNI_INT(*EnsureLocalCapacity)
    (JNIEnv *env, JNI_INT capacity);

    // Allocates a new Java object without invoking any of the constructors for the object.
    // 为一个Java对象分配内存（没调用它的构造器）
    JNI_OBJECT(*AllocObject)
    (JNIEnv *env, JNI_CLASS clazz);
    // Constructs a new Java object
    // 创建一个Java对象并调用其构造函数，3种传递构造参数的方式
    JNI_OBJECT(*NewObject)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    JNI_OBJECT(*NewObjectV)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, va_list args);
    JNI_OBJECT(*NewObjectA)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, JNI_VALUE *args);

    // Returns the class of an object
    // 获取一个对象的class
    JNI_CLASS(*GetObjectClass)
    (JNIEnv *env, JNI_OBJECT obj);
    // Tests whether an object is an instance of a class.
    // 判断一个对象是不是某个class实例
    JNI_BOOLEAN(*IsInstanceOf)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz);

    // Returns the method ID for an instance (nonstatic) method of a class or interface
    // 获取成员函数ID，可以是继承来的方法
    JNI_METHOD_ID(*GetMethodID)
    (JNIEnv *env, JNI_CLASS clazz, char *name, char *sig);

    // Call<type>Method Routines, Call<type>MethodA Routines, Call<type>MethodV Routines
    JNI_OBJECT(*CallObjectMethod)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, ...);
    JNI_OBJECT(*CallObjectMethodV)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, va_list args);
    JNI_OBJECT(*CallObjectMethodA)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, JNI_VALUE *args);

    JNI_BOOLEAN(*CallBooleanMethod)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, ...);
    JNI_BOOLEAN(*CallBooleanMethodV)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, va_list args);
    JNI_BOOLEAN(*CallBooleanMethodA)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, JNI_VALUE *args);

    JNI_BYTE(*CallByteMethod)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, ...);
    JNI_BYTE(*CallByteMethodV)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, va_list args);
    JNI_BYTE(*CallByteMethodA)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, JNI_VALUE *args);

    JNI_CHAR(*CallCharMethod)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, ...);
    JNI_CHAR(*CallCharMethodV)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, va_list args);
    JNI_CHAR(*CallCharMethodA)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, JNI_VALUE *args);

    JNI_SHORT(*CallShortMethod)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, ...);
    JNI_SHORT(*CallShortMethodV)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, va_list args);
    JNI_SHORT(*CallShortMethodA)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, JNI_VALUE *args);

    JNI_INT(*CallIntMethod)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, ...);
    JNI_INT(*CallIntMethodV)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, va_list args);
    JNI_INT(*CallIntMethodA)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, JNI_VALUE *args);

    JNI_LONG(*CallLongMethod)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, ...);
    JNI_LONG(*CallLongMethodV)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, va_list args);
    JNI_LONG(*CallLongMethodA)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, JNI_VALUE *args);

    JNI_FLOAT(*CallFloatMethod)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, ...);
    JNI_FLOAT(*CallFloatMethodV)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, va_list args);
    JNI_FLOAT(*CallFloatMethodA)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, JNI_VALUE *args);

    JNI_DOUBLE(*CallDoubleMethod)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, ...);
    JNI_DOUBLE(*CallDoubleMethodV)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, va_list args);
    JNI_DOUBLE(*CallDoubleMethodA)
    (JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, JNI_VALUE *args);

    void (*CallVoidMethod)(JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, ...);
    void (*CallVoidMethodV)(JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, va_list args);
    void (*CallVoidMethodA)(JNIEnv *env, JNI_OBJECT obj, JNI_METHOD_ID methodID, JNI_VALUE *args);

    JNI_OBJECT(*CallNonvirtualObjectMethod)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    JNI_OBJECT(*CallNonvirtualObjectMethodV)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
     va_list args);
    JNI_OBJECT(*CallNonvirtualObjectMethodA)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
     JNI_VALUE *args);

    JNI_BOOLEAN(*CallNonvirtualBooleanMethod)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    JNI_BOOLEAN(*CallNonvirtualBooleanMethodV)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
     va_list args);
    JNI_BOOLEAN(*CallNonvirtualBooleanMethodA)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
     JNI_VALUE *args);

    JNI_BYTE(*CallNonvirtualByteMethod)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    JNI_BYTE(*CallNonvirtualByteMethodV)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
     va_list args);
    JNI_BYTE(*CallNonvirtualByteMethodA)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
     JNI_VALUE *args);

    JNI_CHAR(*CallNonvirtualCharMethod)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    JNI_CHAR(*CallNonvirtualCharMethodV)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
     va_list args);
    JNI_CHAR(*CallNonvirtualCharMethodA)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
     JNI_VALUE *args);

    JNI_SHORT(*CallNonvirtualShortMethod)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    JNI_SHORT(*CallNonvirtualShortMethodV)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
     va_list args);
    JNI_SHORT(*CallNonvirtualShortMethodA)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
     JNI_VALUE *args);

    JNI_INT(*CallNonvirtualIntMethod)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    JNI_INT(*CallNonvirtualIntMethodV)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
     va_list args);
    JNI_INT(*CallNonvirtualIntMethodA)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
     JNI_VALUE *args);

    JNI_LONG(*CallNonvirtualLongMethod)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    JNI_LONG(*CallNonvirtualLongMethodV)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
     va_list args);
    JNI_LONG(*CallNonvirtualLongMethodA)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
     JNI_VALUE *args);

    JNI_FLOAT(*CallNonvirtualFloatMethod)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    JNI_FLOAT(*CallNonvirtualFloatMethodV)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
     va_list args);
    JNI_FLOAT(*CallNonvirtualFloatMethodA)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
     JNI_VALUE *args);

    JNI_DOUBLE(*CallNonvirtualDoubleMethod)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    JNI_DOUBLE(*CallNonvirtualDoubleMethodV)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
     va_list args);
    JNI_DOUBLE(*CallNonvirtualDoubleMethodA)
    (JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
     JNI_VALUE *args);

    void (*CallNonvirtualVoidMethod)(JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    void (*CallNonvirtualVoidMethodV)(JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
                                      va_list args);
    void (*CallNonvirtualVoidMethodA)(JNIEnv *env, JNI_OBJECT obj, JNI_CLASS clazz, JNI_METHOD_ID methodID,
                                      JNI_VALUE *args);

    // Returns the field ID for an instance (nonstatic) field of a class.
    // 获取成员属性ID
    JNI_FIELD_ID(*GetFieldID)
    (JNIEnv *env, JNI_CLASS clazz, char *name, char *sig);

    // Get<type>Field Routines
    JNI_OBJECT(*GetObjectField)
    (JNIEnv *env, JNI_OBJECT obj, JNI_FIELD_ID fieldID);
    JNI_BOOLEAN(*GetBooleanField)
    (JNIEnv *env, JNI_OBJECT obj, JNI_FIELD_ID fieldID);
    JNI_BYTE(*GetByteField)
    (JNIEnv *env, JNI_OBJECT obj, JNI_FIELD_ID fieldID);
    JNI_CHAR(*GetCharField)
    (JNIEnv *env, JNI_OBJECT obj, JNI_FIELD_ID fieldID);
    JNI_SHORT(*GetShortField)
    (JNIEnv *env, JNI_OBJECT obj, JNI_FIELD_ID fieldID);
    JNI_INT(*GetIntField)
    (JNIEnv *env, JNI_OBJECT obj, JNI_FIELD_ID fieldID);
    JNI_LONG(*GetLongField)
    (JNIEnv *env, JNI_OBJECT obj, JNI_FIELD_ID fieldID);
    JNI_FLOAT(*GetFloatField)
    (JNIEnv *env, JNI_OBJECT obj, JNI_FIELD_ID fieldID);
    JNI_DOUBLE(*GetDoubleField)
    (JNIEnv *env, JNI_OBJECT obj, JNI_FIELD_ID fieldID);

    void (*SetObjectField)(JNIEnv *env, JNI_OBJECT obj, JNI_FIELD_ID fieldID, JNI_OBJECT val);
    void (*SetBooleanField)(JNIEnv *env, JNI_OBJECT obj, JNI_FIELD_ID fieldID, JNI_BOOLEAN val);
    void (*SetByteField)(JNIEnv *env, JNI_OBJECT obj, JNI_FIELD_ID fieldID, JNI_BYTE val);
    void (*SetCharField)(JNIEnv *env, JNI_OBJECT obj, JNI_FIELD_ID fieldID, JNI_CHAR val);
    void (*SetShortField)(JNIEnv *env, JNI_OBJECT obj, JNI_FIELD_ID fieldID, JNI_SHORT val);
    void (*SetIntField)(JNIEnv *env, JNI_OBJECT obj, JNI_FIELD_ID fieldID, JNI_INT val);
    void (*SetLongField)(JNIEnv *env, JNI_OBJECT obj, JNI_FIELD_ID fieldID, JNI_LONG val);
    void (*SetFloatField)(JNIEnv *env, JNI_OBJECT obj, JNI_FIELD_ID fieldID, JNI_FLOAT val);
    void (*SetDoubleField)(JNIEnv *env, JNI_OBJECT obj, JNI_FIELD_ID fieldID, JNI_DOUBLE val);

    JNI_METHOD_ID(*GetStaticMethodID)
    (JNIEnv *env, JNI_CLASS clazz, char *name, char *sig);

    JNI_OBJECT(*CallStaticObjectMethod)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    JNI_OBJECT(*CallStaticObjectMethodV)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, va_list args);
    JNI_OBJECT(*CallStaticObjectMethodA)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, JNI_VALUE *args);

    JNI_BOOLEAN(*CallStaticBooleanMethod)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    JNI_BOOLEAN(*CallStaticBooleanMethodV)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, va_list args);
    JNI_BOOLEAN(*CallStaticBooleanMethodA)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, JNI_VALUE *args);

    JNI_BYTE(*CallStaticByteMethod)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    JNI_BYTE(*CallStaticByteMethodV)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, va_list args);
    JNI_BYTE(*CallStaticByteMethodA)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, JNI_VALUE *args);

    JNI_CHAR(*CallStaticCharMethod)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    JNI_CHAR(*CallStaticCharMethodV)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, va_list args);
    JNI_CHAR(*CallStaticCharMethodA)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, JNI_VALUE *args);

    JNI_SHORT(*CallStaticShortMethod)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    JNI_SHORT(*CallStaticShortMethodV)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, va_list args);
    JNI_SHORT(*CallStaticShortMethodA)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, JNI_VALUE *args);

    JNI_INT(*CallStaticIntMethod)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    JNI_INT(*CallStaticIntMethodV)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, va_list args);
    JNI_INT(*CallStaticIntMethodA)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, JNI_VALUE *args);

    JNI_LONG(*CallStaticLongMethod)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    JNI_LONG(*CallStaticLongMethodV)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, va_list args);
    JNI_LONG(*CallStaticLongMethodA)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, JNI_VALUE *args);

    JNI_FLOAT(*CallStaticFloatMethod)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    JNI_FLOAT(*CallStaticFloatMethodV)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, va_list args);
    JNI_FLOAT(*CallStaticFloatMethodA)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, JNI_VALUE *args);

    JNI_DOUBLE(*CallStaticDoubleMethod)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, ...);
    JNI_DOUBLE(*CallStaticDoubleMethodV)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, va_list args);
    JNI_DOUBLE(*CallStaticDoubleMethodA)
    (JNIEnv *env, JNI_CLASS clazz, JNI_METHOD_ID methodID, JNI_VALUE *args);

    void (*CallStaticVoidMethod)(JNIEnv *env, JNI_CLASS cls, JNI_METHOD_ID methodID, ...);
    void (*CallStaticVoidMethodV)(JNIEnv *env, JNI_CLASS cls, JNI_METHOD_ID methodID, va_list args);
    void (*CallStaticVoidMethodA)(JNIEnv *env, JNI_CLASS cls, JNI_METHOD_ID methodID, JNI_VALUE *args);

    JNI_FIELD_ID(*GetStaticFieldID)
    (JNIEnv *env, JNI_CLASS clazz, char *name, char *sig);
    JNI_OBJECT(*GetStaticObjectField)
    (JNIEnv *env, JNI_CLASS clazz, JNI_FIELD_ID fieldID);
    JNI_BOOLEAN(*GetStaticBooleanField)
    (JNIEnv *env, JNI_CLASS clazz, JNI_FIELD_ID fieldID);
    JNI_BYTE(*GetStaticByteField)
    (JNIEnv *env, JNI_CLASS clazz, JNI_FIELD_ID fieldID);
    JNI_CHAR(*GetStaticCharField)
    (JNIEnv *env, JNI_CLASS clazz, JNI_FIELD_ID fieldID);
    JNI_SHORT(*GetStaticShortField)
    (JNIEnv *env, JNI_CLASS clazz, JNI_FIELD_ID fieldID);
    JNI_INT(*GetStaticIntField)
    (JNIEnv *env, JNI_CLASS clazz, JNI_FIELD_ID fieldID);
    JNI_LONG(*GetStaticLongField)
    (JNIEnv *env, JNI_CLASS clazz, JNI_FIELD_ID fieldID);
    JNI_FLOAT(*GetStaticFloatField)
    (JNIEnv *env, JNI_CLASS clazz, JNI_FIELD_ID fieldID);
    JNI_DOUBLE(*GetStaticDoubleField)
    (JNIEnv *env, JNI_CLASS clazz, JNI_FIELD_ID fieldID);

    void (*SetStaticObjectField)(JNIEnv *env, JNI_CLASS clazz, JNI_FIELD_ID fieldID, JNI_OBJECT value);
    void (*SetStaticBooleanField)(JNIEnv *env, JNI_CLASS clazz, JNI_FIELD_ID fieldID, JNI_BOOLEAN value);
    void (*SetStaticByteField)(JNIEnv *env, JNI_CLASS clazz, JNI_FIELD_ID fieldID, JNI_BYTE value);
    void (*SetStaticCharField)(JNIEnv *env, JNI_CLASS clazz, JNI_FIELD_ID fieldID, JNI_CHAR value);
    void (*SetStaticShortField)(JNIEnv *env, JNI_CLASS clazz, JNI_FIELD_ID fieldID, JNI_SHORT value);
    void (*SetStaticIntField)(JNIEnv *env, JNI_CLASS clazz, JNI_FIELD_ID fieldID, JNI_INT value);
    void (*SetStaticLongField)(JNIEnv *env, JNI_CLASS clazz, JNI_FIELD_ID fieldID, JNI_LONG value);
    void (*SetStaticFloatField)(JNIEnv *env, JNI_CLASS clazz, JNI_FIELD_ID fieldID, JNI_FLOAT value);
    void (*SetStaticDoubleField)(JNIEnv *env, JNI_CLASS clazz, JNI_FIELD_ID fieldID, JNI_DOUBLE value);

    JNI_STRING(*NewString)
    (JNIEnv *env, JNI_CHAR *unicode, JNI_SIZE len);
    JNI_SIZE(*GetStringLength)
    (JNIEnv *env, JNI_STRING str);
    JNI_CHAR *(*GetStringChars)(JNIEnv *env, JNI_STRING str, JNI_BOOLEAN *isCopy);
    void (*ReleaseStringChars)(JNIEnv *env, JNI_STRING str, JNI_CHAR *chars);

    JNI_STRING(*NewStringUTF)
    (JNIEnv *env, char *utf);
    JNI_SIZE(*GetStringUTFLength)
    (JNIEnv *env, JNI_STRING str);
    char *(*GetStringUTFChars)(JNIEnv *env, JNI_STRING str, JNI_BOOLEAN *isCopy);
    void (*ReleaseStringUTFChars)(JNIEnv *env, JNI_STRING str, char *chars);

    JNI_SIZE(*GetArrayLength)
    (JNIEnv *env, JNI_ARRAY array);

    JNI_OBJECT_ARRAY(*NewObjectArray)
    (JNIEnv *env, JNI_SIZE len, JNI_CLASS clazz, JNI_OBJECT init);
    JNI_OBJECT(*GetObjectArrayElement)
    (JNIEnv *env, JNI_OBJECT_ARRAY array, JNI_SIZE index);
    void (*SetObjectArrayElement)(JNIEnv *env, JNI_OBJECT_ARRAY array, JNI_SIZE index, JNI_OBJECT val);

    JNI_BOOLEAN_ARRAY(*NewBooleanArray)
    (JNIEnv *env, JNI_SIZE len);
    JNI_BYTE_ARRAY(*NewByteArray)
    (JNIEnv *env, JNI_SIZE len);
    JNI_CHAR_ARRAY(*NewCharArray)
    (JNIEnv *env, JNI_SIZE len);
    JNI_SHORT_ARRAY(*NewShortArray)
    (JNIEnv *env, JNI_SIZE len);
    JNI_INT_ARRAY(*NewIntArray)
    (JNIEnv *env, JNI_SIZE len);
    JNI_LONG_ARRAY(*NewLongArray)
    (JNIEnv *env, JNI_SIZE len);
    JNI_FLOAT_ARRAY(*NewFloatArray)
    (JNIEnv *env, JNI_SIZE len);
    JNI_DOUBLE_ARRAY(*NewDoubleArray)
    (JNIEnv *env, JNI_SIZE len);

    JNI_BOOLEAN *(*GetBooleanArrayElements)(JNIEnv *env, JNI_BOOLEAN_ARRAY array, JNI_BOOLEAN *isCopy);
    JNI_BYTE *(*GetByteArrayElements)(JNIEnv *env, JNI_BYTE_ARRAY array, JNI_BOOLEAN *isCopy);
    JNI_CHAR *(*GetCharArrayElements)(JNIEnv *env, JNI_CHAR_ARRAY array, JNI_BOOLEAN *isCopy);
    JNI_SHORT *(*GetShortArrayElements)(JNIEnv *env, JNI_SHORT_ARRAY array, JNI_BOOLEAN *isCopy);
    JNI_INT *(*GetIntArrayElements)(JNIEnv *env, JNI_INT_ARRAY array, JNI_BOOLEAN *isCopy);
    JNI_LONG *(*GetLongArrayElements)(JNIEnv *env, JNI_LONG_ARRAY array, JNI_BOOLEAN *isCopy);
    JNI_FLOAT *(*GetFloatArrayElements)(JNIEnv *env, JNI_FLOAT_ARRAY array, JNI_BOOLEAN *isCopy);
    JNI_DOUBLE *(*GetDoubleArrayElements)(JNIEnv *env, JNI_DOUBLE_ARRAY array, JNI_BOOLEAN *isCopy);

    void (*ReleaseBooleanArrayElements)(JNIEnv *env, JNI_BOOLEAN_ARRAY array, JNI_BOOLEAN *elems, JNI_INT mode);
    void (*ReleaseByteArrayElements)(JNIEnv *env, JNI_BYTE_ARRAY array, JNI_BYTE *elems, JNI_INT mode);
    void (*ReleaseCharArrayElements)(JNIEnv *env, JNI_CHAR_ARRAY array, JNI_CHAR *elems, JNI_INT mode);
    void (*ReleaseShortArrayElements)(JNIEnv *env, JNI_SHORT_ARRAY array, JNI_SHORT *elems, JNI_INT mode);
    void (*ReleaseIntArrayElements)(JNIEnv *env, JNI_INT_ARRAY array, JNI_INT *elems, JNI_INT mode);
    void (*ReleaseLongArrayElements)(JNIEnv *env, JNI_LONG_ARRAY array, JNI_LONG *elems, JNI_INT mode);
    void (*ReleaseFloatArrayElements)(JNIEnv *env, JNI_FLOAT_ARRAY array, JNI_FLOAT *elems, JNI_INT mode);
    void (*ReleaseDoubleArrayElements)(JNIEnv *env, JNI_DOUBLE_ARRAY array, JNI_DOUBLE *elems, JNI_INT mode);

    void (*GetBooleanArrayRegion)(JNIEnv *env, JNI_BOOLEAN_ARRAY array, JNI_SIZE start, JNI_SIZE l, JNI_BOOLEAN *buf);
    void (*GetByteArrayRegion)(JNIEnv *env, JNI_BYTE_ARRAY array, JNI_SIZE start, JNI_SIZE len, JNI_BYTE *buf);
    void (*GetCharArrayRegion)(JNIEnv *env, JNI_CHAR_ARRAY array, JNI_SIZE start, JNI_SIZE len, JNI_CHAR *buf);
    void (*GetShortArrayRegion)(JNIEnv *env, JNI_SHORT_ARRAY array, JNI_SIZE start, JNI_SIZE len, JNI_SHORT *buf);
    void (*GetIntArrayRegion)(JNIEnv *env, JNI_INT_ARRAY array, JNI_SIZE start, JNI_SIZE len, JNI_INT *buf);
    void (*GetLongArrayRegion)(JNIEnv *env, JNI_LONG_ARRAY array, JNI_SIZE start, JNI_SIZE len, JNI_LONG *buf);
    void (*GetFloatArrayRegion)(JNIEnv *env, JNI_FLOAT_ARRAY array, JNI_SIZE start, JNI_SIZE len, JNI_FLOAT *buf);
    void (*GetDoubleArrayRegion)(JNIEnv *env, JNI_DOUBLE_ARRAY array, JNI_SIZE start, JNI_SIZE len, JNI_DOUBLE *buf);

    void (*SetBooleanArrayRegion)(JNIEnv *env, JNI_BOOLEAN_ARRAY array, JNI_SIZE start, JNI_SIZE l, JNI_BOOLEAN *buf);
    void (*SetByteArrayRegion)(JNIEnv *env, JNI_BYTE_ARRAY array, JNI_SIZE start, JNI_SIZE len, JNI_BYTE *buf);
    void (*SetCharArrayRegion)(JNIEnv *env, JNI_CHAR_ARRAY array, JNI_SIZE start, JNI_SIZE len, JNI_CHAR *buf);
    void (*SetShortArrayRegion)(JNIEnv *env, JNI_SHORT_ARRAY array, JNI_SIZE start, JNI_SIZE len, JNI_SHORT *buf);
    void (*SetIntArrayRegion)(JNIEnv *env, JNI_INT_ARRAY array, JNI_SIZE start, JNI_SIZE len, JNI_INT *buf);
    void (*SetLongArrayRegion)(JNIEnv *env, JNI_LONG_ARRAY array, JNI_SIZE start, JNI_SIZE len, JNI_LONG *buf);
    void (*SetFloatArrayRegion)(JNIEnv *env, JNI_FLOAT_ARRAY array, JNI_SIZE start, JNI_SIZE len, JNI_FLOAT *buf);
    void (*SetDoubleArrayRegion)(JNIEnv *env, JNI_DOUBLE_ARRAY array, JNI_SIZE start, JNI_SIZE len, JNI_DOUBLE *buf);

    // Java调用本地函数初始化的灵魂函数
    JNI_INT(*RegisterNatives)
    (JNIEnv *env, JNI_CLASS clazz, JNINativeMethod *methods,
     JNI_INT nMethods);
    // 去除native方法
    JNI_INT(*UnregisterNatives)
    (JNIEnv *env, JNI_CLASS clazz);

    JNI_INT(*MonitorEnter)
    (JNIEnv *env, JNI_OBJECT obj);
    JNI_INT(*MonitorExit)
    (JNIEnv *env, JNI_OBJECT obj);

    JNI_INT(*GetJavaVM)
    (JNIEnv *env, JavaVM **vm);

    void (*GetStringRegion)(JNIEnv *env, JNI_STRING str, JNI_SIZE start, JNI_SIZE len, JNI_CHAR *buf);
    void (*GetStringUTFRegion)(JNIEnv *env, JNI_STRING str, JNI_SIZE start, JNI_SIZE len, char *buf);

    void *(*GetPrimitiveArrayCritical)(JNIEnv *env, JNI_ARRAY array, JNI_BOOLEAN *isCopy);
    void (*ReleasePrimitiveArrayCritical)(JNIEnv *env, JNI_ARRAY array, void *carray, JNI_INT mode);

    JNI_CHAR *(*GetStringCritical)(JNIEnv *env, JNI_STRING string, JNI_BOOLEAN *isCopy);
    void (*ReleaseStringCritical)(JNIEnv *env, JNI_STRING string, JNI_CHAR *cstring);

    JNI_WEAK(*NewWeakGlobalRef)
    (JNIEnv *env, JNI_OBJECT obj);
    void (*DeleteWeakGlobalRef)(JNIEnv *env, JNI_WEAK ref);

    JNI_BOOLEAN(*ExceptionCheck)
    (JNIEnv *env);

    JNI_OBJECT(*NewDirectByteBuffer)
    (JNIEnv *env, void *address, JNI_LONG capacity);
    void *(*GetDirectBufferAddress)(JNIEnv *env, JNI_OBJECT buf);
    JNI_LONG(*GetDirectBufferCapacity)
    (JNIEnv *env, JNI_OBJECT buf);

    uint8_t (*GetObjectRefType)(JNIEnv *env, JNI_OBJECT obj);

    JNI_OBJECT(*GetModule)
    (JNIEnv *env, JNI_CLASS clazz);
} JNINativeInterface;

#endif
# cjvm

实现路径，其中较为简单和底层的解析、内存管理、运行时数据区、JIT等使用C实现，涉及异常的使用C++实现

```java
class文件解析 -> 运行时数据区 -> 指令集 -> JNI -> 内存管理与GC -> 启动与JDK加载 -> JIT -> 实战运行网站
```

由于JDK涵盖了海量的方法，部分方法对运行网站没有作用，所以可能需要抽出一个简洁的rt.jar
在系统交互方面，希望只跟NIO打交道即可

## 目前运行流程
* 使用classpath把指定路径上的所有jar包或class读进内存
* 使用classfile将其解析为符号
* 启用自动内存分配机制，开启GC线程
* 构建运行时数据区
* 解析并推入首个栈桢
* 指令依次执行
* 方法执行情况抽样
* 将热方法编译为本地代码
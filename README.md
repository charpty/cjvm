# cjvm


## 解析器版本思路

* 使用classpath把指定路径上的所有jar包或class都读进内存
* 使用classfile将其解析为符号
* 构建运行时数据区
* 解析并推入首个栈桢
* 指令依次执行


## CS|IP实现思路
* 有点绕还没开明白
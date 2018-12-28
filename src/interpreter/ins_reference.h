#ifndef MOON_INS_REFERENCE_H
#define MOON_INS_REFERENCE_H

// 引用
// GETSTATIC 178       0xb2 获取指定类的静态域，并将其值压入栈顶
// PUTSTATIC 179       0xb3 为指定的类的静态域赋值
// GETFIELD 180        0xb4 获取指定类的实例域，并将其值压入栈顶
// PUTFIELD 181        0xb5 为指定的类的实例域赋值
// INVOKEVIRTUAL 182   0xb6 调用实例方法
// INVOKESPECIAL 183   0xb7 调用超类构造方法，实例初始化方法，私有方法
// INVOKESTATIC 184    0xb8 调用静态方法
// INVOKEINTERFACE 185 0xb9 调用接口方法
// INVOKEDYNAMIC 186   0xba 调用动态链接方法
// NEW 187             0xbb 创建一个对象，并将其引用值压入栈顶
// NEWARRAY 188        0xbc 创建一个指定原始类型（如int、float、char„„）的数组，并将其引用值压入栈顶
// ANEWARRAY 189       0xbd 创建一个引用型（如类，接口，数组）的数组，并将其引用值压入栈顶
// ARRAYLENGTH 190     0xbe 获得数组的长度值并压入栈顶
// ATHROW 191          0xbf 将栈顶的异常抛出
// CHECKCAST 192       0xc0 检验类型转换，检验未通过将抛出ClassCastException
// INSTANCEOF 193      0xc1 检验对象是否是指定的类的实例，如果是将1压入栈顶，否则将0压入栈顶
// MONITORENTER 194    0xc2 获得对象的monitor，用于同步方法或同步块
// MONITOREXIT 195     0xc3 释放对象的monitor，用于同步方法或同步块

#endif

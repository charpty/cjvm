#ifndef MOON_INS_CONTROL_H
#define MOON_INS_CONTROL_H

// 控制
// GOTO 167         0xa7 无条件跳转
// JSR 168          0xa8 跳转至指定16位offset位置，并将jsr下一条指令地址压入栈顶
// RET 169          0xa9 返回至局部变量指定的index的指令位置（一般与jsr，jsr_w联合使用）
// TABLESWITCH 170  0xaa 用于switch条件跳转，case值连续（可变长度指令）
// LOOKUPSWITCH 171 0xab 用于switch条件跳转，case值不连续（可变长度指令）
// IRETURN 172      0xac 从当前方法返回int
// LRETURN 173      0xad 从当前方法返回long
// FRETURN 174      0xae 从当前方法返回float
// DRETURN 175      0xaf 从当前方法返回double
// ARETURN 176      0xb0 从当前方法返回对象引用
// RETURN 177       0xb1 从当前方法返回void

#endif

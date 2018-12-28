#ifndef MOON_INS_EXTEND_H
#define MOON_INS_EXTEND_H

// 扩展
// WIDE 196           0xc4 扩展访问局部变量表的索引宽度
// MULTIANEWARRAY 197 0xc5 创建指定类型和指定维度的多维数组（执行该指令时，操作栈中必须包含各维度的长度值），并将其引用值压入栈顶
// IFNULL 198         0xc6 为null时跳转
// IFNONNULL 199      0xc7 不为null时跳转
// GOTO_W 200         0xc8 无条件跳转（宽索引）
// JSR_W 201          0xc9 跳转至指定32位地址偏移量位置，并将jsr_w下一条指令地址压入栈顶 保留指令

#endif

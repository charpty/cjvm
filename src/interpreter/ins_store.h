#ifndef MOON_INS_STORE_H
#define MOON_INS_STORE_H

// 存储
// ISTORE 54   0x36 将栈顶int型数值存入指定局部变量
// LSTORE 55   0x37 将栈顶long型数值存入指定局部变量
// FSTORE 56   0x38 将栈顶float型数值存入指定局部变量
// DSTORE 57   0x39 将栈顶double型数值存入指定局部变量
// ASTORE 58   0x3a 将栈顶引用型数值存入指定局部变量
// ISTORE_0 59 0x3b 将栈顶int型数值存入第一个局部变量
// ISTORE_1 60 0x3c 将栈顶int型数值存入第二个局部变量
// ISTORE_2 61 0x3d 将栈顶int型数值存入第三个局部变量
// ISTORE_3 62 0x3e 将栈顶int型数值存入第四个局部变量
// LSTORE_0 63 0x3f 将栈顶long型数值存入第一个局部变量
// LSTORE_1 64 0x40 将栈顶long型数值存入第二个局部变量
// LSTORE_2 65 0x41 将栈顶long型数值存入第三个局部变量
// LSTORE_3 66 0x42 将栈顶long型数值存入第四个局部变量
// FSTORE_0 67 0x43 将栈顶float型数值存入第一个局部变量
// FSTORE_1 68 0x44 将栈顶float型数值存入第二个局部变量
// FSTORE_2 69 0x45 将栈顶float型数值存入第三个局部变量
// FSTORE_3 70 0x46 将栈顶float型数值存入第四个局部变量
// DSTORE_0 71 0x47 将栈顶double型数值存入第一个局部变量
// DSTORE_1 72 0x48 将栈顶double型数值存入第二个局部变量
// DSTORE_2 73 0x49 将栈顶double型数值存入第三个局部变量
// DSTORE_3 74 0x4a 将栈顶double型数值存入第四个局部变量
// ASTORE_0 75 0x4b 将栈顶引用型数值存入第一个局部变量
// ASTORE_1 76 0x4c 将栈顶引用型数值存入第二个局部变量
// ASTORE_2 77 0x4d 将栈顶引用型数值存入第三个局部变量
// ASTORE_3 78 0x4e 将栈顶引用型数值存入第四个局部变量
// IASTORE 79  0x4f 将栈顶int型数值存入指定数组的指定索引位置
// LASTORE 80  0x50 将栈顶long型数值存入指定数组的指定索引位置
// FASTORE 81  0x51 将栈顶float型数值存入指定数组的指定索引位置
// DASTORE 82  0x52 将栈顶double型数值存入指定数组的指定索引位置
// AASTORE 83  0x53 将栈顶引用型数值存入指定数组的指定索引位置
// BASTORE 84  0x54 将栈顶boolean或byte型数值存入指定数组的指定索引位置
// CASTORE 85  0x55 将栈顶char型数值存入指定数组的指定索引位置
// SASTORE 86  0x56 将栈顶short型数值存入指定数组的指定索引位置
#endif

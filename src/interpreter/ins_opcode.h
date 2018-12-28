#ifndef MOON_INS_OPCODE_H
#define MOON_INS_OPCODE_H

// https://docs.oracle.com/javase/specs/jvms/se11/html/jvms-7.html
// 按照虚拟机规范将指令分为11种类型
// 常量
#define OP_NOP 0         // 0x00 什么都不做
#define OP_ACONST_NULL 1 // 0x01 将null推送至栈顶
#define OP_ICONST_M1 2   // 0x02 将int型-1推送至栈顶
#define OP_ICONST_0 3    // 0x03 将int型0推送至栈顶
#define OP_ICONST_1 4    // 0x04 将int型1推送至栈顶
#define OP_ICONST_2 5    // 0x05 将int型2推送至栈顶
#define OP_ICONST_3 6    // 0x06 将int型3推送至栈顶
#define OP_ICONST_4 7    // 0x07 将int型4推送至栈顶
#define OP_ICONST_5 8    // 0x08 将int型5推送至栈顶
#define OP_LCONST_0 9    // 0x09 将long型0推送至栈顶
#define OP_LCONST_1 10   // 0x0a 将long型1推送至栈顶
#define OP_FCONST_0 11   // 0x0b 将float型0推送至栈顶
#define OP_FCONST_1 12   // 0x0c 将float型1推送至栈顶
#define OP_FCONST_2 13   // 0x0d 将float型2推送至栈顶
#define OP_DCONST_0 14   // 0x0e 将double型0推送至栈顶
#define OP_DCONST_1 15   // 0x0f 将double型1推送至栈顶
#define OP_BIPUSH 16     // 0x10 将单字节的常量值（-128~127）推送至栈顶
#define OP_SIPUSH 17     // 0x11 将一个短整型常量值（-32768~32767）推送至栈顶
#define OP_LDC 18        // 0x12 将int，float或String型常量值从常量池中推送至栈顶
#define OP_LDC_W 19      // 0x13 将int，float或String型常量值从常量池中推送至栈顶（宽索引）
#define OP_LDC2_W 20     // 0x14 将long或double型常量值从常量池中推送至栈顶（宽索引）
// 加载
#define OP_ILOAD 21   // 0x15 将指定的int型局部变量推送至栈顶
#define OP_LLOAD 22   // 0x16 将指定的long型局部变量推送至栈顶
#define OP_FLOAD 23   // 0x17 将指定的float型局部变量推送至栈顶
#define OP_DLOAD 24   // 0x18 将指定的double型局部变量推送至栈顶
#define OP_ALOAD 25   // 0x19 将指定的引用类型局部变量推送至栈顶
#define OP_ILOAD_0 26 // 0x1a 将第一个int型局部变量推送至栈顶
#define OP_ILOAD_1 27 // 0x1b 将第二个int型局部变量推送至栈顶
#define OP_ILOAD_2 28 // 0x1c 将第三个int型局部变量推送至栈顶
#define OP_ILOAD_3 29 // 0x1d 将第四个int型局部变量推送至栈顶
#define OP_LLOAD_0 30 // 0x1e 将第一个long型局部变量推送至栈顶
#define OP_LLOAD_1 31 // 0x1f 将第二个long型局部变量推送至栈顶
#define OP_LLOAD_2 32 // 0x20 将第三个long型局部变量推送至栈顶
#define OP_LLOAD_3 33 // 0x21 将第四个long型局部变量推送至栈顶
#define OP_FLOAD_0 34 // 0x22 将第一个float型局部变量推送至栈顶
#define OP_FLOAD_1 35 // 0x23 将第二个float型局部变量推送至栈顶
#define OP_FLOAD_2 36 // 0x24 将第三个float型局部变量推送至栈顶
#define OP_FLOAD_3 37 // 0x25 将第四个float型局部变量推送至栈顶
#define OP_DLOAD_0 38 // 0x26 将第一个double型局部变量推送至栈顶
#define OP_DLOAD_1 39 // 0x27 将第二个double型局部变量推送至栈顶
#define OP_DLOAD_2 40 // 0x28 将第三个double型局部变量推送至栈顶
#define OP_DLOAD_3 41 // 0x29 将第四个double型局部变量推送至栈顶
#define OP_ALOAD_0 42 // 0x2a 将第一个引用类型局部变量推送至栈顶
#define OP_ALOAD_1 43 // 0x2b 将第二个引用类型局部变量推送至栈顶
#define OP_ALOAD_2 44 // 0x2c 将第三个引用类型局部变量推送至栈顶
#define OP_ALOAD_3 45 // 0x2d 将第四个引用类型局部变量推送至栈顶
#define OP_IALOAD 46  // 0x2e 将int型数组指定索引的值推送至栈顶
#define OP_LALOAD 47  // 0x2f 将long型数组指定索引的值推送至栈顶
#define OP_FALOAD 48  // 0x30 将float型数组指定索引的值推送至栈顶
#define OP_DALOAD 49  // 0x31 将double型数组指定索引的值推送至栈顶
#define OP_AALOAD 50  // 0x32 将引用型数组指定索引的值推送至栈顶
#define OP_BALOAD 51  // 0x33 将boolean或byte型数组指定索引的值推送至栈顶
#define OP_CALOAD 52  // 0x34 将char型数组指定索引的值推送至栈顶
#define OP_SALOAD 53  // 0x35 将short型数组指定索引的值推送至栈顶
// 存储
#define OP_ISTORE 54   // 0x36 将栈顶int型数值存入指定局部变量
#define OP_LSTORE 55   // 0x37 将栈顶long型数值存入指定局部变量
#define OP_FSTORE 56   // 0x38 将栈顶float型数值存入指定局部变量
#define OP_DSTORE 57   // 0x39 将栈顶double型数值存入指定局部变量
#define OP_ASTORE 58   // 0x3a 将栈顶引用型数值存入指定局部变量
#define OP_ISTORE_0 59 // 0x3b 将栈顶int型数值存入第一个局部变量
#define OP_ISTORE_1 60 // 0x3c 将栈顶int型数值存入第二个局部变量
#define OP_ISTORE_2 61 // 0x3d 将栈顶int型数值存入第三个局部变量
#define OP_ISTORE_3 62 // 0x3e 将栈顶int型数值存入第四个局部变量
#define OP_LSTORE_0 63 // 0x3f 将栈顶long型数值存入第一个局部变量
#define OP_LSTORE_1 64 // 0x40 将栈顶long型数值存入第二个局部变量
#define OP_LSTORE_2 65 // 0x41 将栈顶long型数值存入第三个局部变量
#define OP_LSTORE_3 66 // 0x42 将栈顶long型数值存入第四个局部变量
#define OP_FSTORE_0 67 // 0x43 将栈顶float型数值存入第一个局部变量
#define OP_FSTORE_1 68 // 0x44 将栈顶float型数值存入第二个局部变量
#define OP_FSTORE_2 69 // 0x45 将栈顶float型数值存入第三个局部变量
#define OP_FSTORE_3 70 // 0x46 将栈顶float型数值存入第四个局部变量
#define OP_DSTORE_0 71 // 0x47 将栈顶double型数值存入第一个局部变量
#define OP_DSTORE_1 72 // 0x48 将栈顶double型数值存入第二个局部变量
#define OP_DSTORE_2 73 // 0x49 将栈顶double型数值存入第三个局部变量
#define OP_DSTORE_3 74 // 0x4a 将栈顶double型数值存入第四个局部变量
#define OP_ASTORE_0 75 // 0x4b 将栈顶引用型数值存入第一个局部变量
#define OP_ASTORE_1 76 // 0x4c 将栈顶引用型数值存入第二个局部变量
#define OP_ASTORE_2 77 // 0x4d 将栈顶引用型数值存入第三个局部变量
#define OP_ASTORE_3 78 // 0x4e 将栈顶引用型数值存入第四个局部变量
#define OP_IASTORE 79  // 0x4f 将栈顶int型数值存入指定数组的指定索引位置
#define OP_LASTORE 80  // 0x50 将栈顶long型数值存入指定数组的指定索引位置
#define OP_FASTORE 81  // 0x51 将栈顶float型数值存入指定数组的指定索引位置
#define OP_DASTORE 82  // 0x52 将栈顶double型数值存入指定数组的指定索引位置
#define OP_AASTORE 83  // 0x53 将栈顶引用型数值存入指定数组的指定索引位置
#define OP_BASTORE 84  // 0x54 将栈顶boolean或byte型数值存入指定数组的指定索引位置
#define OP_CASTORE 85  // 0x55 将栈顶char型数值存入指定数组的指定索引位置
#define OP_SASTORE 86  // 0x56 将栈顶short型数值存入指定数组的指定索引位置
// 栈
#define OP_POP 87     // 0x57 将栈顶数值弹出（数值不能是long或double类型的）
#define OP_POP2 88    // 0x58 将栈顶的一个（long或double类型的）或两个数值弹出（其它）
#define OP_DUP 89     // 0x59 复制栈顶数值并将复制值压入栈顶
#define OP_DUP_X1 90  // 0x5a 复制栈顶数值并将两个复制值压入栈顶
#define OP_DUP_X2 91  // 0x5b 复制栈顶数值并将三个（或两个）复制值压入栈顶
#define OP_DUP2 92    // 0x5c 复制栈顶一个（long或double类型的)或两个（其它）数值并将复制值压入栈顶
#define OP_DUP2_X1 93 // 0x5d dup_x1指令的双倍版本
#define OP_DUP2_X2 94 // 0x5e dup_x2指令的双倍版本
#define OP_SWAP 95    // 0x5f 将栈最顶端的两个数值互换（数值不能是long或double类型的）
// 数学
#define OP_IADD 96   // 0x60 将栈顶两int型数值相加并将结果压入栈顶
#define OP_LADD 97   // 0x61 将栈顶两long型数值相加并将结果压入栈顶
#define OP_FADD 98   // 0x62 将栈顶两float型数值相加并将结果压入栈顶
#define OP_DADD 99   // 0x63 将栈顶两double型数值相加并将结果压入栈顶
#define OP_ISUB 100  // 0x64 将栈顶两int型数值相减并将结果压入栈顶
#define OP_LSUB 101  // 0x65 将栈顶两long型数值相减并将结果压入栈顶
#define OP_FSUB 102  // 0x66 将栈顶两float型数值相减并将结果压入栈顶
#define OP_DSUB 103  // 0x67 将栈顶两double型数值相减并将结果压入栈顶
#define OP_IMUL 104  // 0x68 将栈顶两int型数值相乘并将结果压入栈顶
#define OP_LMUL 105  // 0x69 将栈顶两long型数值相乘并将结果压入栈顶
#define OP_FMUL 106  // 0x6a 将栈顶两float型数值相乘并将结果压入栈顶
#define OP_DMUL 107  // 0x6b 将栈顶两double型数值相乘并将结果压入栈顶
#define OP_IDIV 108  // 0x6c 将栈顶两int型数值相除并将结果压入栈顶
#define OP_LDIV 109  // 0x6d 将栈顶两long型数值相除并将结果压入栈顶
#define OP_FDIV 110  // 0x6e 将栈顶两float型数值相除并将结果压入栈顶
#define OP_DDIV 111  // 0x6f 将栈顶两double型数值相除并将结果压入栈顶
#define OP_IREM 112  // 0x70 将栈顶两int型数值作取模运算并将结果压入栈顶
#define OP_LREM 113  // 0x71 将栈顶两long型数值作取模运算并将结果压入栈顶
#define OP_FREM 114  // 0x72 将栈顶两float型数值作取模运算并将结果压入栈顶
#define OP_DREM 115  // 0x73 将栈顶两double型数值作取模运算并将结果压入栈顶
#define OP_INEG 116  // 0x74 将栈顶int型数值取负并将结果压入栈顶
#define OP_LNEG 117  // 0x75 将栈顶long型数值取负并将结果压入栈顶
#define OP_FNEG 118  // 0x76 将栈顶float型数值取负并将结果压入栈顶
#define OP_DNEG 119  // 0x77 将栈顶double型数值取负并将结果压入栈顶
#define OP_ISHL 120  // 0x78 将int型数值左移位指定位数并将结果压入栈顶
#define OP_LSHL 121  // 0x79 将long型数值左移位指定位数并将结果压入栈顶
#define OP_ISHR 122  // 0x7a 将int型数值右（有符号）移位指定位数并将结果压入栈顶
#define OP_LSHR 123  // 0x7b 将long型数值右（有符号）移位指定位数并将结果压入栈顶
#define OP_IUSHR 124 // 0x7c 将int型数值右（无符号）移位指定位数并将结果压入栈顶
#define OP_LUSHR 125 // 0x7d 将long型数值右（无符号）移位指定位数并将结果压入栈顶
#define OP_IAND 126  // 0x7e 将栈顶两int型数值作“按位与”并将结果压入栈顶
#define OP_LAND 127  // 0x7f 将栈顶两long型数值作“按位与”并将结果压入栈顶
#define OP_IOR 128   // 0x80 将栈顶两int型数值作“按位或”并将结果压入栈顶
#define OP_LOR 129   // 0x81 将栈顶两long型数值作“按位或”并将结果压入栈顶
#define OP_IXOR 130  // 0x82 将栈顶两int型数值作“按位异或”并将结果压入栈顶
#define OP_LXOR 131  // 0x83 将栈顶两long型数值作“按位异或”并将结果压入栈顶
#define OP_IINC 132  // 0x84 将指定int型变量增加指定值
// 转换
#define OP_I2L 133 // 0x85 将栈顶int型数值强制转换成long型数值并将结果压入栈顶
#define OP_I2F 134 // 0x86 将栈顶int型数值强制转换成float型数值并将结果压入栈顶
#define OP_I2D 135 // 0x87 将栈顶int型数值强制转换成double型数值并将结果压入栈顶
#define OP_L2I 136 // 0x88 将栈顶long型数值强制转换成int型数值并将结果压入栈顶
#define OP_L2F 137 // 0x89 将栈顶long型数值强制转换成float型数值并将结果压入栈顶
#define OP_L2D 138 // 0x8a 将栈顶long型数值强制转换成double型数值并将结果压入栈顶
#define OP_F2I 139 // 0x8b 将栈顶float型数值强制转换成int型数值并将结果压入栈顶
#define OP_F2L 140 // 0x8c 将栈顶float型数值强制转换成long型数值并将结果压入栈顶
#define OP_F2D 141 // 0x8d 将栈顶float型数值强制转换成double型数值并将结果压入栈顶
#define OP_D2I 142 // 0x8e 将栈顶double型数值强制转换成int型数值并将结果压入栈顶
#define OP_D2L 143 // 0x8f 将栈顶double型数值强制转换成long型数值并将结果压入栈顶
#define OP_D2F 144 // 0x90 将栈顶double型数值强制转换成float型数值并将结果压入栈顶
#define OP_I2B 145 // 0x91 将栈顶int型数值强制转换成byte型数值并将结果压入栈顶
#define OP_I2C 146 // 0x92 将栈顶int型数值强制转换成char型数值并将结果压入栈顶
#define OP_I2S 147 // 0x93 将栈顶int型数值强制转换成short型数值并将结果压入栈顶
// 比较
#define OP_LCMP 148      // 0x94 比较栈顶两long型数值大小，并将结果（1，0，-1）压入栈顶
#define OP_FCMPL 149     // 0x95 比较栈顶两float型数值大小，并将结果（1，0，-1）压入栈顶；当其中一个数值为“NaN”时，将-1压入栈顶
#define OP_FCMPG 150     // 0x96 比较栈顶两float型数值大小，并将结果（1，0，-1）压入栈顶；当其中一个数值为“NaN”时，将1压入栈顶
#define OP_DCMPL 151     // 0x97 比较栈顶两double型数值大小，并将结果（1，0，-1）压入栈顶；当其中一个数值为“NaN”时，将-1压入栈顶
#define OP_DCMPG 152     // 0x98 比较栈顶两double型数值大小，并将结果（1，0，-1）压入栈顶；当其中一个数值为“NaN”时，将1压入栈顶
#define OP_IFEQ 153      // 0x99 当栈顶int型数值等于0时跳转
#define OP_IFNE 154      // 0x9a 当栈顶int型数值不等于0时跳转
#define OP_IFLT 155      // 0x9b 当栈顶int型数值小于0时跳转
#define OP_IFGE 156      // 0x9c 当栈顶int型数值大于等于0时跳转
#define OP_IFGT 157      // 0x9d 当栈顶int型数值大于0时跳转
#define OP_IFLE 158      // 0x9e 当栈顶int型数值小于等于0时跳转
#define OP_IF_ICMPEQ 159 // 0x9f 比较栈顶两int型数值大小，当结果等于0时跳转
#define OP_IF_ICMPNE 160 // 0xa0 比较栈顶两int型数值大小，当结果不等于0时跳转
#define OP_IF_ICMPLT 161 // 0xa1 比较栈顶两int型数值大小，当结果小于0时跳转
#define OP_IF_ICMPGE 162 // 0xa2 比较栈顶两int型数值大小，当结果大于等于0时跳转
#define OP_IF_ICMPGT 163 // 0xa3 比较栈顶两int型数值大小，当结果大于0时跳转
#define OP_IF_ICMPLE 164 // 0xa4 比较栈顶两int型数值大小，当结果小于等于0时跳转
#define OP_IF_ACMPEQ 165 // 0xa5 比较栈顶两引用型数值，当结果相等时跳转
#define OP_IF_ACMPNE 166 // 0xa6 比较栈顶两引用型数值，当结果不相等时跳转
// 控制
#define OP_GOTO 167         // 0xa7 无条件跳转
#define OP_JSR 168          // 0xa8 跳转至指定16位offset位置，并将jsr下一条指令地址压入栈顶
#define OP_RET 169          // 0xa9 返回至局部变量指定的index的指令位置（一般与jsr，jsr_w联合使用）
#define OP_TABLESWITCH 170  // 0xaa 用于switch条件跳转，case值连续（可变长度指令）
#define OP_LOOKUPSWITCH 171 // 0xab 用于switch条件跳转，case值不连续（可变长度指令）
#define OP_IRETURN 172      // 0xac 从当前方法返回int
#define OP_LRETURN 173      // 0xad 从当前方法返回long
#define OP_FRETURN 174      // 0xae 从当前方法返回float
#define OP_DRETURN 175      // 0xaf 从当前方法返回double
#define OP_ARETURN 176      // 0xb0 从当前方法返回对象引用
#define OP_RETURN 177       // 0xb1 从当前方法返回void
// 引用
#define OP_GETSTATIC 178       // 0xb2 获取指定类的静态域，并将其值压入栈顶
#define OP_PUTSTATIC 179       // 0xb3 为指定的类的静态域赋值
#define OP_GETFIELD 180        // 0xb4 获取指定类的实例域，并将其值压入栈顶
#define OP_PUTFIELD 181        // 0xb5 为指定的类的实例域赋值
#define OP_INVOKEVIRTUAL 182   // 0xb6 调用实例方法
#define OP_INVOKESPECIAL 183   // 0xb7 调用超类构造方法，实例初始化方法，私有方法
#define OP_INVOKESTATIC 184    // 0xb8 调用静态方法
#define OP_INVOKEINTERFACE 185 // 0xb9 调用接口方法
#define OP_INVOKEDYNAMIC 186   // 0xba 调用动态链接方法
#define OP_NEW 187             // 0xbb 创建一个对象，并将其引用值压入栈顶
#define OP_NEWARRAY 188        // 0xbc 创建一个指定原始类型（如int、float、char„„）的数组，并将其引用值压入栈顶
#define OP_ANEWARRAY 189       // 0xbd 创建一个引用型（如类，接口，数组）的数组，并将其引用值压入栈顶
#define OP_ARRAYLENGTH 190     // 0xbe 获得数组的长度值并压入栈顶
#define OP_ATHROW 191          // 0xbf 将栈顶的异常抛出
#define OP_CHECKCAST 192       // 0xc0 检验类型转换，检验未通过将抛出ClassCastException
#define OP_INSTANCEOF 193      // 0xc1 检验对象是否是指定的类的实例，如果是将1压入栈顶，否则将0压入栈顶
#define OP_MONITORENTER 194    // 0xc2 获得对象的monitor，用于同步方法或同步块
#define OP_MONITOREXIT 195     // 0xc3 释放对象的monitor，用于同步方法或同步块
// 扩展
#define OP_WIDE 196           // 0xc4 扩展访问局部变量表的索引宽度
#define OP_MULTIANEWARRAY 197 // 0xc5 创建指定类型和指定维度的多维数组（执行该指令时，操作栈中必须包含各维度的长度值），并将其引用值压入栈顶
#define OP_IFNULL 198         // 0xc6 为null时跳转
#define OP_IFNONNULL 199      // 0xc7 不为null时跳转
#define OP_GOTO_W 200         // 0xc8 无条件跳转（宽索引）
#define OP_JSR_W 201          // 0xc9 跳转至指定32位地址偏移量位置，并将jsr_w下一条指令地址压入栈顶 保留指令
// 保留指令
#define OP_BREAKPOINT 202 // 0xca 调试时的断点标志
#define OP_IMPDEP1 254    // 0xfe 用于在特定硬件中使用的语言后门
#define OP_IMPDEP2 255    // 0xff 用于在特定硬件中使用的语言后门

// 常量
// NOP 0         0x00 什么都不做
// ACONST_NULL 1 0x01 将null推送至栈顶
// ICONST_M1 2   0x02 将int型-1推送至栈顶
// ICONST_0 3    0x03 将int型0推送至栈顶
// ICONST_1 4    0x04 将int型1推送至栈顶
// ICONST_2 5    0x05 将int型2推送至栈顶
// ICONST_3 6    0x06 将int型3推送至栈顶
// ICONST_4 7    0x07 将int型4推送至栈顶
// ICONST_5 8    0x08 将int型5推送至栈顶
// LCONST_0 9    0x09 将long型0推送至栈顶
// LCONST_1 10   0x0a 将long型1推送至栈顶
// FCONST_0 11   0x0b 将float型0推送至栈顶
// FCONST_1 12   0x0c 将float型1推送至栈顶
// FCONST_2 13   0x0d 将float型2推送至栈顶
// DCONST_0 14   0x0e 将double型0推送至栈顶
// DCONST_1 15   0x0f 将double型1推送至栈顶
// BIPUSH 16     0x10 将单字节的常量值（-128~127）推送至栈顶
// SIPUSH 17     0x11 将一个短整型常量值（-32768~32767）推送至栈顶
// LDC 18        0x12 将int，float或String型常量值从常量池中推送至栈顶
// LDC_W 19      0x13 将int，float或String型常量值从常量池中推送至栈顶（宽索引）
// LDC2_W 20     0x14 将long或double型常量值从常量池中推送至栈顶（宽索引）
// 加载
// ILOAD 21   0x15 将指定的int型局部变量推送至栈顶
// LLOAD 22   0x16 将指定的long型局部变量推送至栈顶
// FLOAD 23   0x17 将指定的float型局部变量推送至栈顶
// DLOAD 24   0x18 将指定的double型局部变量推送至栈顶
// ALOAD 25   0x19 将指定的引用类型局部变量推送至栈顶
// ILOAD_0 26 0x1a 将第一个int型局部变量推送至栈顶
// ILOAD_1 27 0x1b 将第二个int型局部变量推送至栈顶
// ILOAD_2 28 0x1c 将第三个int型局部变量推送至栈顶
// ILOAD_3 29 0x1d 将第四个int型局部变量推送至栈顶
// LLOAD_0 30 0x1e 将第一个long型局部变量推送至栈顶
// LLOAD_1 31 0x1f 将第二个long型局部变量推送至栈顶
// LLOAD_2 32 0x20 将第三个long型局部变量推送至栈顶
// LLOAD_3 33 0x21 将第四个long型局部变量推送至栈顶
// FLOAD_0 34 0x22 将第一个float型局部变量推送至栈顶
// FLOAD_1 35 0x23 将第二个float型局部变量推送至栈顶
// FLOAD_2 36 0x24 将第三个float型局部变量推送至栈顶
// FLOAD_3 37 0x25 将第四个float型局部变量推送至栈顶
// DLOAD_0 38 0x26 将第一个double型局部变量推送至栈顶
// DLOAD_1 39 0x27 将第二个double型局部变量推送至栈顶
// DLOAD_2 40 0x28 将第三个double型局部变量推送至栈顶
// DLOAD_3 41 0x29 将第四个double型局部变量推送至栈顶
// ALOAD_0 42 0x2a 将第一个引用类型局部变量推送至栈顶
// ALOAD_1 43 0x2b 将第二个引用类型局部变量推送至栈顶
// ALOAD_2 44 0x2c 将第三个引用类型局部变量推送至栈顶
// ALOAD_3 45 0x2d 将第四个引用类型局部变量推送至栈顶
// IALOAD 46  0x2e 将int型数组指定索引的值推送至栈顶
// LALOAD 47  0x2f 将long型数组指定索引的值推送至栈顶
// FALOAD 48  0x30 将float型数组指定索引的值推送至栈顶
// DALOAD 49  0x31 将double型数组指定索引的值推送至栈顶
// AALOAD 50  0x32 将引用型数组指定索引的值推送至栈顶
// BALOAD 51  0x33 将boolean或byte型数组指定索引的值推送至栈顶
// CALOAD 52  0x34 将char型数组指定索引的值推送至栈顶
// SALOAD 53  0x35 将short型数组指定索引的值推送至栈顶
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
// 栈
// POP 87     0x57 将栈顶数值弹出（数值不能是long或double类型的）
// POP2 88    0x58 将栈顶的一个（long或double类型的）或两个数值弹出（其它）
// DUP 89     0x59 复制栈顶数值并将复制值压入栈顶
// DUP_X1 90  0x5a 复制栈顶数值并将两个复制值压入栈顶
// DUP_X2 91  0x5b 复制栈顶数值并将三个（或两个）复制值压入栈顶
// DUP2 92    0x5c 复制栈顶一个（long或double类型的)或两个（其它）数值并将复制值压入栈顶
// DUP2_X1 93 0x5d dup_x1指令的双倍版本
// DUP2_X2 94 0x5e dup_x2指令的双倍版本
// SWAP 95    0x5f 将栈最顶端的两个数值互换（数值不能是long或double类型的）
// 数学
// IADD 96   0x60 将栈顶两int型数值相加并将结果压入栈顶
// LADD 97   0x61 将栈顶两long型数值相加并将结果压入栈顶
// FADD 98   0x62 将栈顶两float型数值相加并将结果压入栈顶
// DADD 99   0x63 将栈顶两double型数值相加并将结果压入栈顶
// ISUB 100  0x64 将栈顶两int型数值相减并将结果压入栈顶
// LSUB 101  0x65 将栈顶两long型数值相减并将结果压入栈顶
// FSUB 102  0x66 将栈顶两float型数值相减并将结果压入栈顶
// DSUB 103  0x67 将栈顶两double型数值相减并将结果压入栈顶
// IMUL 104  0x68 将栈顶两int型数值相乘并将结果压入栈顶
// LMUL 105  0x69 将栈顶两long型数值相乘并将结果压入栈顶
// FMUL 106  0x6a 将栈顶两float型数值相乘并将结果压入栈顶
// DMUL 107  0x6b 将栈顶两double型数值相乘并将结果压入栈顶
// IDIV 108  0x6c 将栈顶两int型数值相除并将结果压入栈顶
// LDIV 109  0x6d 将栈顶两long型数值相除并将结果压入栈顶
// FDIV 110  0x6e 将栈顶两float型数值相除并将结果压入栈顶
// DDIV 111  0x6f 将栈顶两double型数值相除并将结果压入栈顶
// IREM 112  0x70 将栈顶两int型数值作取模运算并将结果压入栈顶
// LREM 113  0x71 将栈顶两long型数值作取模运算并将结果压入栈顶
// FREM 114  0x72 将栈顶两float型数值作取模运算并将结果压入栈顶
// DREM 115  0x73 将栈顶两double型数值作取模运算并将结果压入栈顶
// INEG 116  0x74 将栈顶int型数值取负并将结果压入栈顶
// LNEG 117  0x75 将栈顶long型数值取负并将结果压入栈顶
// FNEG 118  0x76 将栈顶float型数值取负并将结果压入栈顶
// DNEG 119  0x77 将栈顶double型数值取负并将结果压入栈顶
// ISHL 120  0x78 将int型数值左移位指定位数并将结果压入栈顶
// LSHL 121  0x79 将long型数值左移位指定位数并将结果压入栈顶
// ISHR 122  0x7a 将int型数值右（有符号）移位指定位数并将结果压入栈顶
// LSHR 123  0x7b 将long型数值右（有符号）移位指定位数并将结果压入栈顶
// IUSHR 124 0x7c 将int型数值右（无符号）移位指定位数并将结果压入栈顶
// LUSHR 125 0x7d 将long型数值右（无符号）移位指定位数并将结果压入栈顶
// IAND 126  0x7e 将栈顶两int型数值作“按位与”并将结果压入栈顶
// LAND 127  0x7f 将栈顶两long型数值作“按位与”并将结果压入栈顶
// IOR 128   0x80 将栈顶两int型数值作“按位或”并将结果压入栈顶
// LOR 129   0x81 将栈顶两long型数值作“按位或”并将结果压入栈顶
// IXOR 130  0x82 将栈顶两int型数值作“按位异或”并将结果压入栈顶
// LXOR 131  0x83 将栈顶两long型数值作“按位异或”并将结果压入栈顶
// IINC 132  0x84 将指定int型变量增加指定值
// 转换
// I2L 133 0x85 将栈顶int型数值强制转换成long型数值并将结果压入栈顶
// I2F 134 0x86 将栈顶int型数值强制转换成float型数值并将结果压入栈顶
// I2D 135 0x87 将栈顶int型数值强制转换成double型数值并将结果压入栈顶
// L2I 136 0x88 将栈顶long型数值强制转换成int型数值并将结果压入栈顶
// L2F 137 0x89 将栈顶long型数值强制转换成float型数值并将结果压入栈顶
// L2D 138 0x8a 将栈顶long型数值强制转换成double型数值并将结果压入栈顶
// F2I 139 0x8b 将栈顶float型数值强制转换成int型数值并将结果压入栈顶
// F2L 140 0x8c 将栈顶float型数值强制转换成long型数值并将结果压入栈顶
// F2D 141 0x8d 将栈顶float型数值强制转换成double型数值并将结果压入栈顶
// D2I 142 0x8e 将栈顶double型数值强制转换成int型数值并将结果压入栈顶
// D2L 143 0x8f 将栈顶double型数值强制转换成long型数值并将结果压入栈顶
// D2F 144 0x90 将栈顶double型数值强制转换成float型数值并将结果压入栈顶
// I2B 145 0x91 将栈顶int型数值强制转换成byte型数值并将结果压入栈顶
// I2C 146 0x92 将栈顶int型数值强制转换成char型数值并将结果压入栈顶
// I2S 147 0x93 将栈顶int型数值强制转换成short型数值并将结果压入栈顶
// 比较
// LCMP 148      0x94 比较栈顶两long型数值大小，并将结果（1，0，-1）压入栈顶
// FCMPL 149     0x95 比较栈顶两float型数值大小，并将结果（1，0，-1）压入栈顶；当其中一个数值为“NaN”时，将-1压入栈顶
// FCMPG 150     0x96 比较栈顶两float型数值大小，并将结果（1，0，-1）压入栈顶；当其中一个数值为“NaN”时，将1压入栈顶
// DCMPL 151     0x97 比较栈顶两double型数值大小，并将结果（1，0，-1）压入栈顶；当其中一个数值为“NaN”时，将-1压入栈顶
// DCMPG 152     0x98 比较栈顶两double型数值大小，并将结果（1，0，-1）压入栈顶；当其中一个数值为“NaN”时，将1压入栈顶
// IFEQ 153      0x99 当栈顶int型数值等于0时跳转
// IFNE 154      0x9a 当栈顶int型数值不等于0时跳转
// IFLT 155      0x9b 当栈顶int型数值小于0时跳转
// IFGE 156      0x9c 当栈顶int型数值大于等于0时跳转
// IFGT 157      0x9d 当栈顶int型数值大于0时跳转
// IFLE 158      0x9e 当栈顶int型数值小于等于0时跳转
// IF_ICMPEQ 159 0x9f 比较栈顶两int型数值大小，当结果等于0时跳转
// IF_ICMPNE 160 0xa0 比较栈顶两int型数值大小，当结果不等于0时跳转
// IF_ICMPLT 161 0xa1 比较栈顶两int型数值大小，当结果小于0时跳转
// IF_ICMPGE 162 0xa2 比较栈顶两int型数值大小，当结果大于等于0时跳转
// IF_ICMPGT 163 0xa3 比较栈顶两int型数值大小，当结果大于0时跳转
// IF_ICMPLE 164 0xa4 比较栈顶两int型数值大小，当结果小于等于0时跳转
// IF_ACMPEQ 165 0xa5 比较栈顶两引用型数值，当结果相等时跳转
// IF_ACMPNE 166 0xa6 比较栈顶两引用型数值，当结果不相等时跳转
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
// 扩展
// WIDE 196           0xc4 扩展访问局部变量表的索引宽度
// MULTIANEWARRAY 197 0xc5 创建指定类型和指定维度的多维数组（执行该指令时，操作栈中必须包含各维度的长度值），并将其引用值压入栈顶
// IFNULL 198         0xc6 为null时跳转
// IFNONNULL 199      0xc7 不为null时跳转
// GOTO_W 200         0xc8 无条件跳转（宽索引）
// JSR_W 201          0xc9 跳转至指定32位地址偏移量位置，并将jsr_w下一条指令地址压入栈顶 保留指令
// 保留指令
// BREAKPOINT 202 0xca 调试时的断点标志
// IMPDEP1 254    0xfe 用于在特定硬件中使用的语言后门
// IMPDEP2 255    0xff 用于在特定硬件中使用的语言后门

#endif
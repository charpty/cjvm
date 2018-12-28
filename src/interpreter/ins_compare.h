#ifndef MOON_INS_COMPARE_H
#define MOON_INS_COMPARE_H

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

#endif

#include <stdlib.h>
#include <classreader.h>

const int CONSTANT_Class = 7;
const int CONSTANT_Fieldref = 9;
const int CONSTANT_Methodref = 10;
const int CONSTANT_InterfaceMethodref = 11;
const int CONSTANT_String = 8;
const int CONSTANT_Integer = 3;
const int CONSTANT_Float = 4;
const int CONSTANT_Long = 5;
const int CONSTANT_Double = 6;
const int CONSTANT_NameAndType = 12;
const int CONSTANT_Utf8 = 1;
const int CONSTANT_MethodHandle = 15;
const int CONSTANT_MethodType = 16;
const int CONSTANT_InvokeDynamic = 18;

typedef struct CpInfo
{
    uint8_t tag;
    uint8_t *info;
} CpInfo;

typedef struct Cp
{
    int len;
    CpInfo **infos;
} Cp;

CpInfo *readConstantInfo(ClassReader *r, Cp *cp)
{
    CpInfo *rs = (CpInfo *)malloc(sizeof(struct CpInfo));
    rs->tag = readUint8(r);
    // TODO
    return NULL;
}

Cp *readConstantPool(ClassReader *r)
{
    Cp *rs = (Cp *)malloc(sizeof(struct Cp));

    int cpCount = readUint16(r);
    rs->infos = (CpInfo **)malloc(cpCount * sizeof(CpInfo *));

    for (int i = 0; i < cpCount; i++)
    {
        rs->infos[i] = readConstantInfo(r, rs);
        // http://docs.oracle.com/javase/specs/jvms/se8/html/jvms-4.html#jvms-4.4.5
        // 这就是个数的特殊情况，读到long和double时，必须下一个元素是个空，以兼容老版本
        // 这是由于一个byte占常量池2个位置
        if (rs->infos[i]->tag == CONSTANT_Long || (rs->infos[i]->tag = CONSTANT_Double))
        {
            i++;
            continue;
        }
    }
    return rs;
}

// C string
char *getClassName(Cp *cp, uint16_t index)
{
    return NULL;
}


typedef struct File
{
    // 文件路径：/tmp/cc.jar; /tmp/com/charpty/Test.class
    char *path;
    char *data;
    int len;
} File;

File *readFile(char *filepath);

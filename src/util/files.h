
typedef struct File
{
    char *data;
    int len;
} File;

File *readFile(char *filepath);
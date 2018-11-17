#define LOG_DEBUG(format, x...) logDebug(__FILE__, __LINE__, format, x)

#define LOG_ERROR(format, x...) logError(__FILE__, __LINE__, format, x)

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

void logDebug(char *file, int line, char *format, ...);
void logError(char *file, int line, char *format, ...);
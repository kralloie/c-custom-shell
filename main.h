#include "commands.c"

#define SHELL_PREFIX "$ "
#define MAX_INPUT 1024
#define MAX_ARGS 100
#define RUNNING 1
#define TAB_KEY 9
#define ENTER_KEY 13
#define BACKSPACE 8
#define MAX_INPUT 1024
#define SPACEBAR 32
#define UP_ARROW 0x48
#define DOWN_ARROW 0x50
#define RIGHT_ARROW 0x4D
#define LEFT_ARROW 0x4B
#define MAX_HISTORY 100

typedef void (*CommandFunc)(char*, char**, int*);

typedef struct Command {
    const char* name;
    CommandFunc func;
} Command;

void echo(char *inputCommand, char **args, int *argc);
void ls(char *inputCommand, char **args, int *argc);
void cd(char *inputCommand, char **args, int *argc);
void clear(char*, char**, int*);
void exitShell(char*, char**, int*);
void touch(char *inputCommand, char **args, int *argc);
void makedir(char *inputCommand, char **args, int *argc);
void rm(char *inputCommand, char **args, int *argc);
void cat(char *inputCommand, char **args, int *argc);
void historyCommand(char *inputCommand, char **args, int *argc);
void cp(char *inputCommand, char **args, int *argc);
void mv(char *inputCommand, char **args, int *argc);
int getCursorY();
int getCursorX();
int getFilesCount(char *path);
int *getFilesLen(char *path, int fileCount);
char **getPathAndFilename(char* path);
char **getFileNames(char* path);
char *strToLower(char* str, int length);
char *getQuotatedName(char *str);
int hasAlphanumeric(char *arg);
void printHistory(char **history, int *historyCount);
char username[UNLEN + 1];
DWORD username_len = sizeof(username);
extern char *history[];
extern int historyCount;

Command commands[] = {
    { "echo", echo },
    { "ls", ls },
    { "cd", cd },
    { "clear", clear },
    { "exit", exitShell },
    { "touch", touch },
    { "mkdir", makedir },
    { "rm", rm },
    { "cat", cat },
    { "history", historyCommand },
    { "cp", cp },
    { "mv", mv }
};

const int commandCount = sizeof(commands) / sizeof(Command);
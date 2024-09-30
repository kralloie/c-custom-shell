#pragma once

#include <windows.h>

typedef void (*CommandFunc)(char*, char**, int*);

typedef struct Command {
    const char* name;
    CommandFunc func;
} Command;

void echo(char *inputCommand, char **args, int* argc) {
    int outputLen = 0;

    for (int i = 0; i < *argc; i++) {
        outputLen += strlen(args[i]) + 1;
    }

    char *output = malloc(outputLen * sizeof(char));

    if (output == NULL) {
        return;
    }

    output[0] = '\0';

    for (int i = 0; i < *argc; i++) {
        if (strcmp(args[i], inputCommand) != 0) {
            strcat(output, args[i]);
            strcat(output, " ");
        }
    }

    if (strlen(output) > 0) {
        output[strlen(output) - 1] = '\0';
    }

    printf("%s\n", output);

    free(output);
    return;
}

void ls (char *inputCommand, char **args, int* argc) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    char cwd[MAX_PATH];

    if (_getcwd(cwd, sizeof(cwd)) == NULL) {
        return;
    }

    char searchPattern[MAX_PATH];

    snprintf(searchPattern, sizeof(searchPattern), "%s\\*", (*argc > 1) ? args[1] : cwd);

    hFind = FindFirstFile(searchPattern, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("No files in this directory.\n");
        return;
    }

    do {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? 10 : 7);
        printf("%s%c\n", findFileData.cFileName, (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? '/' : ' ');
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
    return;
}

void cd(char *inputCommand, char **args, int* argc) {
    if(*argc < 2) {
        return;
    }

    if(_chdir(args[1]) != 0) {
        printf("Invalid directory.\n");
    }

    return;
}

void clear() {
    system("cls");
    return;
}

void exitShell() {
    exit(0);
}

const Command commands[] = {
    { "echo", echo },
    { "ls", ls },
    { "cd", cd },
    { "clear", clear },
    { "exit", exitShell }
};
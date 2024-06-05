#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdbool.h>
struct pos
{
    int line;
    int col;
    const char* filename;
};

enum
{
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_SYMBOL,
    TOKEN_TYPE_COMMENT,
    TOKENT_TYPE_NEWLINE
};

struct token
{
    int type;
    int flags;

    union
    {

        char cval;
        const char* sval;
        unsigned int inum;
        unsigned long lnum;
        unsigned long long llnum;
        void* any;
    };
    
    // True if there is a whitespace between the token and the next token
    bool whitespace;

    // (5+10+20)
    const char* between_bracketss;

};

enum
{
    COMPILER_FILE_COMPILED_OK,
    COMPILER_FILE_WITH_ERRORS
};

struct compile_process
{
    // The flags indicates how this file should be compiled
    int flags;

    struct compile_process_input_file
    {
        FILE* fp;
        const char* abs_path;
    }cfile;

    FILE* ofile;
};

int compile_file(const char* filename, const char* out_filename, int flags);

#endif
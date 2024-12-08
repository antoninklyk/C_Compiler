#ifndef COMPILER_H
#define  COMPILER_H

#include <stdio.h>
#include <stdbool.h>

// need to know the position on the file
struct pos
{
    int line;
    int col;
    const char* filename;
};

// Token types enumeration
enum
{
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_SYMBOL,
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_NEWLINE
};

struct token
{
    int type;
    int flags;

    // A union in C is a special data type that allows you to store different data types in the same memory location. 
    // However, at any given time, only one of the data members can contain a value, as all members of the union share the same memory space. This is in contrast to a struct, where each member has its own memory.
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
    // whitespace between tokens
    bool whitespace;

    // (Hello World) (5+10+20)
    const char* between_bracketss;

};

struct lex_process
{
    struct pos pos;
    struct vector* token_vec;
    struct compile_process* compiler;

    int current_expression_count;
    struct buffer* parentheses_buffer;
    struct lex_process_functions* function;

    // This will be private data that the lexer does understand but the person using lexer understand
    void* private;
}

enum
{
    COMPILER_FILE_COMPILED_OK,
    COMPILER_FAILED_WITH_ERRORS
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
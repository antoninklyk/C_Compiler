#ifndef COMPILER_H
#define  COMPILER_H

#include <stdio.h>
#include <stdbool.h>

#define NUMERIC CASES \
    case '0':         \
    case '1':         \
    case '2':         \
    case '3':         \
    case '4':         \
    case '5':         \
    case '6':         \
    case '7':         \
    case '8':         \
    case '9'


// need to know the position on the file
struct pos
{
    int line;
    int col;
    const char* filename;
};

enum
{
    LEXICAL_ANALYSIS_ALL_OK,
    LEXICAL_ANALYSIS_INPUT_ERROR
};

// Token types enumeration
enum
{
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_SYMBOL,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_NEWLINE
};

struct token
{
    int type;
    int flags;
    struct pos pos;
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

    const char* between_brackets;

};

struct lex_process;
typedef char (*LEX_PROCESS_NEXT_CHAR)(struct lex_process* process);
typedef char (*LEX_PROCESS_PEEK_CHAR)(struct lex_process* process);
typedef char (*LEX_PROCESS_PUSH_CHAR)(struct lex_process* process, char c);

struct lex_process_functions
{
    LEX_PROCESS_NEXT_CHAR next_char;
    LEX_PROCESS_PEEK_CHAR peek_char;
    LEX_PROCESS_PUSH_CHAR push_char;

};

struct lex_process
{
    struct pos pos;
    struct vector* token_vec;
    struct compile_process* compiler;
    int current_expression_count;
    struct buffer* parentheses_buffer;
    struct lex_process_functions* function;
    // This will be private data that the lexer doesn't understand but the person using lexer understand
    void* user_data;
};

enum
{
    COMPILER_FILE_COMPILED_OK,
    COMPILER_FAILED_WITH_ERRORS
};

struct compile_process
{
    // The flags indicates how this file should be compiled
    int flags;
    struct pos pos;
    struct compile_process_input_file
    {
        FILE* fp;
        const char* abs_path;
    }cfile;

    FILE* ofile;
};

int compile_file(const char* filename, const char* out_filename, int flags);

char compile_process_next_char(struct lex_process* lex_process);
char compile_process_peek_char(struct lex_process* lex_process);
void compile_process_push_char(struct lex_process* lex_process, char c);

struct lex_process* lex_process_create(struct compile_process* compiler, struct lex_process_functions* functions, void* user_data);
void lex_process_free(struct lex_process* process);
void lex_process_private(struct lex_process* process);
struct vector* lex_process_tokens(struct lex_process* process);

int lex(struct lex_process* process);

void compiler_error(struct compile_process* compiler, char* msg,...);
void compiler_warning(struct compile_process* compiler, char* msg,...);
#endif
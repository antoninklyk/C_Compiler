#include <stdio.h>
#include <stdlib.h>
#include <compiler.h>

/*function responsible to initialize our compile process structure, donnes l'image initiale du compile process*/
struct compile_process* compile_process_create(const char* filename, const char* filename_out, int flags)
{

    FILE* file = fopen(filename, "r"); //Entry of cprocess
    if(!file)
    {
        return NULL; //si l'ouverture fichier en mode read a failed, renvoie une structure compile process nulle
    }

    FILE* out_file = NULL;
    if(filename_out) // if we not provide a file for output, we not provide a file for writing
    {
        FILE* out_file = fopen(filename_out, "w"); //Output of cprocess
        if(!out_file)
        {
            return NULL;
        }
    }

    struct compile_process* process = calloc(1, sizeof(struct compile_process)); //J'initialise ma structure avec tout les files (I/O) qu'il faut
    process->cfile.fp= file;
    process->ofile = out_file;
    process->flags = flags;
    return process;

}

char compile_process_next_char(struct lex_process* lex_process)
{
    struct compile_process* compiler = lex_process->compiler;
    compiler-> pos.col += 1;
    char c = getc(compiler->cfile.fp);
    
    if(c == '\n')
    {
        compiler->pos.col = 1;
        compiler->pos.line += 1;
    }
    //a la fin le curseur est un caractère plus loin dans le flux

    return c;

}

// peek = make a look
char compile_process_peek_char(struct lex_process* lex_process)
{
    struct compile_process* compiler = lex_process->compiler;
    char c = getc(compiler->cfile.fp); //le caractere est prit du flux
    ungetc(c, compiler->cfile.fp); //le caractere est remit dans le flux
    //a la fin le curseur est toujours sur le meme caractere dans le flux
    return c;
}

void compile_process_push_char(struct lex_process* lex_process, char c)
{
    struct compile_process* compiler = lex_process->compiler;
    ungetc(c, compiler->cfile.fp); //J’ai lu un caractère inutile, je le replace dans fluxpour qu’il soit traité plus tard.
}
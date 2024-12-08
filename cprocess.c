#include <stdio.h>
#include <stdlib.h>
#include <compiler.h>

/*function responsible to initialize our compile process structure, donnes l'image initiale du compile process*/
struct compile_process* compile_process_create(const char* filename, const char* filename_out, int flags)
{

    FILE* file = fopen(filename, "r"); //Entry of cprocess
    if(!file)
    {
        return NULL; //renvoie une structure compile process nulle
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
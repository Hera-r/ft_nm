#ifndef FT_NM_H
#define FT_NM_H

#include <fcntl.h>
#include <sys/mman.h>
#include <ar.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <elf.h>
#include <sys/stat.h>
#include <libft.h>



typedef struct s_symbols
{
    uint64_t    st_value;
    char        symbol_type;
    char        *symbol_name;
}               t_symbols;


#endif
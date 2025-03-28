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
#include <libft.h> // Assure-toi que ce chemin est bon dans ton projet


typedef struct s_symbols
{
	uint64_t	st_value;
	char		symbol_type;
	char		*symbol_name;
}				t_symbols;

// ─────────────────────────────
// Fonctions ELF
// ─────────────────────────────

char			get_symbol_type(Elf64_Sym *sym, Elf64_Shdr *shdr_tab);
int				check_elf_magic(Elf64_Ehdr *ehdr);
Elf64_Shdr		*find_symtab(Elf64_Ehdr *ehdr, Elf64_Shdr *section_header);

// ─────────────────────────────
// Fonctions format/affichage
// ─────────────────────────────
void			ft_print_hexa(unsigned int nb);
void			ft_hexadecimal(unsigned int nb);
void			ft_nm_error(const char *filename, const char *message);
int				ft_nb_numb(unsigned int nb);
char			*formated_ar_name(const char *ar_name);


// ─────────────────────────────
// Fonction principale archive
// ─────────────────────────────

int				handle_archive(void *ptr, char *end, const char *filename);

#endif

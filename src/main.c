#include "../include/ft_nm.h"

char get_symbol_type(Elf64_Sym *sym) {
	unsigned char type = ELF64_ST_TYPE(sym->st_info);
	unsigned char bind = ELF64_ST_BIND(sym->st_info);
	if (sym->st_shndx == SHN_UNDEF) return 'U';
	if (type == STT_FUNC) return (bind == STB_LOCAL) ? 't' : 'T';
	if (type == STT_OBJECT) return (bind == STB_LOCAL) ? 'd' : 'D';
	return '?'; // verifier pour les autres type de symbole comme B
}


int	ft_nb_numb(unsigned int nb)
{
	int	n = 0;

	if (nb == 0)
		return 0;

	while (nb >= 16)
	{
		nb = nb / 16;
		n++;
	}
	return (n == 0) ? 1 : n;
}


void	ft_hexadecimal(unsigned int nb)
{
	char	*hexa;

	if (nb == 0)
	{
		write(1, "0", 1);
	}
	else
	{
		hexa = "0123456789abcdef";

		if (nb >= 16)
		{
			ft_hexadecimal(nb / 16);
			ft_hexadecimal(nb % 16);
		}
		else
			write(1, &hexa[nb], 1);
	}
}


void	ft_print_hexa(unsigned int nb) {
	int nb_num = ft_nb_numb(nb);
	
	for (int i = 0; i < (15 - nb_num); i++)
		ft_putchar_fd('0', STDOUT_FILENO);
	ft_hexadecimal(nb);
}


int	check_elf_magic(Elf64_Ehdr *ehdr) {
	if (ehdr->e_ident[0] != ELFMAG0 || ehdr->e_ident[1] != ELFMAG1 || ehdr->e_ident[2] != ELFMAG2 || ehdr->e_ident[3] != ELFMAG3) {
		// ft_putstr_fd("Ce n'est pas un fichier ELF valide.\n", STDOUT_FILENO);
		return 1;
	}
	return 0;
}

Elf64_Shdr	*find_symtab(Elf64_Ehdr *ehdr, Elf64_Shdr *section_header)
{
	Elf64_Shdr *symtab = NULL;

	for (int i = 0; i < ehdr->e_shnum; i++) {
		Elf64_Shdr *sy = (Elf64_Shdr *)((char *)section_header + (i * ehdr->e_shentsize));
		if (sy->sh_type == SHT_SYMTAB) {
			symtab = sy;
			break;
		}
	}

	return symtab;
}

char *formated_ar_name(const char *ar_name)  // j'ai malloc dans cette fonction
{
    char raw_name[17];

    ft_memcpy(raw_name, ar_name, 16);
    raw_name[16] = '\0';

    for (int i = 15; i >= 0; i--) {
        if (raw_name[i] == ' ' || raw_name[i] == '/' || raw_name[i] == '\0') {
            raw_name[i] = '\0';
        } else
            break;
    }

    char *result = malloc(17);
    if (!result)
        return NULL;

    ft_strlcpy(result, raw_name, 17);

    return result;
}



int main(int argc, char *argv[]) {
	if (argc < 2) {
		ft_putstr_fd("nm: 'a.out': No such file\n", STDOUT_FILENO);
		return 1;
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		perror("open");
		return 1;
	}

	struct stat st;
	if (fstat(fd, &st) < 0) {
		perror("fstat");
		return 1;
	}

	void *file_mem = mmap(NULL, st.st_size , PROT_READ, MAP_PRIVATE, fd, 0);
	if (file_mem == MAP_FAILED) {
		perror("mmap");
		return 1;
	}

	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)file_mem;
	Elf64_Shdr *section_header = (Elf64_Shdr *)(file_mem + ehdr->e_shoff);
	
	// t_symbols *symbol_tab;
	int nb_symbols = 0;

	if (ft_strncmp(file_mem, "!<arch>\n", SARMAG) == 0) 
	{
		char	*ptr = (char *)file_mem + SARMAG;
		char	*end = (char *)file_mem + st.st_size;

		while (1) {
			if (ptr + sizeof(struct ar_hdr) > end)
				break;

			struct ar_hdr *hdr = (struct ar_hdr *)ptr;
			printf("* %ld\n", ft_strlen(hdr->ar_name));
			printf("%s\n", formated_ar_name(hdr->ar_name)); // printf ici faut changer!! 
			ptr += sizeof(struct ar_hdr);
			size_t size = ft_atoi(hdr->ar_size);

			if (ptr + size > end)
				break;

			if (size >= sizeof(Elf64_Ehdr)) {
				Elf64_Ehdr *obj_ehdr = (Elf64_Ehdr *)ptr;

				if (check_elf_magic(obj_ehdr) == 0) {
					if (obj_ehdr->e_shoff + sizeof(Elf64_Shdr) > size) {
						// Fichier corrompu ou pas un ELF valide
						return 1;
					}

					Elf64_Shdr *section_header_ar = (Elf64_Shdr *)((char *)obj_ehdr + obj_ehdr->e_shoff);
			
					Elf64_Shdr *symtab = find_symtab(obj_ehdr, section_header_ar);
					if (!symtab) {
						return 1;
					}
					if (symtab->sh_offset + symtab->sh_size > size) {
						return 1;
					}

					Elf64_Sym *symbols = (Elf64_Sym *)((char *)obj_ehdr + symtab->sh_offset);

					nb_symbols = symtab->sh_size / sizeof(Elf64_Sym);

					if (symtab->sh_link >= obj_ehdr->e_shnum) {
						return 1;
					}
					Elf64_Shdr *strtab = &section_header_ar[symtab->sh_link];
			
					if (strtab->sh_offset + strtab->sh_size > size) {
						return 1;
					}
					char *strtab_ptr = (char *)obj_ehdr + strtab->sh_offset;

					for (int i = 0; i < nb_symbols; i++) {
						if (symbols[i].st_name == 0 || ELF64_ST_TYPE(symbols[i].st_info) == STT_FILE)
							continue;
						if (symbols[i].st_name >= strtab->sh_size)
							continue;
						char *symbol_name = strtab_ptr + symbols[i].st_name;

						if (symbols[i].st_value == 0x0) {
							printf("                 %c %s\n",
									get_symbol_type(&symbols[i]),
									symbol_name);
						} else {
							ft_print_hexa(symbols[i].st_value);
							ft_putstr_fd(" ", STDOUT_FILENO);
							ft_putchar_fd(get_symbol_type(&symbols[i]), STDOUT_FILENO);
							ft_putstr_fd(" ", STDOUT_FILENO);
							ft_putstr_fd(symbol_name, STDOUT_FILENO);
							ft_putchar_fd('\n', STDOUT_FILENO);
						}
					}
				}
			}
			ptr += size;
			if (size % 2 != 0 && ptr < end) {
				ptr++;
			}
		}
	}
	else if (check_elf_magic(ehdr) == 0) {
		Elf64_Shdr *symtab = NULL;
		if (!(symtab = find_symtab(ehdr, section_header)))
			return 1; // Todo: verifier si *symtab n'est pas NULL et return "sans symbol"

		Elf64_Sym * symbo = (Elf64_Sym *)(file_mem + symtab->sh_offset);

		nb_symbols = symtab->sh_size / sizeof(Elf64_Sym);

		Elf64_Shdr *strtab = &section_header[symtab->sh_link];

		for (int i = 0; i < nb_symbols; i++) {
			if (symbo[i].st_name == 0 || ELF64_ST_TYPE(symbo[i].st_info) == STT_FILE) continue;
			char *symbol_name = (char *)(file_mem + strtab->sh_offset + symbo[i].st_name);
			if (symbo[i].st_name < strtab->sh_size) {
				if (symbo[i].st_value == 0x0)
					printf("                 %c %s\n", get_symbol_type(&symbo[i]), symbol_name);
				else{
					// printf("%016lx %c %s\n", symbo[i].st_value, get_symbol_type(&symbo[i]), symbol_name);
					ft_print_hexa(symbo[i].st_value);
					ft_putstr_fd(" ", STDOUT_FILENO); 
					ft_putchar_fd(get_symbol_type(&symbo[i]), STDOUT_FILENO);
					ft_putstr_fd(" ", STDOUT_FILENO);
					ft_putstr_fd(symbol_name, STDOUT_FILENO);
					ft_putchar_fd('\n', STDOUT_FILENO);
				}
			}
		}
	}
	else {
		ft_putstr_fd("Format not supported.\n", STDOUT_FILENO);
		return 1;
	}

	// for (int i = 0; i < nb_symbols; i++) {

	// 	ft_print_hexa(symbol_tab[i].st_value);
	// 	ft_putstr_fd(" ", STDOUT_FILENO); 
	// 	ft_putchar_fd(symbol_tab[i].symbol_type, STDOUT_FILENO);
	// 	ft_putstr_fd(" ", STDOUT_FILENO);
	// 	ft_putstr_fd(symbol_tab[i].symbol_name, STDOUT_FILENO);
	// 	ft_putchar_fd('\n', STDOUT_FILENO);


	// }


	// Elf64_Shdr *symtab = find_symtab(ehdr, section_header);

	// Elf64_Sym * symbo = (Elf64_Sym *)(file_mem + symtab->sh_offset);


	// int nb_symbols = symtab->sh_size / sizeof(Elf64_Sym);

	// Elf64_Shdr *strtab = &section_header[symtab->sh_link];

	// t_symbols *symbol_tab;
	// symbol_tab = malloc(nb_symbols * sizeof(symbol_tab));

	// for (int i = 0; i < nb_symbols; i++) {
	// 	if (symbo[i].st_name == 0 || ELF64_ST_TYPE(symbo[i].st_info) == STT_FILE) continue;
	// 	char *symbol_name = (char *)(file_mem + strtab->sh_offset + symbo[i].st_name);
	// 	if (symbo[i].st_name < strtab->sh_size) {
	// 		symbol_tab[i].st_value = symbo[i].st_value;
	// 		symbol_tab[i].symbol_type = get_symbol_type(&symbo[i]);
	// 		symbol_tab[i].symbol_name = symbol_name;
	// 	}
	// }



	return 0;
}


// if (symbo[i].st_value == 0x0 && (ELF64_ST_TYPE(symbo[i].st_info) == STB_LOCAL))
// 	printf("                 %c %s\n", get_symbol_type(&symbo[i]), symbol_name);
// else{
// 	// printf("%016lx %c %s\n", symbo[i].st_value, get_symbol_type(&symbo[i]), symbol_name);
// 	ft_print_hexa(symbo[i].st_value);
// 	ft_putstr_fd(" ", STDOUT_FILENO); 
// 	ft_putchar_fd(get_symbol_type(&symbo[i]), STDOUT_FILENO);
// 	ft_putstr_fd(" ", STDOUT_FILENO);
// 	ft_putstr_fd(symbol_name, STDOUT_FILENO);
// 	ft_putchar_fd('\n', STDOUT_FILENO);
// }





/* 
******************** TO DO ************************
- gerer le cas ou le premier ou il n'y a pas de ar_hdr name
- Gerer les cas d'erreur adequate a ELF si necessaire
- Organiser mon code en quelque bloc pour que ca soit reutilisable
- quand il n'y pas de paramaetre il doit quand-meme faire un open() par defaut d'un fichier 'a.out'
- Faire tri
- voir aussi comment gerer l'affichage de chaque fichier .o .a .so ... selon le 'e_type' dans Ehdr

*/





// ft_putstr_fd("=== Informations ELF ===\n", STDOUT_FILENO);
// ft_putstr_fd("Type: ", STDOUT_FILENO);
// ft_putnbr_fd(ehdr->e_type, STDOUT_FILENO);  // 1 = Relocatable (ET_REL)
// ft_putchar_fd('\n', STDOUT_FILENO);
// ft_putstr_fd("Architecture:  ", STDOUT_FILENO);
// ft_putnbr_fd(ehdr->e_machine, STDOUT_FILENO );  // 62 = x86_64
// ft_putchar_fd('\n', STDOUT_FILENO);

// ft_putstr_fd("Nombre de sections:  ", STDOUT_FILENO);
// ft_putnbr_fd(ehdr->e_shnum, STDOUT_FILENO);
// ft_putchar_fd('\n', STDOUT_FILENO);

// ft_putstr_fd("Offset Table des sections:  ", STDOUT_FILENO);
// ft_putnbr_fd(ehdr->e_shoff, STDOUT_FILENO);
// ft_putchar_fd('\n', STDOUT_FILENO);

// ft_putstr_fd("Fin du programme.\n", STDOUT_FILENO);

// Elf64_Sym *esym = (Elf64_Sym *)file_mem;
// ft_putstr_fd("Symbol name ", STDOUT_FILENO);
// ft_putnbr_fd(esym->st_name,STDOUT_FILENO);
// ft_putchar_fd('\n', STDOUT_FILENO);

// ft_putstr_fd("Symbol info ", STDOUT_FILENO);
// ft_putnbr_fd(esym->st_shndx, STDOUT_FILENO);
// ft_putchar_fd('\n', STDOUT_FILENO);

// ft_putstr_fd("Section Table ", STDOUT_FILENO);

// ft_putstr_fd("*********************\n", STDOUT_FILENO);
// close(fd);
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


void	ft_print_hexa(unsigned int nb)
{
	int nb_num = ft_nb_numb(nb);
	
	for (int i = 0; i < (15 - nb_num); i++)
		ft_putchar_fd('0', STDOUT_FILENO);
	ft_hexadecimal(nb);
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
	if (ehdr->e_ident[0] != ELFMAG0 || ehdr->e_ident[1] != ELFMAG1 || ehdr->e_ident[2] != ELFMAG2 || ehdr->e_ident[3] != ELFMAG3) {
		ft_putstr_fd("Ce n'est pas un fichier ELF valide.\n", STDOUT_FILENO);
		return 1;
	}


	Elf64_Shdr *section_header = (Elf64_Shdr *)(file_mem + ehdr->e_shoff);
	Elf64_Shdr *symtab = NULL;

	for (int i = 0; i < ehdr->e_shnum; i++) {
		Elf64_Shdr *sy = (Elf64_Shdr *)((char *)section_header + (i * ehdr->e_shentsize));
		if (sy->sh_type == SHT_SYMTAB) {
			symtab = sy;
			break;
		}
	}

	// Todo: verifier si *symtab n'est pas NULL et return "sans symbol"


	Elf64_Sym * symbo = (Elf64_Sym *)(file_mem + symtab->sh_offset);


	int nb_symbols = symtab->sh_size / sizeof(Elf64_Sym);

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
	return 0;
}


/* 
******************** TO DO ************************
- Je dois gerer le cas pour un format ar "!<arch>\n"
- Organiser mon code en quelque bloc pour que ca soit reutilisable
- Faire tri



*/








// if (strncmp(file_mem, "!<arch>\n", 8) == 0) {
//     // C’est une archive, il faut la parcourir
// } else if (ehdr->e_ident[0] == ELFMAG0 && ehdr->e_ident[1] == ELFMAG1 && 
//            ehdr->e_ident[2] == ELFMAG2 && ehdr->e_ident[3] == ELFMAG3) {
//     // C’est un ELF, traite-le comme avant
// } else {
//     ft_putstr_fd("Format non supporté.\n", STDOUT_FILENO);
//     return 1;
// }


// char *ptr = file_mem + 8; // Après "!<arch>\n"
// while (ptr < file_mem + st.st_size) {
//     struct ar_hdr *hdr = (struct ar_hdr *)ptr;
//     size_t size = atoi(hdr->ar_size);
//     ptr += sizeof(struct ar_hdr); // Passe l’en-tête
//     Elf64_Ehdr *obj_ehdr = (Elf64_Ehdr *)ptr;
//     if (obj_ehdr->e_ident[0] == ELFMAG0 && ...) { // Vérifie que c’est un ELF
//         // Traite cet objet comme un ELF (ta logique existante)
//     }
//     ptr += size; // Saute au prochain objet
// }




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
#include "../include/ft_nm.h"

int main(int argc, char *argv[]) {

	const char	*filename;
	if (argc < 2)
		filename = "a.out";
	else
		filename = argv[1];

	int fd = open(filename, O_RDONLY);
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

	if (ft_strncmp(file_mem, ARMAG, SARMAG) == 0) 
	{
		char	*end = (char *)file_mem + st.st_size;
		if (handle_archive(file_mem, end, filename) == 1)
			return 0;
	}
	else if (check_elf_magic(ehdr) == 0) {
		Elf64_Shdr *symtab = NULL;
		if (!(symtab = find_symtab(ehdr, section_header)))
		{
			ft_nm_error(filename, "no symbols");
			return 1;
		}
		Elf64_Sym * symbo = (Elf64_Sym *)(file_mem + symtab->sh_offset);

		nb_symbols = symtab->sh_size / sizeof(Elf64_Sym);

		Elf64_Shdr *strtab = &section_header[symtab->sh_link];

		for (int i = 0; i < nb_symbols; i++) {
			if (symbo[i].st_name == 0 || ELF64_ST_TYPE(symbo[i].st_info) == STT_FILE) continue;
			char c = get_symbol_type(&symbo[i], section_header);
			char *symbol_name = (char *)(file_mem + strtab->sh_offset + symbo[i].st_name);
			if (symbo[i].st_value == 0) {
				ft_putstr_fd("                 ", STDOUT_FILENO);
				ft_putchar_fd(c, STDOUT_FILENO);
				ft_putstr_fd(" ", STDOUT_FILENO);
				ft_putstr_fd(symbol_name, STDOUT_FILENO);
				ft_putchar_fd('\n', STDOUT_FILENO);
			} else {
				ft_print_hexa(symbo[i].st_value);
				ft_putstr_fd(" ", STDOUT_FILENO);
				ft_putchar_fd(c, STDOUT_FILENO);
				ft_putstr_fd(" ", STDOUT_FILENO);
				ft_putstr_fd(symbol_name, STDOUT_FILENO);
				ft_putchar_fd('\n', STDOUT_FILENO);
			}
		}
	}
	else {
		ft_nm_error(filename, "file format not recognized");
		return 1;
	}
		
	return 0;
}





/* 
******************** TO DO ************************
- voir aussi comment gerer l'affichage de chaque fichier .o .a .so ... selon le 'e_type' dans Ehdr (
	surtout le cas des addresse en hexa decimal quand ils sont a zero, dans certains cas ils sont afficher ou pas
)
- Stocker les symbole dans la struct t_symbols (avant faire le tri)
- Faire Tri

*/


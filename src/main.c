#include "../include/ft_nm.h"


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
		ft_putstr_fd("Error fstat:", STDOUT_FILENO);
		return 1;
	}

	void *file_mem = mmap(NULL, st.st_size , PROT_READ, MAP_PRIVATE, fd, 0);

	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)file_mem;

	// Vérifier la signature ELF (doit commencer par 0x7F 'E' 'L' 'F')
	if (ehdr->e_ident[0] != 0x7f || ehdr->e_ident[1] != 'E' || ehdr->e_ident[2] != 'L' || ehdr->e_ident[3] != 'F') {
		ft_putstr_fd("Ce n'est pas un fichier ELF valide.\n", STDOUT_FILENO);
	}

	ft_putstr_fd("=== Informations ELF ===\n", STDOUT_FILENO);
	ft_putstr_fd("Type: ", STDOUT_FILENO);
	ft_putnbr_fd(ehdr->e_type, STDOUT_FILENO);  // 1 = Relocatable (ET_REL)
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_putstr_fd("Architecture:  ", STDOUT_FILENO);
	ft_putnbr_fd(ehdr->e_machine, STDOUT_FILENO );  // 62 = x86_64
	ft_putchar_fd('\n', STDOUT_FILENO);

	ft_putstr_fd("Nombre de sections:  ", STDOUT_FILENO);
	ft_putnbr_fd(ehdr->e_shnum, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);

	ft_putstr_fd("Offset Table des sections:  ", STDOUT_FILENO);
	ft_putnbr_fd(ehdr->e_shoff, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);

	ft_putstr_fd("Fin du programme.\n", STDOUT_FILENO);

	Elf64_Sym *esym = (Elf64_Sym *)file_mem;
	ft_putstr_fd("Symbol name ", STDOUT_FILENO);
	ft_putnbr_fd(esym->st_name,STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);

	ft_putstr_fd("Symbol info ", STDOUT_FILENO);
	ft_putnbr_fd(esym->st_shndx, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);


	ft_putstr_fd("*********************\n", STDOUT_FILENO);
	close(fd);
	return 0;
}


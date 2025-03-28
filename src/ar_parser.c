#include "../include/ft_nm.h"

int	handle_archive(void *file_mem, char *end, const char *filename) {
	char	*ptr = (char *)file_mem + SARMAG;
	int		nb_symbols = 0;

	while (1) {
		if (ptr + sizeof(struct ar_hdr) > end)
			break;

		struct ar_hdr *hdr = (struct ar_hdr *)ptr;
		char *ar_name = formated_ar_name(hdr->ar_name);
		if (!ar_name) {
			ft_nm_error(filename, "memory allocation failed");
			return 1;
		}

		int len = ft_strlen(ar_name);
		if (len > 0 && ar_name[len - 1] == 'o') {
			ft_putstr_fd(ar_name, STDOUT_FILENO);
			ft_putchar_fd(':', STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		free(ar_name);

		ptr += sizeof(struct ar_hdr);
		size_t size = ft_atoi(hdr->ar_size);

		if (ptr + size > end)
			break;

		if (size >= sizeof(Elf64_Ehdr)) {
			Elf64_Ehdr *obj_ehdr = (Elf64_Ehdr *)ptr;

			if (check_elf_magic(obj_ehdr) == 0) {
				if (obj_ehdr->e_shoff + sizeof(Elf64_Shdr) > size) {
					ft_nm_error(filename, "file format not recognized");
					return 1;
				}

				Elf64_Shdr *section_header_ar = (Elf64_Shdr *)((char *)obj_ehdr + obj_ehdr->e_shoff);
				Elf64_Shdr *symtab = find_symtab(obj_ehdr, section_header_ar);

				if (!symtab) {
					ft_nm_error(filename, "no symbols");
					return 1;
				}

				if (symtab->sh_offset + symtab->sh_size > size) {
					return 1;
				}

				Elf64_Sym *symbols = (Elf64_Sym *)((char *)obj_ehdr + symtab->sh_offset);

				nb_symbols = symtab->sh_size / sizeof(Elf64_Sym);

				if (symtab->sh_link >= obj_ehdr->e_shnum) {
					ft_nm_error(filename, "File truncated (invalid sh_link)");
					return 1;
				}

				Elf64_Shdr *strtab = &section_header_ar[symtab->sh_link];
		
				if (strtab->sh_offset + strtab->sh_size > size) {
					ft_nm_error(filename, "File truncated");
					return 1;
				}
				char *strtab_ptr = (char *)obj_ehdr + strtab->sh_offset;

				for (int i = 0; i < nb_symbols; i++) {
					if (symbols[i].st_name == 0 || ELF64_ST_TYPE(symbols[i].st_info) == STT_FILE)
						continue;
					if (symbols[i].st_name >= strtab->sh_size)
						continue;

					char *symbol_name = strtab_ptr + symbols[i].st_name;
					char c = get_symbol_type(&symbols[i], section_header_ar);
					uint64_t displayed_addr = symbols[i].st_value;

					if (obj_ehdr->e_type == ET_REL && symbols[i].st_shndx < obj_ehdr->e_shnum) {
						Elf64_Shdr *sect = &section_header_ar[symbols[i].st_shndx];
						displayed_addr = displayed_addr - sect->sh_addr;
					}

					if (displayed_addr == 0) {
						ft_putstr_fd("                 ", STDOUT_FILENO);
						ft_putchar_fd(c, STDOUT_FILENO);
						ft_putstr_fd(" ", STDOUT_FILENO);
						ft_putstr_fd(symbol_name, STDOUT_FILENO);
						ft_putchar_fd('\n', STDOUT_FILENO);
					} else {
						ft_print_hexa(symbols[i].st_value);
						ft_putstr_fd(" ", STDOUT_FILENO);
						ft_putchar_fd(c, STDOUT_FILENO);
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
	return 0;
}
#include "../include/ft_nm.h"


static int	process_file(void *file_mem, struct stat *st, char *filename)
{
	Elf64_Ehdr	*ehdr;

	ehdr = (Elf64_Ehdr *)file_mem;
	if (ft_strncmp(file_mem, ARMAG, SARMAG) == 0)
	{
		if (handle_archive(file_mem, (char *)file_mem + st->st_size, filename) == 1)
			return (1);
	}
	else if (check_elf_magic(ehdr) == 0)
	{
		if (handle_elf_file(file_mem, filename) == 1)
			return (1);
	}
	else
	{
		ft_nm_error(filename, "file format not recognized");
		return (1);
	}
	return (0);
}


int	main(int argc, char *argv[])
{
	const char	*filename;
	int			fd;
	struct stat	st;
	void		*file_mem;
	int			ret;

	filename = (argc < 2) ? "a.out" : argv[1];
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	if (fstat(fd, &st) < 0)
	{
		perror("fstat");
		close(fd);
		return (1);
	}
	file_mem = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (file_mem == MAP_FAILED)
	{
		perror("mmap");
		close(fd);
		return (1);
	}
	ret = process_file(file_mem, &st, (char *)filename);
	munmap(file_mem, st.st_size);
	close(fd);
	return (ret);
}

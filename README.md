# ft_nm

`ft_nm` is a custom implementation of the Unix `nm` command, developed in C. It is a **post-Common Core project at 42 Paris**. 
This program displays the symbol table of object files, executables, and static libraries, focusing on ELF64 file structure analysis and memory mapping.

## Features

- Supports **ELF64** binaries.
- Supports **Ar** archives (static libraries `.a`).
- Handles symbol sorting (alphanumeric order).
- Displays symbol addresses, types (e.g., T, U, A), and names.
- Efficient memory management using `mmap`.

## Requirements

- GCC or Clang
- Make
- Standard C libraries

## Installation

Clone the repository and compile the project using the Makefile:

    make

This will compile the `libft` dependency and generate the `ft_nm` executable.

## Usage

    ./ft_nm [file...]

### Examples

Run on a specific binary:

    ./ft_nm /bin/ls

Run on a static library:

    ./ft_nm libft/libft.a

Run without arguments (defaults to `a.out`):

    ./ft_nm

## Build Commands

- `make`       : Compiles the project.
- `make clean` : Removes object files.
- `make fclean`: Removes object files and the executable.
- `make re`    : Recompiles the project from scratch.

## Project Structure

- `src/`     : Source code files.
- `include/` : Header files.
- `libft/`   : Libft submodule.

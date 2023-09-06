# File Organizer (fso)

**File Organizer (fso)** is a custom Linux command-line program designed to help you organize the contents of a directory by categorizing and moving/copying files into different folders based on their file types. This program is particularly useful for keeping your file system tidy and well-structured.

## Usage

To use File Organizer, follow these steps:

1. **Compilation**: First, make sure you have `g++` installed on your system. Then, use the provided Makefile to compile the code by running the following command in your terminal:

```bash
make
```

2. **Execution**: Once the code is compiled, you can execute it using the following command:

```bash
./fso [OPTIONS] DIRECTORY
```

   - `[OPTIONS]` can be one or more of the following:
     - `-h` or `--help`: Display help information.
     - `-m`: Move the files to the organized directory (default is to copy).
     - `-t` or `--tree DIR`: Print the contents of the specified directory in a tree format.

   - `DIRECTORY` is the path to the directory you want to organize.

## Example Usages

- To organize the files in the current directory by copying them into categorized folders:

```bash
./fso .
```

- To organize the files in a specific directory by moving them into categorized folders:

```bash
./fso -m /path/to/directory
```

- To print the contents of a directory in a tree format:

```bash
./fso -t /path/to/directory
```

## Available Categories

File Organizer categorizes files into the following categories:

- **Media**: mp4, mkv, mov
- **Archives**: zip, tar, gz, 7z, rar, iso, xz
- **Documents**: docs, doc, pdf, xlsx, xls, odt, ods, odp, odg, odf, txt, ps, tex
- **App**: exe, pkg, dmg, deb

You can customize the categories and associated file extensions by modifying the `dataMap` and `dMap` at the beginning of the code.

## Options

- `-h` or `--help`: Displays this help message, providing information on how to use the program.

- `-m`: By default, files are copied to the organized folders. Use this option to move files instead of copying them.

- `-t` or `--tree DIR`: Prints the contents of the specified directory in a tree-like structure.

## Examples

- To organize files in the current directory by moving them:

```bash
./fso -m .
```

- To print the tree structure of a specific directory:

```bash
./fso -t /path/to/directory
```

## Notes

- The program will create an "Organized Files" directory within the specified directory to store organized files.

- Existing files with the same name in the destination folder will not be overwritten. You can customize this behavior in the `moveFileToOrganizedDirectory` function if needed.

- If a file does not match any of the predefined categories, it will not be moved or copied.

## Cleaning Up

To remove the compiled executable and object files, you can run:

```bash
make clean
```

## License

This program is open-source and released under the [MIT License](LICENSE). Feel free to use, modify, and distribute it as per the terms of the license. If you have any questions or encounter issues, please open an issue on GitHub or contact the developer.

Enjoy organizing your files with File Organizer (fso)!

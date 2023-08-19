#include <iostream>
#include <cstdlib>
#include <cstring>
#include <dirent.h> // For directory operations
#include <sys/stat.h> // For checking directory existence
#include <map>
#include <vector>

// Define a global map with string keys and vector values
std::map<std::string, std::vector<std::string>> dataMap = {
    {"media", {"mp4", "mkv"}},
    {"archives", {"zip", "tar", "gz", "7z", "rar", "ar", "iso", "xz"}},
    {"documents", {"docs", "doc", "pdf", "xlsx", "xls", "odt", "ods", "odp", "odg", "odf", "txt", "ps", "tex"}},
    {"app", {"exe", "pkg", "dmg", "deb"}}
};


void printHelp() {
    std::cout << "Usage: fso [OPTION] DIRECTORY\n"
              << "Custom Linux command to organise the contents of a directory.\n"
              << "Options:\n"
              << "  -h, --help          Display this help and exit\n"
              << "  -p, --print DIR     Print the contents of the specified directory\n"
              << "  -t, --tree DIR      Print the contents of the directory in a tree format\n";
}

void printDirectoryContents(const char* directory) {
    DIR* dir = opendir(directory);
    if (dir == nullptr) {
        std::cerr << "Error opening directory: " << directory << "\n";
        return;
    }

    dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (std::strcmp(entry->d_name, ".") != 0 && std::strcmp(entry->d_name, "..") != 0) {
            std::cout << entry->d_name << "\n";
        }
    }

    closedir(dir);
}

void organiseDirectoryContents(const char* directory) {
    DIR* dir = opendir(directory);
    if (dir == nullptr) {
        std::cerr << "Error opening directory: " << directory << "\n";
        return;
    }

    // 1. Create a directory organised_files inside the directory provided
    // 2. Check which category do each file belong to
    // 3. Copy / Move files to the organised_files directory inside any of the category folders

    closedir(dir);
}

bool directoryExists(const char* path) {
    struct stat fileInfo;
    return (stat(path, &fileInfo) == 0 && S_ISDIR(fileInfo.st_mode));
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Missing arguments. Use -h or --help for help.\n";
        return 1;
    }

    if (std::strcmp(argv[1], "-h") == 0 || std::strcmp(argv[1], "--help") == 0) {
        printHelp();
        return 0;
    }

    if (std::strcmp(argv[1], "-p") == 0 || std::strcmp(argv[1], "--print") == 0) {
        if (argc < 3) {
            std::cerr << "Missing directory argument for -p or --print option.\n";
            return 1;
        }
        const char* directory = argv[2];
        if (!directoryExists(directory)) {
            std::cerr << "Invalid or non-existent directory: " << directory << "\n";
            return 1;
        }
        printDirectoryContents(directory);
        return 0;
    }

    if (std::strcmp(argv[1], "-t") == 0 || std::strcmp(argv[1], "--tree") == 0) {
        if (argc < 3) {
            std::cerr << "Missing directory argument for -p or --print option.\n";
            return 1;
        }
        const char* directory = argv[2];
        if (!directoryExists(directory)) {
            std::cerr << "Invalid or non-existent directory: " << directory << "\n";
            return 1;
        }
        // Do something
        return 0;
    }

    const char* directory = argv[1];

    // Perform processing based on the directory
    if (std::strcmp(directory, ".") == 0) {
        // Handle current directory
        std::cout << "Processing current directory.\n";
        // Implement your processing logic here
    } else {
        if (directoryExists(directory)) {
            // Handle the specified directory
            std::cout << "Processing directory: " << directory << "\n";
            // Implement your processing logic here
        } else {
            std::cerr << "Invalid or non-existent directory: " << directory << "\n";
            return 1;
        }
    }

    return 0;
}



#if 0
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <dirent.h> // For directory operations
#include <unistd.h> // For getopt

void printHelp() {
    std::cout << "Usage: fs [OPTION] DIRECTORY\n"
              << "Custom command to organise files a directory.\n"
              << "Options:\n"
              << "  -h, --help         Display this help and exit\n"
              << "  -p, --print DIR    Print the contents of the specified directory\n";
}

void printDirectoryContents(const char* directory) {
    DIR* dir = opendir(directory);
    if (dir == nullptr) {
        std::cerr << "Error opening directory: " << directory << "\n";
        return;
    }

    dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (std::strcmp(entry->d_name, ".") != 0 && std::strcmp(entry->d_name, "..") != 0) {
            std::cout << entry->d_name << "\n";
        }
    }

    closedir(dir);
}

int main(int argc, char* argv[]) {
    int opt;
    const char* directory = nullptr;
    static struct option long_options[] = {
        {"help", no_argument, nullptr, 'h'},
        {"print", required_argument, nullptr, 'p'},
        {nullptr, 0, nullptr, 0}
    };

    while ((opt = getopt_long(argc, argv, "hp:", long_options, nullptr)) != -1) {
        switch (opt) {
            case 'h':
                printHelp();
                return 0;
            case 'p':
                directory = optarg;
                printDirectoryContents(directory);
                return 0;
            default:
                std::cerr << "Invalid option. Use -h or --help for help.\n";
                return 1;
        }
    }

    std::cout << optind << " " << argc << std::endl;
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }

    if (optind < argc) {
        directory = argv[optind];
    }

    if (directory == nullptr) {
        std::cerr << "Missing directory argument. Use -h or --help for help.\n";
        return 1;
    }

    // Perform processing based on the directory
    if (std::strcmp(directory, ".") == 0) {
        // Handle current directory
        std::cout << "Processing current directory.\n";
        // Implement your processing logic here
    } else {
        // Handle the specified directory
        std::cout << "Processing directory: " << directory << "\n";
        // Implement your processing logic here
    }

    return 0;
}
#endif
#include <iostream>
#include <sys/stat.h> // For checking directory existence
#include <map>
#include <vector>
#include <filesystem>

const std::string ResetColor = "\033[0m";
const std::string RedColor = "\033[31m";
const std::string GreenColor = "\033[32m";
const std::string BlueColor = "\033[34m";

// Define a global map with string keys and vector values
std::map<std::string, std::vector<std::string>> dataMap = {
    {"Media", {"mp4", "mkv"}},
    {"Archives", {"zip", "tar", "gz", "7z", "rar", "ar", "iso", "xz"}},
    {"Documents", {"docs", "doc", "pdf", "xlsx", "xls", "odt", "ods", "odp", "odg", "odf", "txt", "ps", "tex"}},
    {"App", {"exe", "pkg", "dmg", "deb"}}
};

std::map<std::string, std::string> dMap = {
    {"exe",  "App"},
    {"pkg",  "App"},
    {"dmg",  "App"},
    {"deb",  "App"},
    {"zip",  "Archives"},
    {"tar",  "Archives"},
    {"gz",   "Archives"},
    {"7z",   "Archives"},
    {"rar",  "Archives"},
    {"iso",  "Archives"},
    {"docs", "Documents"},
    {"doc",  "Documents"},
    {"pdf",  "Documents"},
    {"xlsx", "Documents"},
    {"txt",  "Documents"},
    {"mp4",  "Media"},
    {"mkv",  "Media"},
    {"mov",  "Media"},
    
};

// Global variable check if we should move the files or just copy
bool moveFiles = false;

void printHelp() {
    std::cout << "Usage: fso [OPTION] DIRECTORY\n"
              << "Custom Linux command to organise the contents of a directory.\n"
              << "Options:\n"
              << "  -h, --help          Display this help and exit\n"
              << "  -m,                 Move the files to the organised directory. Default is copy.\n"
              << "  -t, --tree DIR      Print the contents of the directory in a tree format\n";
}

bool directoryExists(const std::string& path) {
    return std::filesystem::is_directory(path);
}

bool createDirectory(const std::string& path, const std::string& dir) {
    std::string directory = path + dir;
    if (std::filesystem::create_directory(directory)) {
        std::cout << "Created directory: " << directory << "\n";
    } else {
        std::cerr << "Failed to create directory: " << directory << "\n";
        return false;
    }

    return true;
}

bool createOrganisedFilesDirectory(const std::string& path) {
    return createDirectory(path, "/Organised Files");
}

void copyFileToOrganisedDirectory(const std::string& source, const std::string& destination) {
    if (std::filesystem::exists(destination)) return;

    std::filesystem::copy(source, destination);
    std::cout << "Copied file: " << source << " to " << destination << "\n";
}

void moveFileToOrganisedDirectory(const std::string& source, const std::string& destination) {
    if (std::filesystem::exists(destination)) return;   // Doing nothing if file already exists. The file can be deleted
    // Update the function to delete the files, if needed.

    try {
        std::filesystem::rename(source, destination);
        std::cout << "Moved file: " << source << " to " << destination << "\n";
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error moving file: " << e.what() << "\n";
    }
}

void organiseDirectoryContents(const std::string& directory) {
    if (!directoryExists(directory)) {
        std::cerr << "No such directory exists\n";
        return;
    }

    // 1. Create a directory "Organised Files" inside the directory provided
    if (!std::filesystem::exists(directory + "/Organised Files")) {
        if (!createOrganisedFilesDirectory(directory)) {
            return;
        }
    }

    // 2. Check which category do each file belong to
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) {

            // 3. Copy / Move files to the "Organised Files" directory inside any of the category folders
            std::string extension = entry.path().extension().string();
            if (!extension.empty()) {
                // Remove the leading dot
                if (extension.front() == '.') {
                    extension = extension.substr(1);
                }

                if (dMap.find(extension) != dMap.end()) {
                    std::string orgFolder = dMap[extension];
                    if (!std::filesystem::exists(directory + "/Organised Files/" + orgFolder)) {
                        if (!createDirectory(directory, "/Organised Files/" + orgFolder)) {
                            return;
                        }
                    }

                    std::string source = entry.path().string();
                    std::string destination = directory + "/Organised Files/" + orgFolder + "/" + entry.path().filename().string();

                    if (moveFiles) {
                        moveFileToOrganisedDirectory(source, destination);
                    } else {
                        copyFileToOrganisedDirectory(source, destination);
                    }
                }
            }
        }
    }
    
    
}

void printDirectoryTree(const std::string& path, int level = 0) {
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        // Indent based on level for a tree like structure
        for (int i = 0; i < level; i++) {
            std::cout << "  ";
        }

        if (std::filesystem::is_directory(entry)) {
            std::string directory = entry.path().filename().string();
            std::cout << "└── " << GreenColor << directory << ResetColor << "\n";
            printDirectoryTree(path + "/" + directory, level + 1); // Recursive call for subdirectories
        } else {
            std::cout << "├── " << entry.path().filename().string() << "\n";
        }
    }
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Missing arguments. Use -h or --help for help.\n";
        return 1;
    }

    std::string options = argv[1];

    if (options.compare("-h") == 0 || options.compare("--help") == 0) {
        printHelp();
        return 0;
    }

    if (options.compare("-m") == 0) {
        moveFiles = true;
    }

    if (options.compare("-t") == 0 || options.compare("--tree") == 0) {
        if (argc < 3) {
            std::cerr << "Missing directory argument for -p or --print option.\n";
            return 1;
        }
        std::string directory = argv[2];
        if (!directoryExists(directory)) {
            std::cerr << "Invalid or non-existent directory: " << directory << "\n";
            return 1;
        }
        printDirectoryTree(directory);
        return 0;
    }

    std::string directory;
    if (moveFiles) {
        directory = argv[2];
    } else {
        directory = argv[1];
    }

    // Perform processing based on the directory
    if (directory.compare(".") == 0) {
        // Handle current directory
        std::cout << "Processing current directory.\n";
        organiseDirectoryContents(directory);
    } else {
        if (directoryExists(directory)) {
            // Handle the specified directory
            std::cout << "Processing directory: " << directory << "\n";
            organiseDirectoryContents(directory);
        } else {
            std::cerr << "Invalid or non-existent directory: " << directory << "\n";
            return 1;
        }
    }

    return 0;
} // main
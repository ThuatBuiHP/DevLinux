#include <stdio.h>      // For printf, fprintf, perror
#include <sys/types.h>  // For system data types
#include <sys/stat.h>   // For struct stat, lstat(), and file type macros
#include <unistd.h>     // For standard symbolic constants
#include <time.h>       // For ctime()
#include <stdlib.h>     // For exit()

int main(int argc, char *argv[]) {
    // 1.1 & 1.2: Validate command line arguments
    // We expect exactly 2 arguments: the program name and the file path.
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    const char *path = argv[1];
    struct stat file_stat;

    // 1.3: Use lstat to get file metadata
    // lstat is used instead of stat so that if the path is a symbolic link,
    // we get info about the link itself, not the file it points to.
    if (lstat(path, &file_stat) == -1) {
        // perror prints a descriptive error message based on the global 'errno'
        perror("Error getting file stats");
        return 1;
    }

    // 1.4: Prepare data for display

    // Determine File Type
    const char *type_str = "Unknown";
    if (S_ISREG(file_stat.st_mode)) {
        type_str = "Regular File";
    } else if (S_ISDIR(file_stat.st_mode)) {
        type_str = "Directory";
    } else if (S_ISLNK(file_stat.st_mode)) {
        type_str = "Symbolic Link";
    }

    // Format the time
    // ctime converts a time_t value to a human-readable string.
    // Note: ctime string typically ends with a newline character automatically.
    char *time_str = ctime(&file_stat.st_mtime);

    // Display the results
    printf("File Path:     %s\n", path);
    printf("File Type:     %s\n", type_str);
    // Cast st_size to long long to ensure it prints correctly on 32-bit and 64-bit systems
    printf("Size:          %lld bytes\n", (long long)file_stat.st_size); 
    printf("Last Modified: %s", time_str); // time_str includes a \n at the end

    return 0;
}
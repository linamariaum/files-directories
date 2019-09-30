#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void getPermissions(struct stat myStat);

int main(int argc, char **argv)
{
    struct stat fileStat;

    if (argc != 2 && strcmp(argv[2], "--permissions") != 0)
        return 1;

    if (argc == 3 && strcmp(argv[2], "--permissions") == 0)
    {
        if (stat(argv[1], &fileStat) < 0)
            return 1;
        getPermissions(fileStat);
        return 0;
    }

    if (stat(argv[1], &fileStat) < 0)
        return 1;

    printf("Información de %s\n", argv[1]);
    printf("---------------------------\n");
    printf("File Size: \t\t%ld bytes\n", (long)fileStat.st_size);
    printf("Number of Links: \t%ld\n", (long)fileStat.st_nlink);
    printf("File inode: \t\t%ld\n", (long)fileStat.st_ino);
    printf("File Permissions: \t");
    getPermissions(fileStat);
    printf("\n\n");
    printf("Last access: \t%ld\n", (long)fileStat.st_atime);
    printf("Last modification: \t%ld\n", (long)fileStat.st_ctime);
    printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");

    return 0;
}

void getPermissions(struct stat myStat)
{
    printf((S_ISDIR(myStat.st_mode)) ? "d" : "-");
    printf((myStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((myStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((myStat.st_mode & S_IXUSR) ? "x" : "-");
    printf((myStat.st_mode & S_IRGRP) ? "r" : "-");
    printf((myStat.st_mode & S_IWGRP) ? "w" : "-");
    printf((myStat.st_mode & S_IXGRP) ? "x" : "-");
    printf((myStat.st_mode & S_IROTH) ? "r" : "-");
    printf((myStat.st_mode & S_IWOTH) ? "w" : "-");
    printf((myStat.st_mode & S_IXOTH) ? "x" : "-");
}
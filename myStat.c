#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

char *convertTime(time_t time);
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

    printf("Information for: %s\n", argv[1]);
    printf("---------------------------\n");
    printf("File Size: \t\t\t\t%ld bytes\n", (long)fileStat.st_size);
    printf("Number of Links: \t\t\t%ld\n", (long)fileStat.st_nlink);
    printf("File inode: \t\t\t\t%ld\n", (long)fileStat.st_ino);
    printf("Number of 512B blocks allocated: \t%ld\n", (long)fileStat.st_blocks);
    printf("Blocksize for file system I/O: \t\t%ld\n", (long)fileStat.st_blksize);
    printf("File Permissions: \t\t\t");
    getPermissions(fileStat);
    printf("\n\n");
    printf("Last access: \t\t\t\t%s", convertTime(fileStat.st_atime));
    printf("Last modification: \t\t\t%s", convertTime(fileStat.st_atime));
    printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");

    return 0;
}

char *convertTime(time_t time)
{
    char *c_time_string;
    c_time_string = ctime(&time);
    return c_time_string;
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
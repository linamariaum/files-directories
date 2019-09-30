#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include <pwd.h>

#define PATH_MAX 4096
char *getUserName();
void getPermissions(struct stat myStat);

int main(int argc, char *argv[])
{
    DIR *myDir;
    char prop[3];
    char cwd[PATH_MAX];
    struct stat myStat;
    struct dirent *myFile;
    char myFilePath[PATH_MAX];

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-l") == 0)
        {
            strcpy(prop, argv[i]);
        }
        else
        {
            strcpy(cwd, argv[i]);
        }
    }

    if (strcmp(cwd, "") == 0)
    {
        getcwd(cwd, sizeof(cwd));
    }

    myDir = opendir(cwd);
    while ((myFile = readdir(myDir)) != NULL)
    {
        sprintf(myFilePath, "%s/%s", cwd, myFile->d_name);
        stat(myFilePath, &myStat);
        getPermissions(myStat);
        printf("%ld\t %s\t %s\t %s\n", (long)myStat.st_size, getUserName(myStat.st_uid), getUserName(myStat.st_gid), myFile->d_name);
    }
    closedir(myDir);

    return 0;
}

char *getUserName(uid_t uid)
{
    struct passwd *pw = getpwuid(uid);
    if (pw)
    {
        return pw->pw_name;
    }
    return "unnamed";
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
    printf("\t");
}
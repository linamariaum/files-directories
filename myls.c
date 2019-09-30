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
    if (myDir == NULL)
    {
        printf("No fue posible abrir el directorio '%s'\n", cwd);
        return 1;
    }

    if (strcmp(prop, "-l") == 0)
    {
        while ((myFile = readdir(myDir)) != NULL)
        {
            sprintf(myFilePath, "%s/%s", cwd, myFile->d_name);
            stat(myFilePath, &myStat);
            char file[PATH_MAX];

            sprintf(file, "./myStat.out %s --permissions", myFilePath);
            system(&file);
            printf("\t");
            printf("%ld\t %s\t %s\t %s\n", (long)myStat.st_size, getUserName(myStat.st_uid), getUserName(myStat.st_gid), myFile->d_name);
        }
    }
    else
    {
        while ((myFile = readdir(myDir)) != NULL)
        {
            printf("%s\t", myFile->d_name);
        }
        printf("\n");
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
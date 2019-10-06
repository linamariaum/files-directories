#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PATH_MAX 4096
char *getUserName();
int printRecursive(char cwd[PATH_MAX], int n);
void printNTabs(int n);

int main(int argc, char *argv[])
{
    char prop[3];
    char cwd[PATH_MAX];

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

    printRecursive(cwd, 0);

    return 0;
}

int printRecursive(char cwd[PATH_MAX], int n)
{
    DIR *myDir;
    struct stat myStat;
    struct dirent *myFile;
    char myFilePath[PATH_MAX];

    myDir = opendir(cwd);
    if (myDir == NULL)
    {
        printf("No fue posible abrir el directorio '%s'\n", cwd);
        return 1;
    }
    while ((myFile = readdir(myDir)) != NULL)
    {
        sprintf(myFilePath, "%s/%s", cwd, myFile->d_name);
        stat(myFilePath, &myStat);
        printNTabs(n);
        printf("- %s\n", myFile->d_name);
        if (S_ISDIR(myStat.st_mode) && !(strcmp(myFile->d_name, ".") == 0 || strcmp(myFile->d_name, "..") == 0))
        {
            printRecursive(myFilePath, n + 1);
        }
    }
    closedir(myDir);
    return 0;
}

void printNTabs(int n)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("\t");
    }
}
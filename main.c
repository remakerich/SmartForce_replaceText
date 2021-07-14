#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#define BUFF 1000

void greeting();
int replaceFn(char *str, char *oldtext, char *newtext);
void genLog(char *userdir, int i, char *oldtext, char *newtext, char *filename);

int main()
{
    greeting();
    char userdir[BUFF];
    char oldtext[BUFF], newtext[BUFF];
    char path[BUFF];
    char line[BUFF];
    int a, b = 0;
    struct dirent *f;
    FILE *fOrig, *fRepl;
    DIR *d;

    do
    {
        fgets(userdir, BUFF, stdin);
        userdir[strlen(userdir) - 1] = '/';
        d = opendir(userdir);
        if(d == NULL || strlen(userdir) == 1)
        {printf("Invalid directory, try again...\n\n");}

    }while(d == NULL || strlen(userdir) == 1);

    do
    {
        printf("Enter text to replace:\n");
        fgets(oldtext, BUFF, stdin);
        oldtext[strlen(oldtext) - 1] = 0;

        printf("Replace with:\n");
        fgets(newtext, BUFF, stdin);
        newtext[strlen(newtext) - 1] = 0;
        if (!strcmp(oldtext, newtext))
        {printf("Same values entered! Try again...\n\n");}

    }while(!strcmp(oldtext, newtext));

    printf("\n\nSearching...\n");    
    while (f = readdir(d))
    {
        char *filename = f -> d_name;
        printf("\n%s", filename);

        if(strstr(filename, ".txt"))
        {

            strcat(strcpy(path, userdir), filename);
            fOrig = fopen(path, "r");
            fRepl = fopen("replica.tmp", "w");
            int i = 1;
            a = 0;

            while(fgets(line, BUFF, fOrig))
            {
                if(replaceFn(line, oldtext, newtext) == 1)
                {
                    genLog(userdir, i, oldtext, newtext, filename);
                    a = 1;
                }
                fputs(line, fRepl);
                i++;
            }
            fclose(fOrig);
            fclose(fRepl);
            remove(path);
            rename("replica.tmp", path);
            if(a == 1){printf("                  - Match found!"); b = 1;}; 
        }
    }
    if(b != 1){printf("\n...\nNo match found...\n\n\n");}
    else{printf("\n...\nChanges applied, log file:\n%slog.tmp\n\n\n", userdir);}

    closedir(d);
    printf("Press any key to exit..");
    getchar();  
    return 0;
}

int replaceFn(char *str, char *oldtext, char *newtext)
{
    char *pos, temp[BUFF];
    int index = 0;
    int result = 0;

    while (pos = strstr(str, oldtext))
    {
        strcpy(temp, str);
        index = pos - str;
        str[index] = '\0';
        strcat(str, newtext);
        strcat(str, temp + index + strlen(oldtext));
        result = 1;
    }
    return result;
}

void genLog(char *userdir, int i, char *oldtext, char *newtext, char *filename)
{
    time_t t;
    time(&t);
    FILE *fLog;
    char path[BUFF];

    strcat(strcpy(path, userdir), "log.tmp");
    fLog = fopen(path, "a");
    fputs(ctime(&t), fLog);
    strcat(strcpy(path, userdir), filename);
    fputs(path, fLog);
    fprintf(fLog, "\nLine #%d: '%s' -> '%s'\n\n", i, oldtext, newtext);
    fclose(fLog);
}

void greeting()
{
     printf("\nChange text in all (.txt) files of directory.\n");
     printf("Enter directory:\n");
}
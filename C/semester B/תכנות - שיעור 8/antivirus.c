char *read_file(char *fname, int *size, int isQuick);
int contains_virus(char *file_buf, int file_size, char *virus_buf, int virus_size);
char **get_sorted_file_names(char *dir_path, int *num_of_files);

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define ARGC_AMOUNT 3
#define ARGV_DIR 1
#define ARGV_VIRUS 2
#define MAX_LEN 512
#define TWENTY_PERCENT 5

enum ScanMode {FULL = 0, FIRST_20 = 1, LAST_20 = 2 };

/*
Reads the content of a file into a buffer.
input: fname: The path to the file.
       size: A pointer to an integer that will store the size of the read content.
       isQuick: An integer indicating the scan mode (FULL, FIRST_20, or LAST_20).
output: A pointer to the allocated buffer containing the file content, or NULL if an error occurred.
*/
char *read_file(char *fname, int *size, int isQuick) // im sending the size 0 and changing it to the REAL size!!!
{
    FILE *f = fopen(fname, "rb");
    if (!f)
    {
        printf("Cannot open file %s\n", fname);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    int fullSize = ftell(f);

    if (isQuick == FULL)
    {
        *size = fullSize;
        fseek(f, 0, SEEK_SET);
    }
    else if (isQuick == FIRST_20)
    {
        *size = (fullSize + TWENTY_PERCENT - 1) / TWENTY_PERCENT;
        fseek(f, 0, SEEK_SET);
    }
    else if (isQuick == LAST_20)
    {
        *size = fullSize / TWENTY_PERCENT;
        fseek(f, fullSize - *size, SEEK_SET);
    }

    char *buffer = (char *)malloc(*size);
    if (!buffer)
    {
        printf("Memory allocation failed\n");
        fclose(f);
        return NULL;
    }

    fread(buffer, 1, *size, f);
    fclose(f);
    return buffer;
}

/*
Checks if a file buffer contains a virus signature.
input: file_buf: A pointer to the buffer containing the file content. 
       file_size: The size of the file content. virus_buf: 
       A pointer to the buffer containing the virus signature. 
       virus_size: The size of the virus signature.
output: 1 if the virus signature is found, 0 otherwise.
*/
int contains_virus(char *file_buf, int file_size, char *virus_buf, int virus_size)
{
    if (file_size < virus_size)
        return 0;

    for (int i = 0; i <= file_size - virus_size; i++)
    {
        int found = 1;
        for (int j = 0; j < virus_size; j++)
        {
            if (file_buf[i + j] != virus_buf[j])
            {
                found = 0;
                break;
            }
        }
        if (found)
            return 1;
    }
    return 0;
}

/*
Retrieves and sorts the names of files in a given directory.
input: dir_path: The path to the directory. num_of_files: A pointer to an integer that will store the number of files founoutput: A pointer to an array of strings (char**) containing the sorted file names, or NULL if an error occurred.
*/
char **get_sorted_file_names(char *dir_path, int *num_of_files)
{
    DIR *d = opendir(dir_path);
    struct dirent *dir;
    char **names = NULL;
    int count = 0;
    
    if (!d)
    {
        printf("error openning dir!\n");
        return NULL;
    }
    
    while ((dir = readdir(d)) != NULL)
    {
        if (strcmp(dir->d_name, ".") && strcmp(dir->d_name, ".."))
        {
            count++;
        }
    }
    closedir(d);

    names = calloc(count, sizeof(char *));
    if (!names)
    {
        printf("erorr allocating file!\n");
        return NULL;
    }

    d = opendir(dir_path);
    if (!d)
    {
        printf("error openning dir!\n");
        return NULL;
    }

    int i = 0;
    while ((dir = readdir(d)) != NULL)
    {
        if (strcmp(dir->d_name, ".") && strcmp(dir->d_name, ".."))
        {
            names[i] = calloc(strlen(dir->d_name) + 1, sizeof(char));
            if (!names[i])
            {
                printf("erorr in allocation of one of the names");
                for (int j = 0; j < i; j++)
                {
                    free(names[j]);
                }
                free(names);
                closedir(d);
                return NULL;
            }
            strcpy(names[i], dir->d_name);
            i++;
        }
    }
    closedir(d);

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (strcmp(names[j], names[j + 1]) > 0)
            {
                char *temp = names[j];
                names[j] = names[j + 1];
                names[j + 1] = temp;
            }
        }
    }
    *num_of_files = count;

    return names;
}

int main(int argc, char *argv[])
{    
    char **names = NULL;
    char *baseFilePath = NULL;
    FILE *file = NULL;
    DIR *d = 0;
    struct dirent *dir = 0;
    char fPath[MAX_LEN] = {0};
    char *fileBuffer = NULL;
    char *virusBuf = NULL;
    int fSize = 0;
    int vSize = 0;
    int virusFound = 0;
    int isQuick = 0;
    int alreadyInfected = 0;
    int num_of_files = 0;
    int i = 0;
    int mode = FULL;
    char logPath[MAX_LEN] = {0};
    if (argc != ARGC_AMOUNT)
    {
        printf("Usage: %s <directory path> <virus signature path>\n", argv[0]);
        return 1;
    }
    strcpy(logPath, argv[1]);
    strcat(logPath, "/AntiVirusLog.txt");
    FILE *log = fopen(logPath, "w");
    
    
    baseFilePath = argv[ARGV_DIR];
    virusBuf = read_file(argv[ARGV_VIRUS], &vSize, isQuick);
    if(virusBuf == NULL)
    return 1;
    d = opendir(argv[1]);
    
    if (d == NULL)
    {
        printf("Error opening directory");
        return 1;
    }
    
    if (log == NULL)
    {
        printf("Error opening log file!\n");
        return 1;
    }
    printf("Welcome to my Virus Scan!\n\nFolder to scan: %s\nVirus signature: %s\n\nPress 0 for a normal scan or any other key for a quick scan: ", argv[1], argv[ARGV_VIRUS]);
    scanf("%d", &isQuick);
    printf("Scanning began...\nThis process may take several minutes...\n\nScanning:\n");
    
    fputs("Anti-virus began! Welcome!\n\nFolder to scan:\n", log);
    fputs(argv[1], log);
    fputs("\nVirus signature:\n", log);
    fputs(argv[ARGV_VIRUS], log);
    fputs("\n\nScanning option:\n", log);
    if(isQuick)
    {
        fputs("Quick scan", log);
    }
    else
    {
        fputs("Normal scan", log);
    }
    fputs("\n\nResults:\n", log);

    names = get_sorted_file_names(argv[1], &num_of_files);
    if(names == NULL)
        return 1;

    for(i = 0; i < num_of_files; i++)
    {            
        alreadyInfected = 0;
        fPath[0] = '\0';
        strcat(fPath, baseFilePath);
        strcat(fPath, "/");
        if(isQuick != 0)
        {
            mode = FIRST_20;
        }
        strcat(fPath, names[i]);
        fileBuffer = read_file(fPath, &fSize, mode);
        if(fileBuffer == NULL)
            return 1;
        virusFound = contains_virus(fileBuffer, fSize, virusBuf, vSize);
        printf("%s - ", fPath);
        fputs(fPath, log);    
        if(!isQuick)
        {
            if(virusFound)
            {
                printf("Infected!\n");
                fputs(" Infected!\n", log);
            }
            else
            {
                printf("Clean\n");
                fputs(" Clean\n", log);
            }
        }
        else
        {
            if(virusFound)
            {
                alreadyInfected = 1;
                printf("Infected! (first 20%%)\n");
                fputs(" Infected! (first 20%%)\n", log);
            }
        }
        free(fileBuffer);
        if(isQuick && alreadyInfected == 0)
        {
            mode = LAST_20;
            fileBuffer = read_file(fPath, &fSize, mode);
            if(fileBuffer == NULL)
                return 1;
            virusFound = contains_virus(fileBuffer, fSize, virusBuf, vSize);
            if(virusFound)
            {
                printf("Infected! (last 20%%)\n");
                fputs(" Infected! (last 20%%)\n", log);
                alreadyInfected = 1;
            }
            
            free(fileBuffer);
        }
        if(isQuick && alreadyInfected == 0)
        {
            mode = FULL;
            fileBuffer = read_file(fPath, &fSize, mode);
            if(fileBuffer == NULL)
            return 1;
            virusFound = contains_virus(fileBuffer, fSize, virusBuf, vSize);
            if(virusFound)
            {
                printf("Infected!\n");
                fputs(" Infected!\n", log);
                alreadyInfected = 1;
            }
            else
            {
                printf("Clean\n");
                fputs(" Clean\n", log);
            }

            free(fileBuffer);
        }
    }
    printf("Scan Completed.\nSee log path for results: %s\n", logPath);
    free(virusBuf);
    i = 0;
    for (i = 0; i < num_of_files; i++)
    {
        free(names[i]);
    }
    free(names);
    closedir(d);
    fclose(log);
    getchar();
    getchar();
    return 0;
}
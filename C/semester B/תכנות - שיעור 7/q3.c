#include <stdio.h>
#include <string.h>


int copyText(FILE* source, FILE* dest);
int copyBinary(FILE* source, FILE* dest);

#define ARGC_AMOUNT 4
#define SRC 2
#define DES 3

int main(int argc, char* argv[])
{
    FILE *srcFile = NULL, *destFile = NULL;
    int choice = 0;
    int isText = 0;

    if (argc != ARGC_AMOUNT)
    {
        printf("Invalid execution\n");
        printf("Usage: %s (textCopy or binaryCopy) <sourceFilename_filename> <destFilenameination_filename>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "textCopy") == 0)
    {
        isText = 1;
    }

    if(isText)
    {
        srcFile = fopen(argv[SRC], "r");
    }
    else
    {
        srcFile = fopen(argv[SRC], "rb");
    }
    if (srcFile == NULL)
    {
        printf("Source file %s does not exist.\n", argv[SRC]);
        return 1;
    }

    destFile = fopen(argv[DES], "r");
    if (destFile != NULL)
    {
        fclose(destFile);
        printf("Do you want to overwrite? 0 (no) or 1 (yes)\n");
        scanf("%d", &choice);
        if (choice != 1)
        {
            fclose(srcFile);
            return 1;
        }
    }

    if(isText)
    {
        destFile = fopen(argv[DES], "w");
    }
    else
    {
        destFile = fopen(argv[DES], "wb");
    }
    if (destFile == NULL)
    {
        printf("Failed to open destination file\n");
        fclose(srcFile);
        return 1;
    }

    if (isText)
        copyText(srcFile, destFile);
    else
        copyBinary(srcFile, destFile);

    printf("Copy completed\n");

    fclose(srcFile);
    fclose(destFile);

    return 0;
}

/*
Copies the content of a text file from the source to the destination.
input:source: A pointer to the opened source file (FILE*), dest: A pointer to the opened destination file (FILE*).
output: returns 0 upon successful completion.
*/
int copyText(FILE* source, FILE* dest)
{
    char ch = ' ';
    while ((ch = fgetc(source)) != EOF)
    {
        fputc(ch, dest);
    }
    return 0;
}

/*
Copies the content of a binary file from the source to the destination.
input: source: A pointer to the opened source file (FILE*), dest: A pointer to the opened destination file (FILE*).
output: returns 0 upon successful completion.
*/
int copyBinary(FILE* source, FILE* dest)
{
    char buffer[1024] = {0};
    size_t bytes = 0;
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0)
    {
        fwrite(buffer, 1, bytes, dest);
    }
    return 0;
}
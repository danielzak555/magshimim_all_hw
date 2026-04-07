#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 50

typedef struct date
{
    int day;
    int month;
    int year;
} date;

typedef struct singer
{
    char name[STR_LEN];
    int start_year;
    int albums;
    char genre[STR_LEN];
} singer;

typedef struct instgram
{
    char username[STR_LEN];
    int followers;
    int posts;
    int approved;
} instgram;

int main(void)
{
    date event = {1, 1, 2026};
    singer drori = {"drori smanmanoli", 2024, 3, "pop"};
    instgram drori_inst = {"drorism", 1000000, 100, 1};
    print_structures(drori, event, drori_inst);
    getchar();
    return 0;
}

/*
the function prints all the structures
input: singer, date, instgram
output: none 
*/
void print_structures(singer s, date d, instgram i)
{
    printf("Date: %02d/%02d/%04d\n", d.day, d.month, d.year);
    printf("Singer: %s\n", s.name);
    printf("Start Year: %d\n", s.start_year);
    printf("Albums: %d\n", s.albums);
    printf("Genre: %s\n", s.genre);
    printf("Instagram Username: %s\n", i.username);
    printf("Followers: %d\n", i.followers);
    printf("Posts: %d\n", i.posts);
    printf("Approved: %d\n", i.approved);
}

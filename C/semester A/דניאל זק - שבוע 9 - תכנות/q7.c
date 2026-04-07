#include <stdio.h>
#include <unistd.h>  // For sleep and usleep

void printFrame1() {
    printf("\033[H\033[J"); // Clear the screen
    printf("     O/       Hi Maor!\n"); 
    printf("    /|\\\n"); 
    printf("     |       \n"); 
    printf("    / \\     \n"); 
}

void printFrame2() {
    printf("\033[H\033[J"); // Clear the screen
    printf("      O       Hi Maor!\n"); 
    printf("     /|\\      \n"); 
    printf("      |       \n"); 
    printf("     / \\     \n"); 
}

void printFrame3() {
    printf("\033[H\033[J"); // Clear the screen
    printf("     O\\       Hi Maor!\n"); 
    printf("    /|\\      \n"); 
    printf("     |       \n"); 
    printf("    / \\     \n"); 
}

void printFrame4() {
    printf("\033[H\033[J"); // Clear the screen
    printf("      O       Hi Maor!\n"); 
    printf("     \\|/      \n"); 
    printf("      |       \n"); 
    printf("     / \\     \n"); 
}

int main() {
    while (1) {
        printFrame1();
        usleep(400000); // Pause for 400ms
        printFrame2();
        usleep(400000); // Pause for 400ms
        printFrame3();
        usleep(400000); // Pause for 400ms
        printFrame4();
        usleep(400000); // Pause for 400ms
    }
    return 0;
}

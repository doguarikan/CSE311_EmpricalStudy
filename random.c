#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *file = fopen("input.txt", "w");
    srand(time(NULL));
    for (int i = 0; i < 1000000; i++) {
        int random_number = rand() % 65536 + 1;
        fprintf(file, "%d\n", random_number);
    }
    fclose(file);
    return 0;
}

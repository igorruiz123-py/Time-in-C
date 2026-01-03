#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

// Tempo de Execução: Meça quanto tempo um algoritmo de ordenação (ex: Bubble Sort) leva para ordenar um arquivo de 10.000 números inteiros.

void Now(struct timespec *ts){

    clock_gettime(CLOCK_REALTIME, ts);
}

void FormatTime(const struct timespec *ts, char *buffer, size_t size){

    struct tm tm_info;
    size_t len;

    localtime_r(&ts->tv_sec, &tm_info);

    len = strftime(buffer, size, "%d/%m/%Y - %H:%M:%S", &tm_info);

    if (len > 0 && len < size){
        snprintf(buffer + len, size - len, ".%09ld", ts->tv_nsec / 1000000);
    }
}

int CheckFile(FILE *file){

    if (file == NULL){
        perror("fopen");
        exit (EXIT_FAILURE);
    }

    return 1;
}

void loading(){

    int width = 30;

    for (int progress = 0; progress <= width; progress++) {
        printf("\r["); 

        for (int i = 0; i < width; i++) {
            if (i < progress)
                printf("#");
            else
                printf(" ");
        }

        printf("] %d%%", (progress * 100) / width);
        fflush(stdout);
        usleep(200000); // 200 ms
    }

    printf("\n");
}

void MkFile(FILE *file){

    srand(time(NULL));

    file = fopen("numbers.txt", "w");

    CheckFile(file);

    printf("Inserting numbers on file...\n");
    
    loading();

    for (int i = 0; i < 10000; i++){
        fprintf(file, "%d \n", rand() % 1001);
    }

    fclose(file);

    printf("Numbers inserted on file! \n");
}

void ReadFile(FILE *file){

    FILE *SortedFile;

    int buffer[10000];

    struct timespec t1, t2;
    char buff1[64], buff2[64];

    file = fopen("numbers.txt", "r");

    CheckFile(file);

    int i = 0;

    printf("Sorting numbers...\n");

    loading();

    Now(&t1);
    FormatTime(&t1, buff1, sizeof(buff1));

    while(fscanf(file, "%d", &buffer[i]) == 1){
        i++;
    }

    for (int i = 0; i < 10000; i++){
        for (int j = 0; j < 10000 - 1 - i; j++){
            if (buffer[j] > buffer[j + 1]){
                int temp = buffer[j];
                buffer[j] = buffer[j + 1];
                buffer[j + 1] = temp;
            }
        }
    }

    fclose(file);

    SortedFile = fopen("sorted_file.txt", "w");

    CheckFile(SortedFile);

    for (int i = 0; i < 10000; i++){
        fprintf(SortedFile, "%d \n", buffer[i]);
    }

    Now(&t2);
    FormatTime(&t2, buff2, sizeof(buff2));

    fclose(SortedFile);

    printf("Numbers sorted! \n\n");

    printf("Start time: %s \n", buff1);
    printf("End time: %s \n", buff2);
}

int main(){

    FILE file;

    MkFile(&file);

    ReadFile(&file);
}
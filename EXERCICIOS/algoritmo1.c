#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
Diferença entre Datas: Solicite ao usuário duas datas (dia, mês, ano)
e calcule o número de dias decorridos entre elas
*/

void FlushBuffer(){
    
    int temp = 0;

    while((temp = getchar()) != '\n' && temp != EOF){};
}

int CheckData(int *number){

    if (scanf("%d", number) == 0){
        printf("Invalid entry! \n");
        FlushBuffer();
        exit (EXIT_FAILURE);
    }

    return 1;
}

typedef struct {

    int day;
    int month;
    int year;

} datetime;

void date(datetime *var){

    printf("Enter value for day: ");
    CheckData(&var->day);

    printf("Enter value for month: ");
    CheckData(&var->month);

    printf("Enter value for year: ");
    CheckData(&var->year);

    printf("%d/%d/%d \n", var->day,var->month, var->year);

}

void DiffDateTime(datetime *var1, datetime *var2){

    int DiffYear = (var1->year - var2->year) * 365;
    int DiffMonth = (var1->month - var2->month) * 30;
    int DiffDay = var1->day - var2->day;

    int sum = (DiffDay + DiffMonth + DiffYear);

    printf("\nTotal sum of days between date 1 and date 2: %d \n", sum); 
}

void loading() {

    printf("\nCalculating... \n");

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

    printf("\nCalculated!\n");

}

int main(){

    datetime time1;
    datetime time2;

    date(&time1);

    printf("\n");

    date(&time2);

    loading();

    DiffDateTime(&time1, &time2);

}

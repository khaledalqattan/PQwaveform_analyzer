#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "io.h"
#include "io.h"
#include <string.h>
#include <math.h>

int main(void){
    int rows_count =0;
    waveform* data = load_csv("power_quality_log.csv", &rows_count); // loading data from file
    Results_txt(data, rows_count);
    double Va = variance_A(data, rows_count);
    double std_A = sqrt(Va); //standard diviaton
    printf("variance A= %lf\n", Va);
    printf("std A= %lf\n", std_A);
free(data); // malloc()
return 0;
}

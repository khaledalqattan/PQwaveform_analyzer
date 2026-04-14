#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "io.h"
#include "cmake-build-debug/io.h"
#include <string.h>
#include <math.h>

int main(void){
    int rows_count =0;
    waveform* data = load_csv("power_quality_log.csv", &rows_count); // loading data from file
    Results_txt(data, rows_count);
free(data); // malloc()
return 0;
}

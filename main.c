#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "io.h"
#include "cmake-build-debug/io.h"
#include <string.h>


int main(void){
    int rows_count =0;
    waveform* data = load_csv("power_quality_log.csv", &rows_count);

    printf("loadded %d rows", rows_count);
    printf("voltage in first %f", data[1].timestamp);
    return 0;
}
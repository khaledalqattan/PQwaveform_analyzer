#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "io.h"
#include "io.h"
#include <string.h>
#include <math.h>

int main(int argc, char *argv[]){
    char *filename = argv[1];
    int rows_count =0;
    waveform* data = load_csv(filename, &rows_count); // loading data from file
    Results_txt(data, rows_count);
free(data); // malloc()
return 0;
}

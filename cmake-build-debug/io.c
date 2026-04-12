#include <stdlib.h>
#include <stdio.h>
#include "io.h"
#include <string.h>

waveform* load_csv(const char* file, int* rows_count) {
    FILE *fb = fopen(file, "r");
    if (fb == NULL) {
        printf("Error in opening the file"); //debug
        return NULL; // open file
    }
    char line[256];
    if (fgets(line, sizeof(line), fb) == NULL) {
        fclose(fb);
        return NULL; // skip header line in file
    }
    int max = 1000;
    int count = 0;

    waveform *data = malloc(max * sizeof(waveform));
    if (data == NULL) {
        fclose(fb);
        return NULL;
    }
    while (fgets(line, sizeof(line), fb) != NULL) {
        char *token;
//(1)
        token = strtok(line, ",");
        if (token == NULL)
            continue;
        data[count].timestamp = atof(token);
//(2)
        token = strtok(NULL, ",");
        if (token == NULL)
            continue;
        data[count].phase_A_voltage = atof(token);
//(3)
        token = strtok(NULL, ",");
        if (token == NULL)
            continue;
        data[count].phase_B_voltage = atof(token);
//(4)
        token = strtok(NULL, ",");
        if (token == NULL)
            continue;
        data[count].phase_C_voltage = atof(token);
//(5)
        token = strtok(NULL, ",");
        if (token == NULL)
            continue;
        data[count].line_current = atof(token);
//(6)
        token = strtok(NULL, ",");
        if (token == NULL)
            continue;
        data[count].frequency = atof(token);
//(7)
        token = strtok(NULL, ",");
        if (token == NULL)
            continue;
        data[count].power_factor =atof(token);
//(8)
        token = strtok(NULL, ",");
        if (token == NULL)
            continue;
        data[count].thd_percent = atof(token);
        count++;
    }

    fclose(fb); //close file
    *rows_count = count; //store number of rows
    return data; // return pointer to apply dynamic allocation malloc()
}
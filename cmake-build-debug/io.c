#include <stdlib.h>
#include <stdio.h>
#include "io.h"
#include <string.h>

waveform* load_csv(const char* file, int* rows_count) {
    FILE *fb = fopen(file, "r"); // open file
    if (fb == NULL) {
        printf("Error in opening the file"); //debug
        return NULL;
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
void Results_txt(const waveform *data, int rows_count){
    FILE *rf = fopen("results.txt", "w");
    if (rf == NULL) {
        printf("Error");
        return;
    }
    fprintf(rf, "POWER QUALITY REPORT\n");
    // tests RMS
    double rmsA = RMS_voltage_A(data, rows_count);
    double rmsB = RMS_voltage_B(data, rows_count);
    double rmsC = RMS_voltage_C(data, rows_count);
    fprintf(rf, "A RMS = %f\n", rmsA);
    fprintf(rf,"B RMS = %f\n", rmsB);
    fprintf(rf,"C RMS = %f\n", rmsC);
    // test peak to peak
    double peakA = peak_peak_A(data, rows_count);
    double peakB = peak_peak_B(data, rows_count);
    double peakC = peak_peak_C(data, rows_count);
    fprintf(rf,"peak to peak amplitude A = %f\n", peakA);
    fprintf(rf,"peak to peak amplitude B = %f\n", peakB);
    fprintf(rf,"peak to peak amplitude C = %f\n", peakC);
    // test DC offset
    double dcA = DC_offset_A(data, rows_count);
    double dcB = DC_offset_B(data, rows_count);
    double dcC = DC_offset_C(data, rows_count);
    fprintf(rf,"phase A DC offset = %f\n", dcA);
    fprintf(rf,"phase B DC offset = %f\n", dcB);
    fprintf(rf,"phase C DC offset = %f\n", dcC);
    // test clipping
    double clipA = Clipping_A(data, rows_count);
    double clipB = Clipping_B(data, rows_count);
    double clipC = Clipping_C(data, rows_count);
    double clipT = clipA + clipB + clipC;
    fprintf(rf,"number of clippings in phase A is %f\n", clipA);
    fprintf(rf,"number of clippings in phase B is %f\n", clipB);
    fprintf(rf,"number of clippings in phase C is %f\n", clipC);
    fprintf(rf,"number of clippings in all phases is %f\n", clipT);
    //  test tolerance
    fprintf(rf,"For tolerance compliance: Y = compliant , N = Not compliant\n");
    fprintf(rf,"Phase A = %c\n", tolerance_check(rmsA));
    fprintf(rf,"Phase B = %c\n", tolerance_check(rmsB));
    fprintf(rf,"Phase C = %c\n", tolerance_check(rmsC));

    fclose(rf);
}
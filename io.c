#include <stdlib.h>
#include <stdio.h>
#include "io.h"
#include <string.h>
#include <math.h>

waveform* load_csv(const char* file, int* rows_count) {
    FILE *fb = fopen(file, "r"); // open file
    if (fb == NULL) {
        printf("Error in opening the file");
        return NULL;
    }
    char line[256];
    fgets(line, sizeof(line), fb);//skip header line in file

// count the number of lines for memory allocation
    int lines = 0;
    while (fgets(line, sizeof(line), fb) !=NULL) //keep reading until there is nothing
    {
       lines++;
    }
    *rows_count = lines;// to send the counted lines

    // set memory to counted lines
    waveform *data = malloc(lines * sizeof(waveform));

    rewind(fb); // reset the file to start point
    fgets(line, sizeof(line), fb); //skip the header
    //store data
    int count = 0;
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

    fclose(fb);
    return data;
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
    fprintf(rf, "A RMS = %lf\n", rmsA);
    fprintf(rf,"B RMS = %lf\n", rmsB);
    fprintf(rf,"C RMS = %lf\n", rmsC);
    // test peak to peak
    double peakA = peak_peak_A(data, rows_count);
    double peakB = peak_peak_B(data, rows_count);
    double peakC = peak_peak_C(data, rows_count);
    fprintf(rf,"peak to peak amplitude A = %lf\n", peakA);
    fprintf(rf,"peak to peak amplitude B = %lf\n", peakB);
    fprintf(rf,"peak to peak amplitude C = %lf\n", peakC);
    // test DC offset
    double dcA = DC_offset_A(data, rows_count);
    double dcB = DC_offset_B(data, rows_count);
    double dcC = DC_offset_C(data, rows_count);
    fprintf(rf,"phase A DC offset = %lf\n", dcA);
    fprintf(rf,"phase B DC offset = %lf\n", dcB);
    fprintf(rf,"phase C DC offset = %lf\n", dcC);
    // test clipping
    int clipA = Clipping_A(data, rows_count);
    int clipB = Clipping_B(data, rows_count);
    int clipC = Clipping_C(data, rows_count);
    int clipT = clipA + clipB + clipC;
    fprintf(rf,"number of clippings in phase A is %d\n", clipA);
    fprintf(rf,"number of clippings in phase B is %d\n", clipB);
    fprintf(rf,"number of clippings in phase C is %d\n", clipC);
    fprintf(rf,"number of clippings in all phases is %d\n", clipT);
    //  test tolerance
    fprintf(rf,"For tolerance compliance: Y = compliant , N = Not compliant\n");
    fprintf(rf,"Phase A = %c\n", tolerance_check(rmsA));
    fprintf(rf,"Phase B = %c\n", tolerance_check(rmsB));
    fprintf(rf,"Phase C = %c\n", tolerance_check(rmsC));
    // test variance
    double Va = variance_A(data, rows_count);
    double Vb = variance_B(data, rows_count);
    double Vc = variance_C(data, rows_count);
    fprintf(rf,"variance of phase A= %lf\n", Va);
    fprintf(rf,"variance of phase B= %lf\n", Vb);
    fprintf(rf,"variance of phase C= %lf\n", Vc);
    // test Standard deviation
    double std_A = sqrt(Va);
    double std_B = sqrt(Vb);
    double std_C = sqrt(Vc);
    fprintf(rf,"Standard deviation for phase A= %lf\n", std_A);
    fprintf(rf,"Standard deviation for phase B= %lf\n", std_B);
    fprintf(rf,"Standard deviation for phase C= %lf\n", std_C);
    fclose(rf);
}
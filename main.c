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
    // tests loading data
    printf("loadded %d rows\n", rows_count);
    printf("voltage in first %f\n", data[1].phase_B_voltage);
    printf("voltage in first %f\n", data[1].phase_A_voltage);
    printf("voltage in first %f\n", data[1].phase_C_voltage);
    printf("time in first %f\n", data[1].timestamp);
    printf("PF in first %f\n", data[1].power_factor);
    // tests RMS
    double rmsA = RMS_voltage_A(data, rows_count);
    double rmsB = RMS_voltage_B(data, rows_count);
    double rmsC = RMS_voltage_C(data, rows_count);
    printf("A RMS = %f\n", rmsA);
    printf("B RMS = %f\n", rmsB);
    printf("C RMS = %f\n", rmsC);
    // test peak to peak
    double peakA = peak_peak_A(data, rows_count);
    double peakB = peak_peak_B(data, rows_count);
    double peakC = peak_peak_C(data, rows_count);
    printf(" peak to peak amplitude A = %f\n", peakA);
    printf(" peak to peak amplitude B = %f\n", peakB);
    printf(" peak to peak amplitude C = %f\n", peakC);
    // test DC offset
    double dcA = DC_offset_A(data, rows_count);
    double dcB = DC_offset_B(data, rows_count);
    double dcC = DC_offset_C(data, rows_count);
    printf("phase A DC offset = %f\n", dcA);
    printf("phase B DC offset = %f\n", dcB);
    printf("phase C DC offset = %f\n", dcC);
    // test clipping
    double clipA = Clipping_A(data, rows_count);
    double clipB = Clipping_B(data, rows_count);
    double clipC = Clipping_C(data, rows_count);
    double clipT = clipA + clipB + clipC;
    printf("number of clippings in phase A is %f\n", clipA);
    printf("number of clippings in phase B is %f\n", clipB);
    printf("number of clippings in phase C is %f\n", clipC);
    printf("number of clippings in all phases is %f\n", clipT);
    //  test tolerance
    printf("For tolerance compliance Y = compliant , N = Not compliant\n");
    printf("Phase A = %c\n", tolerance_check(rmsA));
    printf("Phase B = %c\n", tolerance_check(rmsB));
    printf("Phase C = %c\n", tolerance_check(rmsC));
free(data); // malloc()
return 0;
}

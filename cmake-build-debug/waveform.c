#include "waveform.h"
#include <math.h>

// RMS
double RMS_voltage_A (const waveform *data, int rows_count) {
    double sum = 0;
    for(int i =0; i<rows_count; i++){
        sum += data[i].phase_A_voltage * data[i].phase_A_voltage;
    }
    double mean = sum / rows_count;

    return sqrt(mean);
}
double RMS_voltage_B (const waveform *data, int rows_count) {
    double sum = 0;
    for(int i =0; i<rows_count; i++){
        sum += data[i].phase_B_voltage * data[i].phase_B_voltage;
    }
    double mean = sum / rows_count;

    return sqrt(mean);
}
double RMS_voltage_C (const waveform *data, int rows_count) {
    double sum = 0;
    for(int i =0; i<rows_count; i++){
        sum += data[i].phase_C_voltage * data[i].phase_C_voltage;
    }
    double mean = sum / rows_count;

    return sqrt(mean);
}
// Peak to Peak
double peak_peak_A (const waveform *data, int rows_count) {
    double max = data[0].phase_A_voltage;
    double min = data[0].phase_A_voltage;
    for (int i=1; i<rows_count; i++){
        if (data[i].phase_A_voltage > max)
            max = data[i].phase_A_voltage;
        if (data[i].phase_A_voltage < min)
            min = data[i].phase_A_voltage;
    }
    return max - min;
}
double peak_peak_B (const waveform *data, int rows_count) {
    double max = data[0].phase_B_voltage;
    double min = data[0].phase_B_voltage;
    for (int i=1; i<rows_count; i++){
        if (data[i].phase_B_voltage > max)
            max = data[i].phase_B_voltage;
        if (data[i].phase_B_voltage < min)
            min = data[i].phase_B_voltage;
    }
    return max - min;
}
double peak_peak_C (const waveform *data, int rows_count) {
    double max = data[0].phase_C_voltage;
    double min = data[0].phase_C_voltage;
    for (int i=1; i<rows_count; i++){
        if (data[i].phase_C_voltage > max)
            max = data[i].phase_C_voltage;
        if (data[i].phase_C_voltage < min)
            min = data[i].phase_C_voltage;
    }
    return max - min;
}
// DC Offset
double DC_offset_A (const waveform *data, int rows_count) {
    double sum = 0;
    for (int i=0; i < rows_count; i++) {
        sum += data[i].phase_A_voltage;
    }
    return sum / rows_count;
}
double DC_offset_B (const waveform *data, int rows_count) {
    double sum = 0;
    for (int i=0; i < rows_count; i++) {
        sum += data[i].phase_B_voltage;
    }
    return sum / rows_count;
}
double DC_offset_C (const waveform *data, int rows_count) {
    double sum = 0;
    for (int i=0; i < rows_count; i++) {
        sum += data[i].phase_C_voltage;
    }
    return sum / rows_count;
}

#ifndef PQWAVEFORM_ANALYZER_WAVEFORM_H
#define PQWAVEFORM_ANALYZER_WAVEFORM_H

typedef struct {
    double timestamp;
    double phase_A_voltage;
    double phase_B_voltage;
    double phase_C_voltage;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percent;
} waveform; //structure for variable in the waveform
double RMS_voltage_A (const waveform *data, int rows_count); // Va RMS
double RMS_voltage_B (const waveform *data, int rows_count); // Vb RMS
double RMS_voltage_C (const waveform *data, int rows_count); // Vc RMS
double peak_peak_A (const waveform *data, int rows_count); // peak to peak A
double peak_peak_B (const waveform *data, int rows_count); // peak to peak B
double peak_peak_C (const waveform *data, int rows_count); // peak to peak C
double DC_offset_A (const waveform *data, int rows_count); // DC offset A
double DC_offset_B (const waveform *data, int rows_count); // DC offset B
double DC_offset_C (const waveform *data, int rows_count); // DC offset C
int Clipping_A (const waveform*data, int rows_count); // Clipping A
int Clipping_B (const waveform*data, int rows_count); // clipping B
int Clipping_C (const waveform*data, int rows_count); // clipping C
char tolerance_check (double rms); // tolerance check
#endif //PQWAVEFORM_ANALYZER_WAVEFORM_H
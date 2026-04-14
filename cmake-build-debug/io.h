

#ifndef PQWAVEFORM_ANALYZER_IO_H
#define PQWAVEFORM_ANALYZER_IO_H
#include "waveform.h"

waveform* load_csv(const char* file, int* rows_count); // pointer to count number of rows for dynamic memory allocation
void Results_txt(const waveform *data, int rows_count); // Results to .txt file
#endif

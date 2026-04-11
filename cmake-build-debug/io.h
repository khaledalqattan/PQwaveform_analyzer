

#ifndef PQWAVEFORM_ANALYZER_IO_H
#define PQWAVEFORM_ANALYZER_IO_H
#include "waveform.h"

waveform* load_csv(const char* file, int* rows_count); // pointer to count number of rows for dynamic memory allocation

#endif

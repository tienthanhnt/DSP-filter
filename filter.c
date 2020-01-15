#include "filters.h"

int fir9Filter(int input, channel_t channel)
{
    int i;
    int output;
    int currentSampleIndex;

    currentSampleIndex = sampleIndex[channel];
    sampleBuffer[channel][currentSampleIndex] = input >> 8;
    for (i=0; i < 9; i++)
    {
        output += lowPassFilterCoef[localFilterIndex][i]* sampleBuffer[channel][(currentSampleIndex - i + 9) % 9]; // change filter here
    }
    output <<= 8;
    sampleIndex[channel] = (currentSampleIndex + 1) % 9;
    return output;

}


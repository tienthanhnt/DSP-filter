#ifndef __Filters_DEFINED
#define __Filters_DEFINED

typedef enum
{
  left0 = 0,
  right0,
  left1,
  right1,
  numberOfChannels
}channel_t;

static int sampleBuffer[numberOfChannels][9]; 
static int sampleIndex[numberOfChannels];
int fir9Filter(int input, channel_t channel);
;

static const float lowPassFilterCoef[9] = {-0.02771010f, 0.05351285f, 0.13862957f,
        0.22591615f, 0.26270698f, 0.22591615f, 0.13862957f, 0.05351285f, -0.02771010f};
static const float highPassFilterCoef[9] = {0.04580234f, -0.03762617f, -0.10357527f,
        -0.25501761f, 0.61416455f, -0.25501761f, -0.10357527f, -0.03762617f, 0.04580234f};
static const float bandPassFilterCoef[9] = {-0.15872657f, -0.21070283f, -0.03056337f,
        0.13461129f, 0.39489365f, 0.13461129f, -0.03056337f, -0.21070283f, -0.15872657f};

#endif


#include "vas_osc.h"

/**
 * creates a new vas_osc object.<br>
 */

vas_osc *vas_osc_new(int tableSize)
{
    vas_osc *x = (vas_osc *)malloc(sizeof(vas_osc));
    x->tableSize = tableSize;
    x->formantDuration = tableSize;
    x->lookupWaveTable = (float *) vas_mem_alloc(x-> tableSize * sizeof(float));
    x->lookupFormantTable1 = (float *) vas_mem_alloc(x-> tableSize * sizeof(float));
    x->lookupFormantTable2 = (float *) vas_mem_alloc(x-> tableSize * sizeof(float));
    x->lookupFormantTable3 = (float *) vas_mem_alloc(x-> tableSize * sizeof(float));
    x->lookupFormantTable4 = (float *) vas_mem_alloc(x-> tableSize * sizeof(float));
    x->currentIndex = 0;
    x->frequency = 440;
    x->envelopeIndex = 0;
    x->numberOfHarmonics = 10;
    x->Formant0 = 0;
    x->Formant1 = 0;
    x->Formant2 = 0;
    x->Formant3 = 0;
    x->Formant4 = 22050;
    
    for(int i = 0; i < x->numberOfHarmonics; i++)
    {
        x->harmonicGain[i] = 1 / floor(i + 1);
        x->harmonicIndex[i] = 0;
    }
    
    vas_osc_setWavetable(x);
    vas_osc_setFormants(x);
    
    return x;
}

/**
 * calculate a mathematic sinus function and load them to the oscillator
 */

void vas_osc_setWavetable(vas_osc *x)
{
    float stepSize = (M_PI*2) / (float)x->tableSize;
    float currentX = 0;
    
    for(int i = 0; i < x->tableSize; i++)
    {
        x->lookupWaveTable[i] = sinf(currentX);
        currentX += stepSize;
    }
}

/**
 * set all formant envelopes to continous
 */

void vas_osc_setFormants(vas_osc *x)
{
    for(int i = 0; i < x->tableSize; i++)
    {
        x->lookupFormantTable1[i] = 1;
        x->lookupFormantTable2[i] = 1;
        x->lookupFormantTable3[i] = 1;
        x->lookupFormantTable4[i] = 1;
    }
}

/**
 * free all wavetables
 */

void vas_osc_free(vas_osc *x)
{
    vas_mem_free(x->lookupWaveTable);
    vas_mem_free(x->lookupFormantTable1);
    vas_mem_free(x->lookupFormantTable2);
    vas_mem_free(x->lookupFormantTable3);
    vas_mem_free(x->lookupFormantTable4);
    free(x);
}

/**
 * check the frequency of the harmonics and multiply them with the correct envelope
 */

float vas_osc_output(vas_osc *x, float frequency, int Index, float Gain)
{
    if (frequency <= x->Formant4)
    {
        if (frequency <= x->Formant3)
        {
            if (frequency <= x->Formant2)
            {
                if (frequency <= x->Formant1)
                {
                    if (frequency >= x->Formant0)
                    {
                        return x->lookupWaveTable[Index] * Gain * x->lookupFormantTable1[x->envelopeIndex];
                    }
                    else
                        return 0;
                }
                return x->lookupWaveTable[Index] * Gain * x->lookupFormantTable2[x->envelopeIndex];
            }
            return x->lookupWaveTable[Index] * Gain * x->lookupFormantTable3[x->envelopeIndex];
        }
        return x->lookupWaveTable[Index] * Gain * x->lookupFormantTable4[x->envelopeIndex];
    }
    else
        return 0;
}

/**
 * writes the signal vectors to the output
 */

void vas_osc_process(vas_osc *x, float *in, float *out, int vectorSize)
{
    int i = vectorSize;
    
    while(i--)
    {
        *out = vas_osc_output(x, x->frequency, x->currentIndex, 1);
        
        x->currentIndex += x->frequency;

        for(int i = 0; i < x->numberOfHarmonics; i++)
        {
            float harmonicFreq = x->frequency * (i+2);
            int intIndex = floor(x->harmonicIndex[i]);
            
            *out += vas_osc_output(x, harmonicFreq, intIndex, x->harmonicGain[i]);
            
            x->harmonicIndex[i] += harmonicFreq;
            
            if(x->harmonicIndex[i] >= x->tableSize)
                x->harmonicIndex[i] -= x->tableSize;
        }
        
        x->envelopeIndex += floor(x->tableSize/x->formantDuration);
        
        if(x->currentIndex >= x->tableSize)
            x->currentIndex -= x->tableSize;
        
        if(x->envelopeIndex >= x->tableSize)
            x->envelopeIndex = 0;
        
        out++;
    }
}

/**
 * set the frequency of the oscillator
 */

void vas_osc_setFrequency(vas_osc *x, float frequency)
{
    if(frequency > 0)
        x->frequency = frequency;
}

/**
 * set the number of harmonics
 */

void vas_osc_setHarmonics(vas_osc *x, float harmonics)
{
    if(harmonics > 0)
    {
        if (harmonics > 40)
            harmonics = 40;
        
        x->numberOfHarmonics = harmonics;
    }
    
    for(int i = 0; i < x->numberOfHarmonics; i++)
    {
        x->harmonicGain[i] = (1 / floor(i + 1));
        x->harmonicIndex[i] = 0;
    }
    
    x->currentIndex = 0;
}

/**
 * set the range of formants
 */

void vas_osc_setFormantrange(vas_osc *x, float formant0, float formant1, float formant2, float formant3, float formant4)
{
    if(formant0 > 0)
        x->Formant0 = floor(formant0);
    
    if(formant1 > 0)
        x->Formant1 = floor(formant1);
    
    if(formant2 > 0)
        x->Formant2 = floor(formant2);
    
    if(formant3 > 0)
        x->Formant3 = floor(formant3);
    
    if(formant4 > 0)
        x->Formant4 = floor(formant4);
}

/**
 * set the duration of the envelope cycle
 */

void vas_osc_setFormantFrequency(vas_osc *x, float frequency)
{
    if (frequency > 0)
        x->formantDuration = floor(x->tableSize/frequency);
}




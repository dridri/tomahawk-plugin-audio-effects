#include <QWidget>
#include <QtPlugin>
#include <utils/Logger.h>

#include "Equalizer.h"

#include <stdint.h>
#include <math.h>

#define min(a, b) ((a) <= (b)) ? (a) : (b)
#define max(a, b) ((a) >= (b)) ? (a) : (b)

#define BANDS_COUNT 1024

extern "C" {
void fft3_forward(float* buf, int len, int N, float* re, float* im, int stride);
void fft3_inverse(float* re, float* im, int len, int N, float* buf, int stride);
}


static Equalizer* plugin_instance = 0;


Equalizer* Equalizer::instance()
{
    return plugin_instance;
}


Equalizer::Equalizer()
	: QObject( 0 )
    , m_equalizerUi ( new Ui::Equalizer )
{
	tDebug() << Q_FUNC_INFO;

    plugin_instance = this;
    mainWidget = new QWidget();
    m_equalizerUi->setupUi( mainWidget );

    bandcount = BANDS_COUNT;
    bands = new float[bandcount];
    for ( int i = 0 ; i < bandcount ; i++ )
    {
        bands[ i ] = 1.0f;
    }
}


Equalizer::~Equalizer()
{
	tDebug() << Q_FUNC_INFO;
}


QString
Equalizer::title()
{
    return "Equalizer";
}


QWidget*
Equalizer::widget()
{
	tDebug() << Q_FUNC_INFO;

	return mainWidget;
}
void
Equalizer::setPreamp(float value)
{
  tDebug() << Q_FUNC_INFO;
    preamp = value;
}


void
Equalizer::setBand(int b, float value)
{
  tDebug() << Q_FUNC_INFO;
    bands[b] = value;
}


void
Equalizer::processData( float* samples, int nb_channels, int nb_samples )
{
    int i;
    uint32_t j;
    uint32_t k;

    static float buffer[2048 * 2 * 4] = { 0 };
    static float last_buffer[2048 * 2 * 4] = { 0 };
    static float re[2048 * 2 * 4] = { 0.0 };
    static float im[2048 * 2 * 4] = { 0.0 };
    static float last_re[2048 * 2 * 4] = { 0.0 };


    memcpy(buffer, &last_buffer[nb_samples*nb_channels], 896*nb_channels*sizeof(float));
    memcpy(&buffer[896*2], samples, nb_samples*nb_channels*sizeof(float));
    memcpy(last_buffer, buffer, 2048*nb_channels*sizeof(float));

    for ( i = 0 ; i < nb_channels ; i++ )
    {
        fft3_forward(&buffer[i], 2048, 12, re, im, nb_channels);
/*
    // LINEAR EQUALIZER
        for(j=0; j<BANDS_COUNT; j++){
            uint32_t range = 1024 / BANDS_COUNT;
            for(k=0; k<range; k++){
                re[j * range + k] *= bands[j];
                im[j * range + k] *= bands[j];
            }
        }
*/
    // LOGARITHMIC EQUALIZER
        for(j=0; j<BANDS_COUNT/4; j++){
        //  uint32_t start = (uint32_t)( powf((float)j, 1.4f) - 1.0f );
        //  uint32_t range = (uint32_t)( powf((float)j + 1.0f, 1.4f) - 1.0f );
            uint32_t start = (uint32_t)( 0.75f * ((float)j / 32.0f + 1.0f) * (float)j / 2.0f );
            uint32_t range = (uint32_t)( 0.75f * ((float)(j + 1) / 32.0f + 1.0f) * ((float)j + 1.0f) / 2.0f );
            for(k=start; k < range && k < BANDS_COUNT; k++){
                //re[k] *= max(0.0f, min(2.0f, preamp + bands[j]));
                //im[k] *= max(0.0f, min(2.0f, preamp + bands[j]));
                re[k] *= max(0.0f, min(2.0f, bands[j]));
                im[k] *= max(0.0f, min(2.0f, bands[j]));
            }
        }

        memcpy(last_re, re, 2048 * sizeof(float));

        fft3_inverse(re, im, 2048, 12, &buffer[i], nb_channels);
        
    }
    
    memcpy(samples, &buffer[448*nb_channels], sizeof(float) * nb_channels * 1152);
}

Q_EXPORT_PLUGIN2( equalizer, Equalizer )

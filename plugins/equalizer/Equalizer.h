#ifndef EQUALIZER_H
#define EQUALIZER_H

#include "DspPluginInterface.h"
#include "ui_equalizer.h"

class Equalizer : public QObject, public DspPluginInterface
{
	Q_OBJECT
	Q_INTERFACES( DspPluginInterface )

public:
	Equalizer();
	~Equalizer();
    QString title();
	QWidget* widget();
	void processData( float* samples, int nb_channels, int nb_samples );

    int bandCount() { return bandcount / 4; /* divide by 4 only with logarithmic */ }
    float* getBands() { return bands; }
    void setBand(int b, float v);

    static Equalizer* instance();

public slots:
    void reset();
    void setPreamp(int v);

private:
    Ui::Equalizer* m_equalizerUi;
    QWidget* mainWidget;

    float preamp;
    float* bands;
    int bandcount;
};

#endif // EQUALIZER_H

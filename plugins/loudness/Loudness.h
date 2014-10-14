#ifndef LOUDNESS_H
#define LOUDNESS_H

#include "DspPluginInterface.h"
#include "ui_loudness.h"

#define LP_SIZE 445
#define HP_SIZE 27

class Loudness : public QObject, public DspPluginInterface
{
	Q_OBJECT
	Q_INTERFACES( DspPluginInterface )

public:
	Loudness();
	~Loudness();
    QString title();
	QWidget* widget();
	void processData( float* samples, int nb_channels, int nb_samples );

    static Loudness* instance();

public slots:
    void changeBass( int value );
    void changeTreble( int value );

private:
    void FirFixed( float* buffer, int len, float* coeffs, int coeffslen, float level );

    Ui::Loudness* m_loudnessUi;
    QWidget* mainWidget;

    int m_basslevel;
    int m_treblelevel;

    static float f_lowpass[LP_SIZE];
    static float f_highpass[HP_SIZE];
};

#endif // LOUDNESS_H

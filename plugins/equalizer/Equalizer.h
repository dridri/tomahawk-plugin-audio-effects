#ifndef EQUALIZER_H
#define EQUALIZER_H

#include "DspPluginInterface.h"

class Equalizer : public QObject, public DspPluginInterface
{
	Q_OBJECT
	Q_INTERFACES( DspPluginInterface )

public:
	Equalizer();
	~Equalizer();
	QWidget* widget();
	void processData( float* samples, int nb_channels, int nb_samples );

private:

};

#endif // EQUALIZER_H

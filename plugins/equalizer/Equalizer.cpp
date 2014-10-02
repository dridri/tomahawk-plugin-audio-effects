#include <QWidget>
#include <QtPlugin>

#include <utils/Logger.h>

#include "Equalizer.h"


Equalizer::Equalizer()
	:QObject( 0 )
{
	tDebug() << Q_FUNC_INFO;
}


Equalizer::~Equalizer()
{
	tDebug() << Q_FUNC_INFO;
}


QWidget*
Equalizer::widget()
{
	tDebug() << Q_FUNC_INFO;

	return 0;
}


void
Equalizer::processData( float* samples, int nb_channels, int nb_samples )
{
	tDebug() << Q_FUNC_INFO;
}

Q_EXPORT_PLUGIN2( equalizer, Equalizer )

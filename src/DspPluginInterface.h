#ifndef DSPPLUGININTERFACE_H
#define DSPPLUGININTERFACE_H

#include <QWidget>

class DspPluginInterface
{
public:
	virtual ~DspPluginInterface(){}
	virtual QWidget* widget() = 0;
    virtual QString title() = 0;
	virtual void processData( float* samples, int nb_channels, int nb_samples ) = 0;

private:
};

Q_DECLARE_INTERFACE( DspPluginInterface, "org.tomahawk-player.AudioFilter.AudioFilterPlugin" )

#endif // DSPPLUGININTERFACE_H

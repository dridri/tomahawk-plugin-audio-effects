#ifndef DSPPLUGIN_H
#define DSPPLUGIN_H

#include <ViewPagePlugin.h>
#include <ViewPageLazyLoader.h>
#include <ViewPage.h>
#include <utils/Logger.h>

#include "DspWidget.h"
#include "DspPluginInterface.h"

namespace Tomahawk
{

namespace Widgets
{

class DspPlugin : public ViewPageLazyLoader<DspWidget>
{
	Q_PLUGIN_METADATA( IID "org.tomahawk-player.Player.ViewPagePlugin" )
	Q_OBJECT
	Q_INTERFACES( Tomahawk::ViewPagePlugin )

public:
	DspPlugin();
	virtual ~DspPlugin();

	virtual const QString defaultName();
	virtual QString title() const;
	virtual QString description() const;
	virtual const QString pixmapPath() const;

    QVector < DspPluginInterface* >* plugins();
	static DspPlugin* instance();

private:
	static void DSPEntry( float* samples, int nb_channels, int nb_samples );
	void DSP( float* samples, int nb_channels, int nb_samples );

	QVector < DspPluginInterface* > m_plugins;
};

}

}

#endif // DSPPLUGIN_H

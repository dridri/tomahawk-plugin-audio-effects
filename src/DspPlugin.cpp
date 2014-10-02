#include <QCoreApplication>
#include <QPluginLoader>
#include <QDir>
#include <ViewManager.h>

#include "DspPlugin.h"
#include "DspWidget.h"

#include <stdint.h>
#include <math.h>


static Tomahawk::Widgets::DspPlugin* plugin_instance = 0;


Tomahawk::Widgets::DspPlugin* Tomahawk::Widgets::DspPlugin::instance()
{
	return plugin_instance;
}


Tomahawk::Widgets::DspPlugin::DspPlugin()
	: plugins ( QVector < DspPluginInterface* >() )
{
	tDebug() << Q_FUNC_INFO;
	plugin_instance = this;

	AudioEngine::instance()->setDspCallback( &Tomahawk::Widgets::DspPlugin::DSPEntry );

	QDir dir( QDir::currentPath() );
	QFileInfoList list = dir.entryInfoList();
	for ( int i = 0 ; i < list.size() ; i++ ) {
		QString filename = list.at( i ).fileName();
		if ( filename.startsWith( "libtomahawk_filter_" ) ) {
			filename = dir.absolutePath() + "/" + filename;
			tDebug() << "Audio filter plugin : " << filename;
			QPluginLoader loader ( filename );
			DspPluginInterface* intf = qobject_cast<DspPluginInterface*>( loader.instance() );
			if ( intf != 0 ) {
				plugins.append( intf );
			}
		}
	}
}


Tomahawk::Widgets::DspPlugin::~DspPlugin()
{
	tDebug() << Q_FUNC_INFO;
}


const QString
Tomahawk::Widgets::DspPlugin::defaultName()
{
	tDebug() << Q_FUNC_INFO;
	return "dsp";
}


QString
Tomahawk::Widgets::DspPlugin::title() const
{
	tDebug() << Q_FUNC_INFO;
	return "Audio Effects";
}


QString
Tomahawk::Widgets::DspPlugin::description() const
{
	tDebug() << Q_FUNC_INFO;
	return QString();
}


const QString
Tomahawk::Widgets::DspPlugin::pixmapPath() const
{
	tDebug() << Q_FUNC_INFO;
	return ( RESPATH "images/eq_icon.png" );
}


void
Tomahawk::Widgets::DspPlugin::DSPEntry( float* samples, int nb_channels, int nb_samples )
{
	Tomahawk::Widgets::DspPlugin::instance()->DSP(samples, nb_channels, nb_samples);
}


void
Tomahawk::Widgets::DspPlugin::DSP( float* samples, int nb_channels, int nb_samples )
{
	for ( int i = 0 ; i < plugins.count() ; i++ ) {
		plugins.at( i )->processData( samples, nb_channels, nb_samples );
	}
}


Q_EXPORT_PLUGIN2( Tomahawk::ViewPagePlugin, Tomahawk::Widgets::DspPlugin )

#ifndef DSPWIDGET_H
#define DSPWIDGET_H

#include <ViewPage.h>
#include <utils/ImageRegistry.h>
#include <audio/AudioEngine.h>
#include <phonon/Path>
#include <phonon/Effect>

#include <QWidget>
#include <QPixmap>
#include <QResizeEvent>
#include <QShowEvent>
#include <QHideEvent>

#include "ui_effects.h"

class ViWidget;

class DspWidget : public QWidget, public Tomahawk::ViewPage
{
	Q_OBJECT

public:
	DspWidget( QWidget *parent = 0 );
	~DspWidget();

	bool jumpToCurrentTrack() { return false; }
	QString description() const { return QString("dsp"); }
	QString title() const{ return QString("Audio Effects"); }
	QPixmap pixmap() const { return ImageRegistry::instance()->pixmap( RESPATH "images/eq_icon.png", QSize( 0, 0 ) ); }
	Tomahawk::playlistinterface_ptr playlistInterface() const { return Tomahawk::playlistinterface_ptr(); }
	QWidget* widget(){ return this; }
	static bool canRun(){ return true; }
	void setWidget( QWidget* w );

public slots:
	void enable( bool en );
/*
protected:
	void resizeEvent(QResizeEvent* event);
	void paintEvent(QPaintEvent* ){;}//Will be taken Care by the Rendering thread
	void hideEvent(QHideEvent* ){;}
	void showEvent(QShowEvent* ){;}
*/
private:
	Ui::Effects* m_effectsUi;
};
#endif // DSPWIDGET_H

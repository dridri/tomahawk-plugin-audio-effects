#include <utils/Logger.h>
#include <QPainter>
#include <QToolTip>
#include <iostream>

#include "DspPlugin.h"
#include "DspWidget.h"
#include "DspGraph.h"

DspGraph::DspGraph( QWidget* parent )
	: QWidget( parent )
	, tooltip( new QLabel( this ) )
{
	tDebug() << Q_FUNC_INFO;

	setMouseTracking( true );
	tooltip->setVisible( false );
	last_x = -1;
	last_y = -1;
}


DspGraph::~DspGraph()
{
	tDebug() << Q_FUNC_INFO;
}


void DspGraph::paintEvent( QPaintEvent* e )
{
	tDebug() << Q_FUNC_INFO;

	Q_UNUSED( e );
	QPainter qp( this );

    int width = this->geometry().width();
    int height = this->geometry().height();

    qp.fillRect( 0, 0, width, height, QBrush(palette().color(QPalette::Base)) );
    qp.setPen( QPen( palette().color(QPalette::Text), 1, Qt::SolidLine ) );

    if ( boxes.count() == 0 ) {
        QVector < DspPluginInterface* >* plugins = Tomahawk::Widgets::DspPlugin::instance()->plugins();
        for ( int i = 0 ; i < plugins->count() ; i++ ) {
            Box box;
            box.x = ( box_width + 16 ) / plugins->count();
            box.y = 42;
            box.w = qp.fontMetrics().width( plugins->at( i )->title() );
            box.h = qp.font().pixelSize() > 0 ? qp.font().pixelSize() : qp.font().pointSize();
            box.plugin = plugins->at( i );
            boxes.append( box );
        }
    }

    for ( int i = 0 ; i < boxes.count() ; i++ ) {
        int x = boxes.at( i ).x;
        int y = boxes.at( i ).y;
        int w = boxes.at( i ).w;
        int h = boxes.at( i ).h;
        std::cout << x << ", " << y << ", " << w << ", " << h << "\n";
        qp.drawRoundedRect( x, y, 1.5 * w, 3 * h, 4, 4 );
        qp.drawText( x + ( 1.5 * w ) / 2 - w / 2, y + 2 * ( ( 3 * h ) / 2 - h / 2 ), boxes.at( i ).plugin->title() );
    }
}


void DspGraph::mousePressEvent( QMouseEvent* e )
{
	tDebug() << Q_FUNC_INFO;


    for ( int i = 0 ; i < boxes.count() ; i++ ) {
        int x = boxes.at( i ).x;
        int y = boxes.at( i ).y;
        int w = boxes.at( i ).w;
        int h = boxes.at( i ).h;
        if ( e->x() >= x && e->y() >= y && e->x() <= x + w && e->y() <= y + h ) {
            Tomahawk::Widgets::DspPlugin::instance()->widget()->setWidget( boxes.at( i ).plugin->widget() );
        }
    }
	mouseMoveEvent(e);
}


void DspGraph::mouseReleaseEvent( QMouseEvent* e )
{
	tDebug() << Q_FUNC_INFO;

	last_x = -1;
	last_y = -1;
}


void DspGraph::mouseMoveEvent( QMouseEvent* e )
{
	tDebug() << Q_FUNC_INFO;
}


void DspGraph::leaveEvent( QEvent* event )
{
	tDebug() << Q_FUNC_INFO;

	tooltip->hide();
}

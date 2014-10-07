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
	, boxes ( QVector< Box > () )
{
	tDebug() << Q_FUNC_INFO;

	setMouseTracking( true );
	tooltip->setVisible( false );
	last_x = -1;
	last_y = -1;
	current_box = -1;
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

    Box box;
    int width = this->geometry().width();
    int height = this->geometry().height();

    qp.fillRect( 0, 0, width, height, QBrush(palette().color(QPalette::Base)) );
    qp.setPen( QPen( palette().color(QPalette::Text), 1, Qt::SolidLine ) );

    if ( boxes.count() == 0 ) {
		int x = 16;

        box.x = x;
        box.y = 42;
        box.w = qp.fontMetrics().width( "Input" );
        box.h = qp.font().pixelSize() > 0 ? qp.font().pixelSize() : qp.font().pointSize();
		box.title = "Input";
        box.plugin = 0;
        boxes.append( box );
		x += 1.5 * box.w + 16;

        box.x = x;
        box.y = 42;
        box.w = qp.fontMetrics().width( "MilkDrop" );
        box.h = qp.font().pixelSize() > 0 ? qp.font().pixelSize() : qp.font().pointSize();
		box.title = "MilkDrop";
        box.plugin = 0;
        boxes.append( box );
		x += 1.5 * box.w + 16;

        QVector < DspPluginInterface* >* plugins = Tomahawk::Widgets::DspPlugin::instance()->plugins();
        for ( int i = 0 ; i < plugins->count() ; i++ ) {
			tDebug() << "x : " << x;
            box.x = x;
            box.y = 42;
            box.w = qp.fontMetrics().width( plugins->at( i )->title() );
            box.h = qp.font().pixelSize() > 0 ? qp.font().pixelSize() : qp.font().pointSize();
			box.title = plugins->at( i )->title();
            box.plugin = plugins->at( i );
            boxes.append( box );
			x += 1.5 * box.w + 16;
        }

        box.x = x;
        box.y = 42;
        box.w = qp.fontMetrics().width( "Output" );
        box.h = qp.font().pixelSize() > 0 ? qp.font().pixelSize() : qp.font().pointSize();
		box.title = "Output";
        box.plugin = 0;
        boxes.append( box );
		x += 1.5 * box.w + 16;
    }

    for ( int i = 0 ; i < boxes.count() ; i++ ) {
        int x = boxes.at( i ).x;
        int y = boxes.at( i ).y;
        int w = boxes.at( i ).w;
        int h = boxes.at( i ).h;
        std::cout << x << ", " << y << ", " << w << ", " << h << "\n";

		if ( current_box == i ) {
			qp.setPen( QPen( palette().color(QPalette::Mid), 1, Qt::SolidLine ) );
		}
        qp.drawRoundedRect( x, y, 1.5 * w, 3 * h, 4, 4 );
		qp.setPen( QPen( palette().color(QPalette::Text), 1, Qt::SolidLine ) );
        qp.drawText( x + ( 1.5 * w ) / 2 - w / 2, y + 2 * ( ( 3 * h ) / 2 - h / 2 ), boxes.at( i ).title );
		if ( i > 0 ) {
			qp.drawLine( boxes.at( i - 1 ).x + 1.5 * boxes.at( i - 1 ).w, 42 + 3 * boxes.at( i ).h / 2, boxes.at( i ).x, 42 + 3 * boxes.at( i ).h / 2 );
		}
    }
}


void DspGraph::mousePressEvent( QMouseEvent* e )
{
    for ( int i = 0 ; i < boxes.count() ; i++ ) {
        int x = boxes.at( i ).x;
        int y = boxes.at( i ).y;
        int w = 1.5 * boxes.at( i ).w;
        int h = 3 * boxes.at( i ).h;
		tDebug() << "Box " << i << " : " << boxes.at( i ).title;
        if ( e->x() >= x && e->y() >= y && e->x() <= x + w && e->y() <= y + h ) {
			current_box = i;
			repaint();
			if ( boxes.at( i ).plugin ) {
				Tomahawk::Widgets::DspPlugin::instance()->widget()->setWidget( boxes.at( i ).plugin->widget() );
			} else {
				Tomahawk::Widgets::DspPlugin::instance()->widget()->setWidget( 0 );
			}
        }
    }
	mouseMoveEvent(e);
}


void DspGraph::mouseReleaseEvent( QMouseEvent* e )
{
	last_x = -1;
	last_y = -1;
}


void DspGraph::mouseMoveEvent( QMouseEvent* e )
{
}


void DspGraph::leaveEvent( QEvent* event )
{
	tooltip->hide();
}

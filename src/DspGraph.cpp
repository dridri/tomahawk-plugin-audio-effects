#include <utils/Logger.h>
#include <QPainter>
#include <QToolTip>

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

	int i;
	int width = this->geometry().width();
	int height = this->geometry().height();

	qp.fillRect( 0, 0, width, height, QBrush(palette().color(QPalette::Base)) );
	QPen pen( palette().color(QPalette::Button), 1, Qt::SolidLine );  
	qp.setPen( pen );
}


void DspGraph::mousePressEvent( QMouseEvent* e )
{
	tDebug() << Q_FUNC_INFO;

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

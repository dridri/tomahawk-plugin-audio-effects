#include <utils/Logger.h>
#include <QPainter>
#include <QToolTip>

#include "Equalizer.h"
#include "GraphicEq.h"

GraphicEq::GraphicEq(QWidget* parent)
	: QWidget(parent)
	, tooltip(new QLabel(this))
{
	last_x = -1;
	last_y = -1;
	setMouseTracking(true);
	tooltip->setVisible(false);
}

GraphicEq::~GraphicEq()
{
}

void GraphicEq::paintEvent(QPaintEvent* e)
{
	Q_UNUSED(e);
	QPainter qp(this);

	int i;
	int width = this->geometry().width();
	int height = this->geometry().height();

	qp.fillRect(0, 0, width, height, QBrush(QColor(40, 40, 40)));

	QPen pen(QColor(140, 150, 180), 1, Qt::SolidLine);  
	qp.setPen(pen);

	for ( i = 0 ; i < width ; i++ )
	{
		int y = ((float)height * Equalizer::instance()->getBands()[(i * Equalizer::instance()->bandCount() / width)]);
		qp.drawLine(i, height - y / 2, i, height);
	}
}

void GraphicEq::setByXY(int x, int y)
{
	/*
	 * x = 1.028^x - 1
	 */
	int width = this->geometry().width();
	int height = this->geometry().height();
	if ( x >= 0 && x < width && y >= 0 && y < height )
	{
		x = x * Equalizer::instance()->bandCount() / width;
		y = y * 256 / height;
		y = -(y - 128);
		float v = 0.0;
		if(y >= 0){
			v = ((float)y + 128.0) / 128.0;
		}else{
			v = 1.0 + (((float)y) / 128.0);
		}
		Equalizer::instance()->setBand(x, v);
	}
}

void GraphicEq::mousePressEvent(QMouseEvent* e)
{
	mouseMoveEvent(e);
}

void GraphicEq::mouseReleaseEvent(QMouseEvent* e)
{
	last_x = -1;
	last_y = -1;
}

void GraphicEq::mouseMoveEvent(QMouseEvent* e)
{
	float freq = (float)( e->x() * Equalizer::instance()->bandCount() / geometry().width() );
	freq = (freq / 32.0f + 1.0f) * freq;
	freq = 0.75f * freq * 22050.0f / 1024.0f / 2.0f;
	tooltip->setParent(this);
	tooltip->setText(QString("%1 Hz").arg((int)freq));
	tooltip->move( e->x() + 2, e->y() - tooltip->geometry().height() * 1.25 );
	tooltip->resize(tooltip->font().pointSize() * 32, tooltip->font().pointSize() + 8);
	tooltip->show();

	if(e->buttons() == Qt::LeftButton)
	{
		if(last_x >= 0 && last_y >= 0)
		{
			int x = 0;
			int xstart = (e->x() - last_x) < 0 ? (e->x() - last_x) : 0;
			int xend = (e->x() - last_x) < 0 ? 0 : (e->x() - last_x);
			int xstep = xstart < xend ? 1 : -1;
			for(x = xstart ; x != xend ; x += xstep)
			{
				int y = e->y() + x * ((float)(e->y() - last_y) / (float)(e->x() - last_x));
				setByXY(last_x + x, y);
			}
		}else
		{
			setByXY(e->x(), e->y());
		}
		this->repaint();
		last_x = e->x();
		last_y = e->y();
	}
}

void GraphicEq::leaveEvent(QEvent* event)
{
	tooltip->hide();
}

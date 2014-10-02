#ifndef GRAPHICEQ_H
#define GRAPHICEQ_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPaintEvent>
#include <QMouseEvent>

class DspGraph : public QWidget
{
	Q_OBJECT

public:
	DspGraph( QWidget *parent = 0 );
	~DspGraph();

protected:
	void paintEvent( QPaintEvent* e );
	void mousePressEvent( QMouseEvent* e );
	void mouseReleaseEvent( QMouseEvent* e );
	void mouseMoveEvent( QMouseEvent* e );
	void leaveEvent( QEvent* event );

private:
	int last_x;
	int last_y;
	QLabel* tooltip;
};
#endif // GRAPHICEQ_H

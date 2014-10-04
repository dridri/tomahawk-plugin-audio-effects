#ifndef GRAPHICEQ_H
#define GRAPHICEQ_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPaintEvent>
#include <QMouseEvent>

class GraphicEq : public QWidget
{
	Q_OBJECT

public:
	GraphicEq( QWidget *parent = 0 );
	~GraphicEq();

protected:
	void paintEvent(QPaintEvent* e);
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	void leaveEvent(QEvent* event);

private:
	void setByXY(int x, int y);
	int last_x;
	int last_y;
	QLabel* tooltip;
};
#endif // GRAPHICEQ_H

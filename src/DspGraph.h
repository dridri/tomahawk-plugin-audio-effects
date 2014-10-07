#ifndef GRAPHICEQ_H
#define GRAPHICEQ_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPaintEvent>
#include <QMouseEvent>

class DspPluginInterface;

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
    struct Box {
        int x;
        int y;
        int w;
        int h;
		QString title;
        DspPluginInterface* plugin;
    };
	int last_x;
	int last_y;
	QLabel* tooltip;
    QVector< Box > boxes;
    int box_width;
	int current_box;
};
#endif // GRAPHICEQ_H

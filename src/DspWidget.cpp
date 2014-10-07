#include <utils/Logger.h>

#include <phonon/BackendCapabilities>
#include <phonon/Effect>
#include <phonon/EffectParameter>

#include "DspPlugin.h"
#include "DspWidget.h"
#include "DspGraph.h"
#include "ui_effects.h"


DspWidget::DspWidget( QWidget* parent )
	: QWidget( parent )
	, m_effectsUi( new Ui::Effects )
{
	tDebug() << Q_FUNC_INFO;
	m_effectsUi->setupUi( this );
}


DspWidget::~DspWidget()
{
	tDebug() << Q_FUNC_INFO;
}

/*
void DspWidget::resizeEvent(QResizeEvent* event)
{
//	tDebug() << Q_FUNC_INFO;
}
*/


void
DspWidget::enable( bool en )
{
	tDebug() << Q_FUNC_INFO;
}


void rm( QLayout* l )
{
	QLayoutItem *child;
	while ((child = l->takeAt(0)) != 0) {
		child->widget()->setParent( 0 );
		if ( child->layout() ) {
			rm( child->layout() );
		}
		l->removeWidget( child->widget() );
		l->removeItem( child );
		delete child;
	}
	l->deleteLater();
	delete l;
}


void
DspWidget::setWidget( QWidget* w )
{
    tDebug() << Q_FUNC_INFO << w;

	if ( m_effectsUi->widgetContainer->layout() ) {
		rm( m_effectsUi->widgetContainer->layout() );
	}

	QBoxLayout* layout = new QBoxLayout( QBoxLayout::LeftToRight );
	m_effectsUi->widgetContainer->setLayout( layout );

	if (!w) {
		w = new QWidget();
	}
	if ( w ) {
		m_effectsUi->widgetContainer->layout()->addWidget( w );
	}
}

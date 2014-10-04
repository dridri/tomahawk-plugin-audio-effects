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


void
DspWidget::setWidget( QWidget* w )
{
    tDebug() << Q_FUNC_INFO << w;

    QBoxLayout* layout = new QBoxLayout( QBoxLayout::LeftToRight );
    layout->addWidget( w );
    m_effectsUi->widgetContainer->setLayout( layout );
}

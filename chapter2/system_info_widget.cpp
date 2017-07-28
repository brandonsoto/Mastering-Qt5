#include "system_info_widget.h"

#include <QVBoxLayout>

using namespace QtCharts;

System_Info_Widget::System_Info_Widget(QWidget *parent, const int start_dely_ms, const int update_series_delay_ms)
    : QWidget( parent ),
      chartview_( this )
{
    // set up timer
    refresh_timer_.setInterval( update_series_delay_ms );
    connect( &refresh_timer_, &QTimer::timeout, this, &System_Info_Widget::update_series );
    QTimer::singleShot( start_dely_ms, [this]() { refresh_timer_.start(); } );

    // set up chartview
    chartview_.setRenderHint( QPainter::Antialiasing );
    chartview_.chart()->legend()->setVisible( true );

    // set up layout
    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->addWidget( &chartview_ );
    setLayout( layout );
}

QtCharts::QChartView &System_Info_Widget::chartview()
{
    return chartview_;
}

#include "cpu_widget.h"
#include "system_info.h"

using namespace QtCharts;

CPU_Widget::CPU_Widget(QWidget *parent)
    : System_Info_Widget( parent ),
      series_( new QPieSeries( this ) )
{
    // set up series
    series_->setHoleSize( 0.35 );
    series_->append( "CPU Free", 100.0 );

    // set up chart
    QChart* chart = chartview().chart();
    chart->addSeries( series_ );
    chart->setTitle( "CPU average load" );
}

void CPU_Widget::update_series()
{
    const auto cpu_load_average = System_Info::instance().cpu_load_average();
    series_->clear();
    series_->append( "Load", cpu_load_average );
    series_->append( "Free", 100.0 - cpu_load_average );
}


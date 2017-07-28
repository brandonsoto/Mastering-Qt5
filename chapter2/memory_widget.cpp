#include "memory_widget.h"
#include "system_info.h"

#include <QtCharts/QAreaSeries>
#include <QLinearGradient>
#include <QPen>

using namespace QtCharts;

constexpr int CHART_X_RANGE_COUNT = 50;
constexpr int CHART_X_RANGE_MAX = CHART_X_RANGE_COUNT - 1;
constexpr int COLOR_DARK_BLUE = 0x209fdf;
constexpr int COLOR_LIGHT_BLUE = 0xbfdfef;
constexpr int PEN_WIDTH = 3;

Memory_Widget::Memory_Widget(QWidget *parent)
    : System_Info_Widget(parent),
      series_{ new QLineSeries{ this } },
      point_position_x_{ 0 }
{
    QPen pen( COLOR_DARK_BLUE );
    pen.setWidth( PEN_WIDTH );

    QLinearGradient gradient( QPointF( 0, 0 ), QPointF( 0, 1 ) );
    gradient.setColorAt( 1.0, COLOR_DARK_BLUE );
    gradient.setColorAt( 0.0, COLOR_LIGHT_BLUE );
    gradient.setCoordinateMode( QGradient::ObjectBoundingMode );

    QAreaSeries* area_series = new QAreaSeries(series_);
    area_series->setBrush( gradient );
    area_series->setPen( pen );

    QChart* chart = chartview().chart();
    chart->addSeries( area_series );
    chart->setTitle( "Memory used" );
    chart->createDefaultAxes();
    chart->axisX()->setVisible( false );
    chart->axisX()->setRange( 0, CHART_X_RANGE_MAX );
    chart->axisY()->setRange( 0, 100 );
}

void Memory_Widget::update_series()
{
    const double memory_used = System_Info::instance().memory_used();
    series_->append( point_position_x_++, memory_used );

    if ( series_->count() > CHART_X_RANGE_COUNT ) {
        QChart* chart = chartview().chart();
        chart->scroll( chart->plotArea().width() / CHART_X_RANGE_MAX, 0 );
        series_->remove( 0 );
    }

}

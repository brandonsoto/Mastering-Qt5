#ifndef SYSTEM_INFO_WIDGET_H
#define SYSTEM_INFO_WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QtCharts/QChartView>

class System_Info_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit System_Info_Widget( QWidget *parent = nullptr,
                                 const int start_dely_ms = 500,
                                 const int update_series_delay_ms = 500 );

protected:
    QtCharts::QChartView& chartview();

protected slots:
    virtual void update_series() = 0;

private:
    QTimer refresh_timer_;
    QtCharts::QChartView chartview_;


};

#endif // SYSTEM_INFO_WIDGET_H

#ifndef MEMORY_WIDGET_H
#define MEMORY_WIDGET_H

#include <QtCharts/QLineSeries>

#include "system_info_widget.h"

class Memory_Widget : public System_Info_Widget
{
    Q_OBJECT
public:
    explicit Memory_Widget(QWidget *parent = nullptr);

protected slots:
    void update_series() override;

private:
    QtCharts::QLineSeries* series_;
    qint64 point_position_x_;
};

#endif // MEMORY_WIDGET_H

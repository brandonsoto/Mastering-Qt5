#ifndef CPU_WIDGET_H
#define CPU_WIDGET_H

#include <QtCharts/QPieSeries>

#include "system_info_widget.h"

class CPU_Widget : public System_Info_Widget
{
    Q_OBJECT

public:
    explicit CPU_Widget( QWidget* parent = nullptr );

protected slots:
    void update_series() override;

private:
    QtCharts::QPieSeries* series_;
};

#endif // CPU_WIDGET_H

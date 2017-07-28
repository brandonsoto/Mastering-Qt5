#ifndef LINUX_SYSTEM_INFO_H
#define LINUX_SYSTEM_INFO_H

#include <QtGlobal>
#include <QVector>

#include "system_info.h"

class Linux_System_Info : public System_Info
{
public:
    Linux_System_Info() = default;
    ~Linux_System_Info() = default;

    void init() override;
    double cpu_load_average() override;
    double memory_used() override;

private:
    QVector<qulonglong> cpu_raw_data();
    QVector<qulonglong> cpu_load_last_values_{};
};

#endif // LINUX_SYSTEM_INFO_H

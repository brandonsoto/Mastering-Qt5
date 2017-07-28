#ifndef WINDOWS_SYSTEM_INFO_H
#define WINDOWS_SYSTEM_INFO_H

#include <QVector>
#include <QtGlobal>

#include "system_info.h"

using FILETIME = struct _FILETIME;

class Windows_System_Info : public System_Info
{
public:
    Windows_System_Info() = default;
    ~Windows_System_Info() = default;

    void init() override;
    double cpu_load_average() override;
    double memory_used() override;

private:
    QVector<qulonglong> cpu_raw_data();
    qulonglong convert_file_time( const FILETIME& filetime ) const;
    QVector<qulonglong> cpu_load_last_values_{};

};

#endif // WINDOWS_SYSTEM_INFO_H

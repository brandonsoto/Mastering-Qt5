#include "windows_system_info.h"
#include <windows.h>

void Windows_System_Info::init()
{
    cpu_load_last_values_ = cpu_raw_data();
}

double Windows_System_Info::cpu_load_average()
{
    const auto first_sample = cpu_load_last_values_;
    const auto second_sample = cpu_raw_data();
    cpu_load_last_values_ = second_sample;

    qulonglong current_idle = second_sample[0] - first_sample[0];
    qulonglong curent_kernel = second_sample[1] - first_sample[1];
    qulonglong current_user = second_sample[2] - first_sample[2];
    qulonglong current_system = current_kernel + current_user;

    const double percent = (current_system - current_idle ) * 100.0 / current_system;
    return qBound( 0.0, percent, 100.0 );

}

double Windows_System_Info::memory_used()
{
    MEMORYSTATUSEX memory_status;
    memory_status.dwLength = sizeof( MEMORYSTATUSEX );
    GlobalMemoryStatusEx( &memory_status );
    qulonglong memory_physical_used = memory_status.ullTotalPhys - memory_status.ullAvailPhys;
    return static_cast<double>( memory_physical_used ) / static_cast<double>( memory_status.ullTotalPhys * 100.0 );

}

QVector<qulonglong> Windows_System_Info::cpu_raw_data()
{
    FILETIME idle_time;
    FILETIME kernel_time;
    FILETIME user_time;

    GetSystemTimes( &idle_time, &kernel_time, &user_time );

    QVector<qulonglong> raw_data{};
    raw_data.append( convert_file_time( idle_time ) );
    raw_data.append( convert_file_time( kernel_time ) );
    raw_data.append( convert_file_time( user_time ) );
    return raw_data;
}

qulonglong Windows_System_Info::convert_file_time(const FILETIME &filetime) const
{
    ULARGE_INTEGER large_int;
    large_int.LowPart = filetime.dwLowDateTime;
    large_int.HighPart = filetime.dwHighDateTime;
    return large_int.QuadPart;
}

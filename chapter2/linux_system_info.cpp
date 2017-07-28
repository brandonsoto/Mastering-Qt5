#include "linux_system_info.h"

#include <sys/types.h>
#include <sys/sysinfo.h>

#include <QFile>

void Linux_System_Info::init()
{
    cpu_load_last_values_ = cpu_raw_data();
}

double Linux_System_Info::cpu_load_average()
{
    const auto first_sample = cpu_load_last_values_;
    const auto second_sample = cpu_raw_data();
    cpu_load_last_values_ = second_sample;

    const double overall = (second_sample[0] - first_sample[0])
            + (second_sample[1] - first_sample[1])
            + (second_sample[2] - first_sample[2]);

    const double total = overall + (second_sample[3] - first_sample[3]);
    const double percent = (overall / total) * 100.0;
    return qBound( 0.0, percent, 100.0 );
}

double Linux_System_Info::memory_used()
{
    struct sysinfo mem_info;
    sysinfo( &mem_info );

    qulonglong total_memory = mem_info.totalram;
    total_memory += mem_info.totalswap;
    total_memory *= mem_info.mem_unit;

    qulonglong total_memory_used = mem_info.totalram - mem_info.freeram;
    total_memory_used += mem_info.totalswap - mem_info.freeswap;
    total_memory_used *= mem_info.mem_unit;

    const double percent = static_cast<double>( total_memory_used ) / static_cast<double>( total_memory * 100.0 );
    return qBound( 0.0, percent, 100.0 );
}

QVector<qulonglong> Linux_System_Info::cpu_raw_data()
{
    QFile file{ "/proc/stat" };
    file.open( QIODevice::ReadOnly );

    const auto line = file.readLine();
    file.close();

    qulonglong total_user = 0;
    qulonglong total_user_nice = 0;
    qulonglong total_system = 0;
    qulonglong total_idle = 0;

    std::sscanf( line.data(), "cpu %llu %llu %llu %llu", &total_user, &total_user_nice, &total_system, &total_idle );

    QVector<qulonglong> raw_data{};
    raw_data.append( total_user );
    raw_data.append( total_user_nice );
    raw_data.append( total_system );
    raw_data.append( total_idle );
    return raw_data;
}

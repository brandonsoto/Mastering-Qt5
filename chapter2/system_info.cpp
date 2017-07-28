#include "system_info.h"

#include <QtGlobal>

#ifdef Q_OS_WIN
    #include "windows_system_info.h"
#elif defined(Q_OS_LINUX)
    #include "linux_system_info.h"
#endif

System_Info &System_Info::instance()
{
    #ifdef Q_OS_WIN
        static Windows_System_Info singleton{};
    #elif defined(Q_OS_LINUX)
        static Linux_System_Info singleton{};
    #endif

    return singleton;
}

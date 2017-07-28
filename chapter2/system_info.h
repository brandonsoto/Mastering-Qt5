#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H


class System_Info
{
public:
    System_Info( const System_Info& info ) = delete;
    System_Info& operator=( const System_Info& info ) = delete;

    static System_Info& instance();
    virtual ~System_Info() = default;

    virtual void init() = 0;
    virtual double cpu_load_average() = 0;
    virtual double memory_used() = 0;

protected:
    System_Info() = default;

};

#endif // SYSTEM_INFO_H

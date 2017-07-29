#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <QString>

#include <memory>

#include "album_database.h"
#include "picture_database.h"

class QSqlDatabase;

const QString DATABASE_FILENAME = "gallery.db";

class Database_Manager {
public:
    static Database_Manager& instance();
    ~Database_Manager();

protected:
    Database_Manager( const QString& path = DATABASE_FILENAME );
//    Database_Manager& operator=( const Database_Manager& rhs );

private:
    std::unique_ptr<QSqlDatabase> database_;

public:
    const Album_Database album_database_;
    const Picture_Database picture_database_;

};

#endif // DATABASE_MANAGER_H

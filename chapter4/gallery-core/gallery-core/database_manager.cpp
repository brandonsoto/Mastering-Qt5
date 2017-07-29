#include "database_manager.h"

#include <QSqlDatabase>

Database_Manager &Database_Manager::instance()
{
    static Database_Manager singleton{};
    return singleton;
}

Database_Manager::~Database_Manager()
{
   database_->close();
}

Database_Manager::Database_Manager(const QString &path)
    : database_{ std::make_unique<QSqlDatabase>( QSqlDatabase::addDatabase( "QSQLITE" ) ) },
      album_database_{ *database_ },
      picture_database_{ *database_ }
{
   database_->setDatabaseName( path );
   database_->open();

   album_database_.init();
}

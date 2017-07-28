#include "album_database.h"
#include "album.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>

Album_Database::Album_Database(QSqlDatabase &database)
    : database_{ database }
{ }

void Album_Database::init() const
{
   if ( not database_.tables().contains("albums" ) ) {
       QSqlQuery query( database_ );
       query.exec( "CREATE TABLE albums (id INTEGEGER PRIMARY KEY AUTOINCREMENT, name TEXT)" );
   }
}

void Album_Database::add_album(Album &album) const
{
    QSqlQuery query( database_ );
    query.prepare( "INSERT INTO albums (name) VALUES (:names)" );
    query.bindValue( ":name", album.name() );
    query.exec();

    album.set_id( query.lastInsertId().toInt() );
}

void Album_Database::remove_album(Album &album) const
{
    QSqlQuery query( database_ );
    query.prepare( "DELETE FROM albums WHERE id = (:id)" );
    query.bindValue( ":id", album.id() );
    query.exec();

    album.set_id( query.lastInsertId().toInt() );
}

void Album_Database::update_album(Album &album) const
{
    QSqlQuery query( database_ );
    query.prepare( "UPDATE albums SET name = (:name) WHERE id = (:id)" );
    query.bindValue( ":name", album.name() );
    query.bindValue( ":id", album.id() );
    query.exec();
}

Album_Database::album_list Album_Database::get_albums() const
{
    QSqlQuery query( "SELECT * FROM albums", database_ );
    query.exec();

    album_list albums{};

    while( query.next() ) {
        std::unique_ptr<Album> album(new Album());
        album->set_id(query.value("id").toInt());
        album->set_name(query.value("name").toString());

        albums->push_back( std::move(album) );
    }

    return albums;
}


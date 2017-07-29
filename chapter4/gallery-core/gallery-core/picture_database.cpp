#include "picture_database.h"
#include "picture.h"

#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>

Picture_Database::Picture_Database(QSqlDatabase &database)
    : database_{ database }
{ }

void Picture_Database::init() const
{
   if ( not database_.tables().contains("pictures" ) ) {
       QSqlQuery query( database_ );
       query.exec( QString( "CREATE TABLE pictures" )
                   + " (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   + "album_id INTEGER, "
                   + "url TEXT) " );
   }
}

void Picture_Database::add_picture_in_album(int albumId, Picture& picture) const
{
    QSqlQuery query(database_);
    query.prepare(QString("INSERT INTO pictures")
        + " (album_id, url)"
        + " VALUES ("
        + ":album_id, "
        + ":url"
        + ")");
    query.bindValue(":album_id", albumId);
    query.bindValue(":url", picture.file_url());
    query.exec();

    picture.set_id(query.lastInsertId().toInt());
    picture.set_album_id(albumId);
}

void Picture_Database::remove_picture(int id) const
{
    QSqlQuery query(database_);
    query.prepare("DELETE FROM pictures WHERE id = (:id)");
    query.bindValue(":id", id);
    query.exec();
}

void Picture_Database::remove_pictures_for_album(int albumId) const
{
    QSqlQuery query(database_);
    query.prepare("DELETE FROM pictures WHERE album_id = (:album_id)");
    query.bindValue(":album_id", albumId);
    query.exec();
}

Picture_Database::picture_list Picture_Database::get_pictures_for_album(int albumId) const
{
    QSqlQuery query(database_);
    query.prepare("SELECT * FROM pictures WHERE album_id = (:album_id)");
    query.bindValue(":album_id", albumId);
    query.exec();

    picture_list pictures{};

    while(query.next()) {
        std::unique_ptr<Picture> picture{ std::make_unique<Picture>() };
        picture->set_id(query.value("id").toInt());
        picture->set_album_id(query.value("album_id").toInt());
        picture->set_file_url(query.value("url").toString());

        pictures->push_back(std::move(picture));
    }

    return pictures;
}

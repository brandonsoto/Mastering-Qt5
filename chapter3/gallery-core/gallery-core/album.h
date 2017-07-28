#ifndef ALBUM_H
#define ALBUM_H

#include <QString>

#include "gallery-core_global.h"

class GALLERYCORESHARED_EXPORT Album
{
public:
    explicit Album( const QString& name = "" ) : database_id_{ -1 }, name_{ name } { }

    int id() const { return database_id_; }
    void set_id( const int id ) { database_id_ = id; }
    QString name() const { return name_; }
    void set_name( const QString& name ) { name_ = name; }

private:
    int database_id_;
    QString name_;
};

#endif // ALBUM_H

#ifndef PICTURE_H
#define PICTURE_H

#include <QUrl>
#include <QString>

#include "gallery-core_global.h"

class GALLERYCORESHARED_EXPORT Picture
{
public:
    explicit Picture( const QString& file_path = "" )
        : Picture{ QUrl::fromLocalFile( file_path ) } { }

    explicit Picture( const QUrl& file_url )
        : id_{ -1 }, album_id_{ -1 }, file_url_{ file_url } { }

    int id() const { return id_; }
    void set_id( const int id ) { id_ = id; }

    int album_id() const { return album_id_; }
    void set_album_id( const int album_id ) { album_id_ = album_id; }

    QUrl file_url() const { return file_url_; }
    void set_file_url( const QUrl& file_url ) { file_url_ = file_url; }

private:
    int id_;
    int album_id_;
    QUrl file_url_;
};

#endif // PICTURE_H

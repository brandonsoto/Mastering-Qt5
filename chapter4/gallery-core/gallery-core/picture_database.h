#ifndef PICTURE_DATABASE_H
#define PICTURE_DATABASE_H

#include <memory>
#include <vector>

class QSqlDatabase;
class Picture;

class Picture_Database
{
public:
    using picture_list = std::unique_ptr<std::vector<std::unique_ptr<Picture>>>;

    explicit Picture_Database( QSqlDatabase& database );
    void init() const;

    void add_picture_in_album( int album_id, Picture& picture ) const;
    void remove_picture( int id ) const;
    void remove_pictures_for_album( int album_id ) const;
    void update_picture( Picture& Picture ) const;
    picture_list get_pictures_for_album( int album_id ) const;

private:
    QSqlDatabase& database_;
};

#endif // PICTURE_DATABASE_H

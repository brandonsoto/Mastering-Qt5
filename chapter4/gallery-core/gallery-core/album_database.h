#ifndef ALBUM_DATABASE_H
#define ALBUM_DATABASE_H

#include <memory>
#include <vector>

class QSqlDatabase;
class Album;

class Album_Database
{
public:
    using album_list = std::unique_ptr<std::vector<std::unique_ptr<Album>>>;

    explicit Album_Database( QSqlDatabase& database );
    void init() const;
    void add_album( Album& album ) const;
    void remove_album( int id ) const;
    void update_album( Album& album ) const;
    album_list get_albums() const;

private:
    QSqlDatabase& database_;
};

#endif // ALBUM_DATABASE_H

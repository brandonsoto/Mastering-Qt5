#include "album_model.h"

Album_Model::Album_Model(QObject *parent)
    : QAbstractListModel( parent ),
      database_{ Database_Manager::instance() },
      album_cache_{ database_.album_database_.get_albums() }
{ }

QModelIndex Album_Model::add_album(const Album &album)
{
    const int row_index = rowCount();

    // signal that rows are about to change for given indexes
    beginInsertRows( QModelIndex(), row_index, row_index );

    std::unique_ptr<Album> new_album{ std::make_unique<Album>( album ) };
    database_.album_database_.add_album( *new_album );

    album_cache_->push_back( std::move( new_album ) );

    // signal that rows have been changed
    endInsertRows();

    return index( row_index, 0 );

}

int Album_Model::rowCount(const QModelIndex & /* parent */ ) const
{
    return album_cache_->size();
}

QVariant Album_Model::data(const QModelIndex &index, int role) const
{
    if ( not is_index_valid( index ) ) {
        return QVariant{};
    }

    const Album& album = *album_cache_->at( index.row() );

    switch( role ) {
        case Roles::ROLE_ID:
            return album.id();
        case Roles::ROLE_NAME:
        case Qt::DisplayRole:
            return album.name();
        default:
            return QVariant{};
    }
}

bool Album_Model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if ( not is_index_valid( index ) || role != Roles::ROLE_NAME ) {
        return false;
    }

    Album& album = *album_cache_->at( index.row() );
    album.set_name( value.toString() );

    database_.album_database_.update_album( album );

    emit dataChanged( index, index ); // signal tht row changed for give indexes

    return true;
}

bool Album_Model::removeRows(int row, int count, const QModelIndex &parent)
{
    if ( row < 0 || row >= rowCount() || count < 0 || (row+count) > rowCount() ) {
        return false;
    }

    beginRemoveRows( parent, row, row + count - 1 );

    int count_left = count;

    while ( count_left-- ) {
        const Album& album = *album_cache_->at( row + count_left );
        database_.album_database_.remove_album( album.id() );
    }

    *album_cache_->erase( album_cache_->begin() + row, album_cache_->begin() + row + count );

    endRemoveRows();
    return true;
}

QHash<int, QByteArray> Album_Model::roleNames() const
{
    QHash<int, QByteArray> roles{};
    roles[Roles::ROLE_ID] = "id";
    roles[Roles::ROLE_NAME] = "name";
    return roles;
}

bool Album_Model::is_index_valid(const QModelIndex &index) const
{
    if ( index.row() < 0
         || index.row() >= rowCount()
         || not index.isValid() ) {
        return false;
    }

    return true;
}

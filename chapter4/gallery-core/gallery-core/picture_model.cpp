#include "picture_model.h"
#include "album_model.h"
#include "album.h"
#include "database_manager.h"
#include "picture_database.h"


Picture_Model::Picture_Model(const Album_Model &album_model, QObject *parent)
    : QAbstractListModel( parent ),
      database_{ Database_Manager::instance() },
      album_id_{ -1 },
      picture_cache_( new std::vector<std::unique_ptr<Picture>>() )
{
    connect( &album_model, &Album_Model::rowsRemoved,
             this, &Picture_Model::delete_pictures_for_album );
}

QModelIndex Picture_Model::add_picture(const Picture &picture)
{
    const int rows = rowCount();

    beginInsertRows( QModelIndex(), rows, rows );

    std::unique_ptr<Picture> new_picture{ std::make_unique<Picture>( picture ) };
    database_.picture_database_.add_picture_in_album( album_id_, *new_picture );
    picture_cache_->push_back( std::move( new_picture ) );

    endInsertRows();

    return index( rows, 0 );
}

QHash<int, QByteArray> Picture_Model::roleNames() const
{
   QHash<int, QByteArray> roles{};
   roles[Roles::ROLE_FILEPATH] = "filepath";
   return roles;
}

int Picture_Model::rowCount(const QModelIndex& /* parent */ ) const
{
    return picture_cache_->size();
}

QVariant Picture_Model::data(const QModelIndex &index, int role) const
{
    if ( not is_index_valid( index ) ) {
        return QVariant();
    }

    const Picture& picture = *picture_cache_->at( index.row() );

    switch (role) {
        case Qt::DisplayRole:
            return picture.file_url().fileName();
        case Roles::ROLE_URL:
            return picture.file_url();
        case Roles::ROLE_FILEPATH:
            return picture.file_url().toLocalFile();
        default:
            return QVariant();
    }

}

bool Picture_Model::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || row >= rowCount() || count < 0 || (row + count) > rowCount()) {
        return false;
    }

    beginRemoveRows( parent, row, row + count - 1 );

    int countLeft = count;

    while(countLeft--) {
        const Picture& picture = *picture_cache_->at(row + countLeft);
        database_.picture_database_.remove_picture( picture.id() );
    }

    picture_cache_->erase(picture_cache_->begin() + row,
                          picture_cache_->begin() + row + count);

    endRemoveRows();

    return true;
}

void Picture_Model::set_album_id(int album_id)
{
    beginResetModel();
    album_id_ = album_id;
    load_pictures( album_id_ );
    endResetModel();
}

void Picture_Model::clear_album()
{
    set_album_id( -1 );
}

void Picture_Model::delete_pictures_for_album()
{
    database_.picture_database_.remove_pictures_for_album( album_id_ );
    clear_album();
}

void Picture_Model::load_pictures(int album_id)
{
    if ( album_id_ <= 0 ) {
        picture_cache_.reset( new std::vector<std::unique_ptr<Picture>>() );
        return;
    }

    picture_cache_ = database_.picture_database_.get_pictures_for_album( album_id );
}

bool Picture_Model::is_index_valid(const QModelIndex &index) const
{
    if ( index.row() < 0 || index.row() >= rowCount() || not index.isValid() ) {
        return false;
    }

    return true;
}

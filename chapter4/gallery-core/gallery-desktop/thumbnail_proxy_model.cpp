#include "thumbnail_proxy_model.h"
#include "picture_model.h"

constexpr unsigned int THUMBNAIL_SIZE = 350;

Thumbnail_Proxy_Model::Thumbnail_Proxy_Model(QObject *parent)
    : QIdentityProxyModel( parent )
{ }

QVariant Thumbnail_Proxy_Model::data(const QModelIndex &index, int role) const
{
    if ( role != Qt::DecorationRole ) {
        return QIdentityProxyModel::data( index, role ); // calls data() in Picture_Model
    }

    QString filepath = sourceModel()->data( index, Picture_Model::Roles::ROLE_FILEPATH ).toString();
    return *thumbnails_[filepath]; // pixmap casted to QVariant
}

void Thumbnail_Proxy_Model::setSourceModel(QAbstractItemModel *source_model)
{
    QIdentityProxyModel::setSourceModel( source_model );

    if ( not source_model ) {
        return;
    }

    connect( source_model, &QAbstractItemModel::modelReset, [this](){ reload_thumbnails(); } );
    connect( source_model, &QAbstractItemModel::rowsInserted,
             [this]( const QModelIndex& /* parent */, int first, int last )
    {
        generate_thumbnails( index( first, 0), last - first + 1 );
    } );
}

Picture_Model *Thumbnail_Proxy_Model::picture_model() const
{
    return static_cast<Picture_Model*>( sourceModel() );
}

void Thumbnail_Proxy_Model::generate_thumbnails(const QModelIndex &start_index, int count)
{
    if ( not start_index.isValid() ) {
        return;
    }

    const QAbstractItemModel* model = start_index.model();
    int last_index = start_index.row() + count;

    for ( int row = start_index.row(); row < last_index; ++row ) {
        QString filepath = model->data( model->index( row, 0 ),
                                        Picture_Model::Roles::ROLE_FILEPATH ).toString();
        QPixmap pixmap( filepath );
        QPixmap* thumbnail = new QPixmap( pixmap.scaled( THUMBNAIL_SIZE,
                                                         THUMBNAIL_SIZE,
                                                         Qt::KeepAspectRatio,
                                                         Qt::SmoothTransformation ) );

        thumbnails_.insert( filepath, thumbnail );
    }

}

void Thumbnail_Proxy_Model::reload_thumbnails()
{
    qDeleteAll( thumbnails_ );
    thumbnails_.clear();
    generate_thumbnails( index( 0, 0 ), rowCount() ); // show all thumbnails
}

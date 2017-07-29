#ifndef ALBUM_MODEL_H
#define ALBUM_MODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <vector>
#include <memory>

#include "gallery-core_global.h"
#include "album.h"
#include "database_manager.h"

/***************************************************************************************************
 * model:
 *     - central point to interact with our data (the database)
 *          - requests and updates
 *     - it exposes the data to client in implementation-agnostic form
 **************************************************************************************************/

// QModelIndex = object used to locate data iwthin a model
//              - used by view to query the model

/***************************************************************************************************
 * 3 types of models:
 *     1) list - data stored in 1-D array (rows)
 *     2) table - data is stored in 2-D array (rows & columns)
 *     3) tree - data is stored in hierarchical relationship (parent/child)
 **************************************************************************************************/

class GALLERYCORESHARED_EXPORT Album_Model : public QAbstractListModel
{
    Q_OBJECT

public:
    using album_list = std::unique_ptr<std::vector<std::unique_ptr<Album>>>;

    enum Roles {
        ROLE_ID = Qt::UserRole + 1,
        ROLE_NAME
    };

    explicit Album_Model(QObject *parent = nullptr);
    QModelIndex add_album( const Album& album );

    int rowCount( const QModelIndex& parent = QModelIndex() ) const override;
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    bool setData( const QModelIndex& index, const QVariant& value, int role ) override;
    bool removeRows( int row, int count, const QModelIndex& parent ) override;
    QHash<int, QByteArray> roleNames() const override;

private:
    bool is_index_valid( const QModelIndex& index ) const;

    Database_Manager& database_; // how we communicate with data layer
    album_list album_cache_;     // cached albums; used when interacting with view
};

#endif // ALBUM_MODEL_H

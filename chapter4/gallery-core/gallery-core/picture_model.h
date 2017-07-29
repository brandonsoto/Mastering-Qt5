#ifndef PICTURE_MODEL_H
#define PICTURE_MODEL_H

#include <memory>
#include <vector>

#include <QAbstractListModel>

#include "gallery-core_global.h"
#include "picture.h"

class Album;
class Database_Manager;
class Album_Model;

class GALLERYCORESHARED_EXPORT Picture_Model : public QAbstractListModel
{
    Q_OBJECT
public:

    enum Roles {
        ROLE_URL = Qt::UserRole + 1,
        ROLE_FILEPATH
    };

    explicit Picture_Model( const Album_Model& album_model, QObject *parent = nullptr );

    QModelIndex add_picture( const Picture& picture );
    QHash<int, QByteArray> roleNames() const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool removeRows( int row, int count, const QModelIndex& parent ) override;

    void set_album_id( int album_id );
    void clear_album();

public slots:
    void delete_pictures_for_album();

private:
    void load_pictures( int album_id );
    bool is_index_valid( const QModelIndex& index ) const;

    Database_Manager& database_;
    int album_id_;
    std::unique_ptr<std::vector<std::unique_ptr<Picture>>> picture_cache_;
};

#endif // PICTURE_MODEL_H

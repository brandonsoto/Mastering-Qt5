#ifndef THUMBNAIL_PROXY_MODEL_H
#define THUMBNAIL_PROXY_MODEL_H

#include <QIdentityProxyModel>
#include <QHash>
#include <QString>
#include <QPixmap>

class Picture_Model;

// proxy models add behavior to an existing model without breaking it

class Thumbnail_Proxy_Model : public QIdentityProxyModel
{
public:
    Thumbnail_Proxy_Model( QObject* parent = nullptr );

    QVariant data( const QModelIndex& index, int role ) const override;
    void setSourceModel( QAbstractItemModel* source_model ) override;
    Picture_Model* picture_model() const;

private:
    void generate_thumbnails( const QModelIndex& start_index, int count );
    void reload_thumbnails();

    QHash<QString, QPixmap*> thumbnails_;
};

#endif // THUMBNAIL_PROXY_MODEL_H

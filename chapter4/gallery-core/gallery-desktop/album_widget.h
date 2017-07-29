#ifndef ALBUM_WIDGET_H
#define ALBUM_WIDGET_H

#include <QWidget>

namespace Ui {
class Album_Widget;
}

class Album_Model;
class Picture_Model;
class QItemSelectionModel;
class Thumbnail_Proxy_Model;

class Album_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Album_Widget(QWidget *parent = nullptr);
    ~Album_Widget();

    void set_album_model( Album_Model* model );
    void set_album_selection_model( QItemSelectionModel* album_selection_model );
    void set_picture_model( Thumbnail_Proxy_Model* picture_model );
    void set_picture_selection_model( QItemSelectionModel* selection_model );

signals:
    void picture_activated( const QModelIndex& index );

private slots:
    void delete_album();
    void edit_album();
    void add_pictures();

private:
    void clear_ui();
    void load_album( const QModelIndex& album_index );

    Ui::Album_Widget *ui;

    // album members
    Album_Model* album_model_;
    QItemSelectionModel* album_selection_model_;

    // picture members
    Thumbnail_Proxy_Model* picture_model_;
    QItemSelectionModel* picture_selection_model_;
};

#endif // ALBUM_WIDGET_H

#ifndef ALBUM_LIST_WIDGET_H
#define ALBUM_LIST_WIDGET_H

#include <QWidget>
#include <QItemSelectionModel>

class Album_Model;

namespace Ui {
class Album_List_Widget;
}

class Album_List_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Album_List_Widget(QWidget *parent = nullptr);
    ~Album_List_Widget();

    void set_model( Album_Model* model );
    void set_selection_model( QItemSelectionModel* selection_model );

private slots:
    void create_album();

private:
    Ui::Album_List_Widget *ui;
    Album_Model* album_model_;
};

#endif // ALBUM_LIST_WIDGET_H

#include "album_list_widget.h"
#include "ui_album_list_widget.h"
#include "album_model.h"

#include <QInputDialog>
#include <QString>
#include <QListView>

Album_List_Widget::Album_List_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Album_List_Widget),
    album_model_{ nullptr }
{
    ui->setupUi(this);

    connect( ui->create_album_button, &QPushButton::clicked,
             this, &Album_List_Widget::create_album );
}

Album_List_Widget::~Album_List_Widget()
{
    delete ui;
}

void Album_List_Widget::set_model(Album_Model *model)
{
    album_model_ = model;
    ui->album_list->setModel( album_model_ );
}

void Album_List_Widget::set_selection_model(QItemSelectionModel* selection_model)
{
    ui->album_list->setSelectionModel( selection_model );
}

void Album_List_Widget::create_album()
{
    if ( not album_model_ ) {
        return;
    }

    bool ok = false;
    QString album_name = QInputDialog::getText( this,
                                                "Create a new Album",
                                                "Choose a name",
                                                QLineEdit::Normal,
                                                "New album",
                                                &ok );

    if ( ok && not album_name.isEmpty() ) {
        const Album album{ album_name };
        QModelIndex created_index = album_model_->add_album( album );
        ui->album_list->setCurrentIndex( created_index );
    }

}

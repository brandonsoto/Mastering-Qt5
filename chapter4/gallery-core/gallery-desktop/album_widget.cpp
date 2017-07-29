#include "album_widget.h"
#include "ui_album_widget.h"
#include "album_model.h"
#include "picture_model.h"
#include "picture.h"
#include "thumbnail_proxy_model.h"

#include <QInputDialog>
#include <QFileDialog>
#include <QItemSelectionModel>
#include <QListView>

Album_Widget::Album_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Album_Widget),
    album_model_{ nullptr },
    album_selection_model_{ nullptr },
    picture_model_{ nullptr },
    picture_selection_model_{ nullptr }
{
    ui->setupUi(this);
    clear_ui();

    ui->thumbnail_list_view->setSpacing( 5 );
    ui->thumbnail_list_view->setResizeMode( QListView::Adjust );
    ui->thumbnail_list_view->setFlow( QListView::LeftToRight );
    ui->thumbnail_list_view->setWrapping( true );

    // setup album signals/slots
    connect( ui->thumbnail_list_view, &QListView::doubleClicked,
             this, &Album_Widget::picture_activated );
    connect( ui->delete_button, &QPushButton::clicked,
             this, &Album_Widget::delete_album );
    connect( ui->edit_button, &QPushButton::clicked,
             this, &Album_Widget::edit_album );
    connect( ui->add_pictures_button, &QPushButton::clicked,
             this, &Album_Widget::add_pictures );
}

Album_Widget::~Album_Widget()
{
    delete ui;
}

void Album_Widget::set_album_model(Album_Model *model)
{
    album_model_ = model;

    connect( album_model_, &QAbstractItemModel::dataChanged,
             [this]( const QModelIndex& top_left )
    {
        if ( top_left == album_selection_model_->currentIndex() ) {
            load_album( top_left );
        }
    } );
}

void Album_Widget::set_album_selection_model(QItemSelectionModel *album_selection_model)
{
    album_selection_model_ = album_selection_model;

    connect( album_selection_model_, &QItemSelectionModel::selectionChanged,
             [this](const QItemSelection& selected )
    {
        if ( selected.isEmpty() ) {
           clear_ui();
           return;
        }

        load_album( selected.indexes().first() );

    });
}

void Album_Widget::set_picture_model(Thumbnail_Proxy_Model *picture_model)
{
    picture_model_ = picture_model;
    ui->thumbnail_list_view->setModel( picture_model_ );
}

void Album_Widget::set_picture_selection_model(QItemSelectionModel *selection_model)
{
    ui->thumbnail_list_view->setSelectionModel( selection_model );
}

void Album_Widget::delete_album()
{
    if ( album_selection_model_->selectedIndexes().isEmpty() ) {
        return;
    }

    int row = album_selection_model_->currentIndex().row();
    album_model_->removeRow( row );

    // try to select the previous album
    QModelIndex previous_model_index = album_model_->index( row - 1, 0 );
    if ( previous_model_index.isValid() ) {
        album_selection_model_->setCurrentIndex( previous_model_index,
                                                 QItemSelectionModel::SelectCurrent );
        return;
    }

    // try to select the next album
    QModelIndex next_model_index = album_model_->index( row + 1, 0 );
    if ( next_model_index.isValid() ) {
        album_selection_model_->setCurrentIndex( next_model_index,
                                                 QItemSelectionModel::SelectCurrent );
        return;
    }
}

void Album_Widget::edit_album()
{
    if ( album_selection_model_->selectedIndexes().isEmpty() ) {
        return;
    }

    QModelIndex current_album_index = album_selection_model_->selectedIndexes().first();
    QString old_album_name = album_model_->data( current_album_index,
                                                 Album_Model::Roles::ROLE_NAME ).toString();

    bool ok = false;
    QString new_name = QInputDialog::getText( this,
                                              "Album's name",
                                              "Change Album name",
                                              QLineEdit::Normal,
                                              old_album_name,
                                              &ok );
    if ( ok && not new_name.isEmpty() ) {
        // setData emits dataChanged signal
        album_model_->setData( current_album_index, new_name, Album_Model::Roles::ROLE_NAME );
    }
}

void Album_Widget::add_pictures()
{
    QStringList filenames = QFileDialog::getOpenFileNames( this,
                                                           "Add pictures",
                                                           QDir::homePath(),
                                                           "Picture files (*.jpg *.png)" );
    if ( not filenames.isEmpty() ) {
        QModelIndex last_model_index{};

        for ( const auto& filename : filenames ) {
            Picture picture( filename );
            last_model_index = picture_model_->picture_model()->add_picture( picture );
        }

        ui->thumbnail_list_view->setCurrentIndex( last_model_index );
    }
}

void Album_Widget::clear_ui()
{
    ui->album_name->setText( "" );
    ui->delete_button->setVisible( false );
    ui->edit_button->setVisible( false );
    ui->add_pictures_button->setVisible( false );
}

void Album_Widget::load_album(const QModelIndex &album_index)
{
    picture_model_->picture_model()->set_album_id(
                album_model_->data( album_index, Album_Model::Roles::ROLE_ID ).toInt() );

    ui->album_name->setText( album_model_->data( album_index, Qt::DisplayRole ).toString() );

    ui->delete_button->setVisible( true );
    ui->edit_button->setVisible( true );
    ui->add_pictures_button->setVisible( true );
}

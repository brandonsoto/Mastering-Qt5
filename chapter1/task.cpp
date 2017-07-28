#include "task.h"
#include "ui_task.h"

#include <QInputDialog>
#include <QDebug>
#include <QFont>

Task::Task( const QString& name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    set_name(name);

    connect(ui->edit_button, &QPushButton::clicked, this, &Task::rename );
    connect(ui->remove_button, &QPushButton::clicked, this, [this]() {
        qDebug() << "Trying to remove: " << get_name();
        emit removed(this);
    } );
    connect( ui->checkbox, &QCheckBox::toggled, this, &Task::checked );
}

Task::~Task()
{
    delete ui;
}

QString Task::get_name() const
{
   return ui->checkbox->text();
}

void Task::set_name(const QString &name)
{
    ui->checkbox->setText( name );
}

bool Task::is_completed() const
{
    return ui->checkbox->isChecked();
}

void Task::rename()
{
    bool is_ok = false;
    const auto name = QInputDialog::getText( this, tr("Edit task"), tr("Task name"),
                                             QLineEdit::Normal, get_name(), &is_ok );

    if ( is_ok && not name.isEmpty() ) {
        set_name( name );
    }
}

void Task::checked(const bool checked)
{
   auto font = ui->checkbox->font();
   font.setStrikeOut( checked );
   ui->checkbox->setFont( font );
   emit status_changed( this );
}

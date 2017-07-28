#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect( ui->add_task_button, &QPushButton::clicked, // sender
             this, &MainWindow::add_task );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_status()
{
    int total_completed = 0;
    for ( const auto& task : tasks_ ) {
        if ( task->is_completed() ) {
            ++total_completed;
        }
    }

    const auto total_todos = tasks_.size() - total_completed;
    ui->status_label->setText( QString("Status: %1 todo / %2 completed")
                               .arg( total_todos )
                               .arg( total_completed ) );
}

void MainWindow::add_task() {
    qDebug() << "User clicked on the button";

    bool is_ok = false;
    const QString name = QInputDialog::getText( this, tr("Add task"), tr("Task name"),
                                                QLineEdit::Normal, tr("Untitled task"), &is_ok );

    if ( is_ok && not name.isEmpty() ) {
        Task* task = new Task(name);
        connect( task, &Task::removed, this, &MainWindow::remove_task );
        connect( task, &Task::status_changed, this, &MainWindow::task_status_changed );
        tasks_.append( task );
        ui->tasks_layout->addWidget( task );
    }

}

void MainWindow::remove_task(Task *task)
{
    tasks_.removeOne( task );
    ui->tasks_layout->removeWidget( task );
    task->setParent( nullptr );
    delete task;
    update_status();
}

void MainWindow::task_status_changed(Task *task)
{
   update_status();
}

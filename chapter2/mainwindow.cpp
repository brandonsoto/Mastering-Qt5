#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "system_info.h"

#include <QLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    cpu_widget_( this )
{
    ui->setupUi(this);
    System_Info::instance().init();
    ui->centralWidget->layout()->addWidget( &cpu_widget_ );
}

MainWindow::~MainWindow()
{
    delete ui;
}

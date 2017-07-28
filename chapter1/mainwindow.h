#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "task.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void update_status();

public slots:
    void add_task();
    void remove_task( Task* task );
    void task_status_changed( Task* task );

private:
    Ui::MainWindow *ui;
    QVector<Task*> tasks_;
};

#endif // MAINWINDOW_H

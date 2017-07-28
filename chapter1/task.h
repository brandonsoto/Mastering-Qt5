#ifndef TASK_H
#define TASK_H

#include <QWidget>
#include <QString>

namespace Ui {
class Task;
}

class Task : public QWidget
{
    Q_OBJECT

public:
    explicit Task( const QString& name, QWidget *parent = 0);
    ~Task();

    QString get_name() const;
    void set_name( const QString& name );
    bool is_completed() const;

public slots:
    void rename();

private slots:
    void checked( const bool checked );

signals:
    void removed( Task* task );
    void status_changed( Task* task );

private:
    Ui::Task *ui;
};

#endif // TASK_H

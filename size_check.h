#ifndef SIZE_CHECK_H
#define SIZE_CHECK_H

#include <QDialog>
#include <QPushButton>
namespace Ui
{
    class Size_check;
}

class Size_check : public QDialog
{
    Q_OBJECT

public:
    explicit Size_check(QWidget *parent = nullptr);
    ~Size_check();

private:
    Ui::Size_check *ui;

signals:
    void ensure(QString, QString);
public slots:
    void open_by_main();
};

#endif // SIZE_CHECK_H

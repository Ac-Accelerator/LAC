#ifndef EDITOR_H
#define EDITOR_H

#include "calculate.h"
#include "matix.h"
#include "size_check.h"
#include <QDialog>
#include <QListWidget>
namespace Ui
{
    class Editor;
}

class Editor : public QDialog
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);
    ~Editor();

private:
    Matix matix;
    Matix matix_adj;
    Matix matix_inv;
    Matix matix_transpose;
    Matix matix_save;
    Ui::Editor *ui;
    void reset_output_hlab(int);

public slots:
    void open_by_checker(QString, QString);
    void open_by_displayer(QListWidgetItem *);
    void button_ensure();
    void button_inverse();
    void button_adjoint();
    void button_turn();
    void button_env();
    void button_save();
    void button_delete();
};

#endif // EDITOR_H

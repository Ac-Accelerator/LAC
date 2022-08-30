#include "var_man.h"
#include "ui_var_man.h"

Var_man::Var_man(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Var_man)
{
    ui->setupUi(this);
}

Var_man::~Var_man()
{
    delete ui;
}

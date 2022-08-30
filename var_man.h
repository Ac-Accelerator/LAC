#ifndef VAR_MAN_H
#define VAR_MAN_H

#include <QDialog>

namespace Ui {
class Var_man;
}

class Var_man : public QDialog
{
    Q_OBJECT

public:
    explicit Var_man(QWidget *parent = nullptr);
    ~Var_man();

private:
    Ui::Var_man *ui;
};

#endif // VAR_MAN_H

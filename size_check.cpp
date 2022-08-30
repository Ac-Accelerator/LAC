#include "size_check.h"
#include "ui_size_check.h"

Size_check::Size_check(QWidget *parent) : QDialog(parent),
                                          ui(new Ui::Size_check)
{
    ui->setupUi(this);
    connect(ui->ensure, &QPushButton::clicked, [=]()
            {
                emit ensure(ui->row->text(),ui->co->text());
                this->close(); });

    connect(ui->cancel, &QPushButton::clicked, [=]()
            { this->close(); });
}

Size_check::~Size_check()
{
    delete ui;
}

void Size_check::open_by_main()
{
    ui->co->clear();
    ui->row->clear();
    this->exec();
}

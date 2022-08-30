#include "editor.h"
#include "ui_editor.h"
#include <QDebug>
Editor::Editor(QWidget *parent) : QDialog(parent),
                                  ui(new Ui::Editor)
{
    ui->setupUi(this);
    ui->inverse->setDisabled(true);
    ui->turn->setDisabled(true);
    ui->env->setDisabled(true);
    ui->adjoint->setDisabled(true);
    ui->save->setDisabled(true);
    ui->delete_2->setDisabled(true);
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::red);
    ui->warn->setPalette(pe);
    ui->warn->hide();

    connect(ui->ensrue, &QPushButton::clicked, this, &Editor::button_ensure);

    connect(ui->cancel, &QPushButton::clicked, [=]()
            { this->close(); });

    connect(ui->inverse, &QPushButton::clicked, [=]()
            {   ui->save->setDisabled(false);
                button_inverse(); });

    connect(ui->adjoint, &QPushButton::clicked, [=]()
            {   ui->save->setDisabled(false);
                button_adjoint(); });

    connect(ui->turn, &QPushButton::clicked, [=]()
            {   ui->save->setDisabled(false);
                button_turn(); });

    connect(ui->env, &QPushButton::clicked, [=]()
            {   ui->save->setDisabled(true);
                button_env(); });

    connect(ui->save, &QPushButton::clicked, [=]()
            { button_save(); });

    connect(ui->delete_2, &QPushButton::clicked, [=]()
            { button_delete(); });
}

Editor::~Editor()
{
    delete ui;
}

void Editor::reset_output_hlab(int n)
{
    QStringList order;
    for (int i = 1; i <= n; ++i)
    {
        order << to_string(i).c_str();
    }
    ui->output->setHorizontalHeaderLabels(order);
}

void Editor::open_by_checker(QString str_row, QString str_co)
{
    int row = str_row.toInt(), co = str_co.toInt();
    ui->input->setRowCount(row);
    ui->input->setColumnCount(co);
    ui->output->clear();

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < co; ++j)
        {
            ui->input->setItem(i, j, new QTableWidgetItem("0"));
        }
    }
    this->exec();
}

void Editor::open_by_displayer(QListWidgetItem *item)
{
    Matix *temp = &LM[order[item->text().toStdString()]];
    ui->delete_2->setDisabled(false);
    ui->input->setRowCount(temp->m_m);
    ui->input->setColumnCount(temp->m_n);
    for (int i = 0; i < temp->m_m; ++i)
    {
        for (int j = 0; j < temp->m_n; ++j)
        {
            ui->input->setItem(i, j, new QTableWidgetItem(temp->map[i + 1][j + 1].display().c_str()));
        }
    }
    ui->name_input->setText(temp->m_name.c_str());
    button_ensure();
    this->exec();
}

void Editor::button_ensure()
{
    if (ui->name_input->text() == "")
    {
        ui->warn->show();
        return;
    }
    ui->save->setDisabled(false);
    ui->turn->setDisabled(false);
    ui->ensrue->setText("更改");
    ui->output->setRowCount(ui->input->rowCount());
    ui->output->setColumnCount(ui->input->columnCount());
    reset_output_hlab(ui->input->columnCount());

    matix.m_m = ui->input->rowCount(), matix.m_n = ui->input->columnCount();
    matix.m_name = ui->name_input->text().toStdString();

    for (int i = 0; i < ui->input->rowCount(); ++i)
    {
        for (int j = 0; j < ui->input->columnCount(); ++j)
        {
            delete ui->output->takeItem(i, j);
            matix.map[i + 1][j + 1] = Fraction(ui->input->item(i, j)->text().toStdString());
            ui->output->setItem(i, j, new QTableWidgetItem(ui->input->item(i, j)->text()));
        }
    }
    matix_save = matix;
    //    qDebug() << matix.m_name.c_str() << matix_save.m_name.c_str();
    ui->name->setText(ui->name_input->text());
    ui->rank->setText(QString::number(matix.rank()));
    if (matix.m_m == matix.m_n)
    {
        ui->value->setText(matix.Det().calculate().display().c_str());
        ui->env->setDisabled(false);
        if (matix.rank() == matix.m_m)
        {
            ui->adjoint->setDisabled(false);
            ui->inverse->setDisabled(false);
        }
    }
    else
    {
        ui->inverse->setDisabled(true);
        ui->env->setDisabled(true);
        ui->adjoint->setDisabled(true);
    }
}

void Editor::button_inverse()
{

    reset_output_hlab(ui->input->columnCount());
    matix_inv = matix.inverse();
    matix_save = matix_inv;
    ui->name->setText(matix_save.m_name.c_str());
    for (int i = 0; i < matix.m_m; ++i)
    {
        for (int j = 0; j < matix.m_n; ++j)
        {
            delete ui->output->takeItem(i, j);
            ui->output->setItem(i, j, new QTableWidgetItem(matix_inv.map[i + 1][j + 1].display().c_str()));
        }
    }
}

void Editor::button_adjoint()
{
    reset_output_hlab(ui->input->columnCount());
    matix_adj = matix.adjoint();
    matix_save = matix_adj;
    ui->name->setText(matix_save.m_name.c_str());
    for (int i = 0; i < matix.m_m; ++i)
    {
        for (int j = 0; j < matix.m_n; ++j)
        {
            delete ui->output->takeItem(i, j);
            ui->output->setItem(i, j, new QTableWidgetItem(matix_adj.map[i + 1][j + 1].display().c_str()));
        }
    }
}

void Editor::button_turn()
{
    matix.transpose();
    matix_transpose = matix;
    matix_transpose.m_name = matix.m_name + "_T";
    matix_save = matix_transpose;
    matix.transpose();
    ui->output->setRowCount(ui->input->columnCount());
    ui->output->setColumnCount(ui->input->rowCount());
    reset_output_hlab(ui->input->rowCount());
    ui->name->setText(matix_save.m_name.c_str());
    for (int i = 0; i < matix.m_n; ++i)
    {
        for (int j = 0; j < matix.m_m; ++j)
        {
            delete ui->output->takeItem(i, j);
            ui->output->setItem(i, j, new QTableWidgetItem(matix_transpose.map[i + 1][j + 1].display().c_str()));
        }
    }
}

void Editor::button_env()
{
    QStringList eval;
    eigen ans = matix.eigenvalue(); //记得删除指针
    for (int i = 0; i < matix.m_m; ++i)
    {
        gsl_complex eval_i = gsl_vector_complex_get(ans.value, i);
        {
            std::ostringstream temp;
            temp << "值:" << (abs(eval_i.dat[0]) < 1e-10 ? 0 : eval_i.dat[0]);
            if (abs(eval_i.dat[1]) > 1e-10)
            {
                if (eval_i.dat[1] > 0)
                    temp << '+';
                temp << eval_i.dat[1] << "*i";
            }
            eval << temp.str().c_str();
        }
        for (int j = 0; j < matix.m_m; j++)
        {
            std::ostringstream temp;
            gsl_complex element = gsl_matrix_complex_get(ans.matix, j, i);
            temp << ((abs(element.dat[0]) < 1e-10) ? 0 : element.dat[0]);
            if (abs(element.dat[1]) > 1e-10)
            {
                if (element.dat[1] > 0)
                    temp << '+';
                temp << element.dat[1] << "*i";
            }
            delete ui->output->takeItem(j, i);
            ui->output->setItem(j, i, new QTableWidgetItem(temp.str().c_str()));
        }
    }
    ui->output->setHorizontalHeaderLabels(eval);
    delete ans.matix, delete ans.value;
}

void Editor::button_save()
{
    order[ui->name->text().toStdString()] = PM;
    LM[PM] = matix_save;
    ++PM;
}

void Editor::button_delete()
{
    order.erase(ui->name->text().toStdString());
    this->close();
}

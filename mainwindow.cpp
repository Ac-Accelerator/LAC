#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    check_window = new Size_check(this);
    this->startTimer(500);
    std::fstream exist("data"); //
    if (!exist.good())
    {
        fstream exist("data", ios::out);
        streambuf *oldout = cout.rdbuf(exist.rdbuf());
        cout << '0' << endl;
        cout.rdbuf(oldout);
    }
    exist.close();
    connect(ui->inputmatix, &QPushButton::clicked, check_window, &Size_check::open_by_main);

    //    connect(check_window, &Size_check::ensure, edit_window, &Editor::open_by_checker);
    connect(check_window, &Size_check::ensure, [=](QString a, QString b)
            {   Editor *edit_window = new Editor(this);
                edit_window->open_by_checker(a, b);
                delete edit_window; });
    connect(ui->var_display, &QListWidget::itemDoubleClicked, [=](QListWidgetItem *item)
            {
                Editor *edit_window = new Editor(this);
                edit_window->open_by_displayer(item);
                delete edit_window; });
    connect(ui->button_clear, &QPushButton::clicked, ui->expression_input, &QLineEdit::clear);
    connect(ui->button_compute, &QPushButton::clicked, [=]()
            { compute(); });
    connect(ui->load, &QPushButton::clicked, [=]()
            { load(); });
    connect(ui->write, &QPushButton::clicked, [=]()
            { write(); });
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    ui->var_display->setCurrentRow(PM);
    ui->var_display->clear();
    for (auto i : order)
    {
        ui->var_display->addItem(i.first.c_str());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::compute()
{
    int p = 0;
    Matix m = expression_value(ui->expression_input->text().toStdString(), p);
    order[m.m_name] = PM;
    LM[PM] = m;
    ++PM;
    ui->outcome->setText("计算结果已储存为" + QString(m.m_name.c_str()));
}

void MainWindow::load()
{
    using namespace std;
    fstream data("data", ios::in);
    streambuf *oldin = cin.rdbuf(data.rdbuf());
    int num;
    cin >> num;
    string vcalss, na, fractions;
    int n, m;
    for (int i = 0; i < num; i++)
    {
        cin >> na;
        cin >> m >> n;
        Fraction list[m * n];
        for (int i = 0; i < n * m; i++)
        {
            cin >> fractions;
            list[i] = Fraction(fractions);
        }
        order[na] = PM;
        LM[PM++] = Matix(na, m, n, list);
    }
    cin.rdbuf(oldin);
}

void MainWindow::write()
{
    using namespace std;
    fstream data("data", ios::in | ios::out | ios::trunc);
    streambuf *oldout = cout.rdbuf(data.rdbuf());
    cout << order.size() << endl;
    int m, n;
    for (auto it = order.begin(); it != order.end(); ++it)
    {
        cout << it->first << ' ';
        cout << LM[it->second].m_m << ' ' << LM[it->second].m_n << ' ';
        m = LM[it->second].m_m;
        n = LM[it->second].m_n;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                cout << LM[it->second].map[i][j].display() << ' ';
    }
    cout << endl;
    cout.rdbuf(oldout);
}

#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_about_dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineFast->setFocus();
    connect(this, &MainWindow::valueChanged,
            this, &MainWindow::updateBinaryView);
    connect(ui->action_About, &QAction::triggered, [](){
        QDialog dialog;
        Ui_Dialog ui;
        ui.setupUi(&dialog);
        dialog.exec();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnEncode_clicked()
{
    auto orig = ui->lineOriginal->text();
    bool ok = false;
    quint64 val = orig.toULongLong(&ok, 10);
    if (!ok)
    {
        ui->statusBar->showMessage(QString("Unable convert %1").arg(orig), 1000);
        return;
    }
    emit valueChanged(val);

    QByteArray vec;
    while (val > 0)
    {
        char f = val&0x7f;
        vec.push_front(f);
        val >>= 7;
    }
    auto it = vec.rbegin();
    *it = *it | 0x80;
    ui->lineFast->setText(vec.toHex());
}

void MainWindow::on_btnDecode_clicked()
{
    auto orig = ui->lineFast->text();
    bool ok = false;
    quint64 val = orig.toULongLong(&ok, 16);
    if (!ok)
    {
        ui->statusBar->showMessage(QString("Unable convert %1").arg(orig), 1000);
        return;
    }

    QByteArray vec = QByteArray::fromHex(orig.toUtf8());
    emit valueChanged(val);

    quint64 ret = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        quint8 t = (quint8)(*it) & 0x7F;
        ret <<= 7;
        ret += t;
    }

    ui->lineOriginal->setText(QString("%1").arg(ret));
}

void MainWindow::updateBinaryView(quint64 value)
{
    ui->dispBinary->setText(QString("%1").arg(value));
}

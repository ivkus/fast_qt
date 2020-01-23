#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void valueChanged(quint64);
private slots:
    void on_btnEncode_clicked();
    void on_btnDecode_clicked();
    void updateBinaryView(quint64 value);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

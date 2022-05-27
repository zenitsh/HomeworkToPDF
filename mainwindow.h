#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <MagickWand/MagickWand.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_expl_clicked();

    void on_btn_com_clicked();

private:
    Ui::MainWindow *ui;
    QString m_filepath;
    QString m_filepath1;
    QString m_filename;
};
#endif // MAINWINDOW_H

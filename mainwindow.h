#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <MagickWand/MagickWand.h>
#include <QDragEnterEvent>
#include <QDropEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void OpenFile(QString filename);

private slots:
    void on_btn_expl_clicked();

    void on_btn_com_clicked();

    void on_btn_del_clicked();

    void img_open(QStringList);

    void dragEnterEvent(QDragEnterEvent *event);

    void dropEvent(QDropEvent *event);

private:
    Ui::MainWindow *ui;
    QString m_filepath;
    QString m_filepath1;
    QString m_filename;
    QLayout *m_layout;
};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "htpitemwidget.h"
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file("homework_info.json");
    if(file.open(QIODevice::ReadOnly))
    {
        QJsonDocument document = QJsonDocument::fromJson(file.readAll());
        QJsonObject root = document.object();
        m_filepath = root.find("in-filepath").value().toString();
        m_filepath1 = root.find("out-filepath").value().toString();
        m_filename = root.find("out-filename").value().toString();
        file.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_expl_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"打开",m_filepath);
    QFileInfo info(filename);
    m_filepath = info.absolutePath();
    QImage img;
    if(img.load(filename))
    {
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(128,128));
        HtpItemWidget *widget = new HtpItemWidget(this,filename,img);
        widget->setSizeIncrement(QSize(0,128));
        ui->list_files->addItem(item);
        ui->list_files->setItemWidget(item,widget);
    }
}


void MainWindow::on_btn_com_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,"保存",m_filepath1+"/"+m_filename,"pdf",new QString("pdf"));
    if(filename=="")
    {
        return;
    }
    QFileInfo info(filename);
    m_filepath1 = info.absolutePath();
    m_filename = info.fileName();
    QFile file("homework_info.json");
    if(file.exists())
        file.open(QIODevice::WriteOnly);
    else
        file.open(QIODevice::Append);
    QJsonDocument document;
    QJsonObject root;
    root.insert("in-filepath",m_filepath);
    root.insert("out-filepath",m_filepath1);
    root.insert("out-filename",m_filename);
    document.setObject(root);
    file.write(document.toJson());
    file.close();
    MagickWand *wand = NewMagickWand();
    for(int i=0;i<ui->list_files->count();++i)
    {
        MagickReadImage(wand,((HtpItemWidget*)ui->list_files->itemWidget(ui->list_files->item(i)))->name().toStdString().c_str());
    }
    MagickWriteImages(wand,(m_filepath1+"/"+m_filename).toStdString().c_str(),MagickBooleanType::MagickTrue);
    DestroyMagickWand(wand);
}


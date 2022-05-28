#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "htpitemwidget.h"
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QTextStream>
#include <QFileInfo>
#include <QImageReader>
#include <QMimeData>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(!QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).exists())
        QDir().mkdir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));

    QFile file(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/homework_info.json");
    if(file.open(QIODevice::ReadOnly))
    {
        QJsonDocument document = QJsonDocument::fromJson(file.readAll());
        QJsonObject root = document.object();
        m_filepath = root.find("in-filepath").value().toString();
        m_filepath1 = root.find("out-filepath").value().toString();
        m_filename = root.find("out-filename").value().toString();
        file.close();
    }
    QImageReader::setAllocationLimit(256);
    m_layout = this->layout();
    setAcceptDrops(true);
    connect(ui->list_files,SIGNAL(img_open(QStringList)),this,SLOT(img_open(QStringList)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::img_open(QStringList filenames)
{
    for(int i=0;i<filenames.count();++i)
    {
        OpenFile(filenames[i]);
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        QListWidgetItem *item =ui->list_files->itemAt(event->position().toPoint());
        if(item)ui->list_files->setCurrentItem(item);
        QStringList ls;
        for(int i=0;i<event->mimeData()->urls().size();++i)
        {
            ls.append(event->mimeData()->urls().at(i).path().remove(0,1));
        }
        emit img_open(ls);
    }
}

void MainWindow::on_btn_expl_clicked()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this,"打开",m_filepath);
    for(int i=0;i<filenames.count();++i)
    {
        OpenFile(filenames[i]);
    }
}

void MainWindow::OpenFile(QString filename)
{
    QImage img;
    QFileInfo info(filename);
    m_filepath = info.absolutePath();
    if(img.load(filename))
    {
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(128,128));
        item->setData(Qt::UserRole+1,filename);
        HtpItemWidget *widget = new HtpItemWidget(this,filename,img);
        widget->setSizeIncrement(QSize(0,128));
        ui->list_files->insertItem(ui->list_files->currentRow()+1,item);
        ui->list_files->setCurrentItem(item);
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
    QFile file(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/homework_info.json");
    qDebug()<<file.filesystemFileName();
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


void MainWindow::on_btn_del_clicked()
{
    QListWidgetItem *item = ui->list_files->currentItem();
    if(item)
    {
        ui->list_files->removeItemWidget(item);
        ui->list_files->takeItem(ui->list_files->currentRow());
    }
}



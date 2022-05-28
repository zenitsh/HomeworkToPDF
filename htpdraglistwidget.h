#ifndef HTPDRAGLISTWIDGET_H
#define HTPDRAGLISTWIDGET_H

#include <QListWidget>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDrag>
#include <QDropEvent>

class HtpDragListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit HtpDragListWidget(QWidget *parent = nullptr);

protected slots:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

signals:
    void img_open(QStringList);

};

#endif // HTPDRAGLISTWIDGET_H

#include "htpdraglistwidget.h"
#include "htpitemwidget.h"
#include <QMimeData>
#include <QStandardItemModel>

HtpDragListWidget::HtpDragListWidget(QWidget *parent)
    : QListWidget{parent}
{
    this->setAcceptDrops(true);
}

void HtpDragListWidget::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist"))
    {
        QListWidgetItem *take = this->currentItem();
        QPoint p = event->position().toPoint();
        p.setY(p.y()-64);
        QListWidgetItem *item = this->itemAt(p);
        if(item)
        {
            setCurrentItem(item);
        }
        else
        {
            if(p.y()-64<0)
                setCurrentRow(-1);
        }
        QStandardItemModel *model = new QStandardItemModel();
        model->dropMimeData(event->mimeData(),Qt::MoveAction,0,0,QModelIndex());
        QString filename = model->item(0)->data().toString();
        QStringList ls;
        ls.append(filename);
        emit img_open(ls);
        this->takeItem(this->row(take));
    }
}

void HtpDragListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    QListWidget::dragEnterEvent(event);
}

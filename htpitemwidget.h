#ifndef HTPITEMWIDGET_H
#define HTPITEMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

class HtpItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HtpItemWidget(QWidget *parent, QString text, QImage img);
    ~HtpItemWidget();

    QString name();

signals:

private:
    QString m_text;
    QImage m_img;
    QLabel *m_label0;
    QLabel *m_label1;
    QHBoxLayout *m_layout;

};

#endif // HTPITEMWIDGET_H

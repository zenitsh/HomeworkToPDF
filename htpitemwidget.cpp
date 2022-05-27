#include "htpitemwidget.h"

HtpItemWidget::HtpItemWidget(QWidget *parent, QString text, QImage img)
    : QWidget{parent}, m_text(text), m_img(img)
{
    m_layout = new QHBoxLayout();
    this->setLayout(m_layout);
    m_label0 = new QLabel();
    m_label0->setPixmap(QPixmap::fromImage(img));
    m_label1 = new QLabel();
    m_label1->setText(text);
    m_layout->addWidget(m_label0);
    m_layout->addWidget(m_label1);
}

HtpItemWidget::~HtpItemWidget()
{
    m_layout->removeWidget(m_label1);
    m_layout->removeWidget(m_label0);
    delete m_label1;
    delete m_label0;
    delete m_layout;
}

QString HtpItemWidget::name()
{
    return m_text;
}

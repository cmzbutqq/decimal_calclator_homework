#ifndef WIDGET_H
#define WIDGET_H

#include "decimal.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_plus_clicked();

    void on_minus_clicked();

    void on_multiply_clicked();

    void on_divide_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

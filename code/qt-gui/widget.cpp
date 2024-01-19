#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_plus_clicked()
{
    Decimal left(ui->left->text().toStdString());
    Decimal right(ui->right->text().toStdString());
    string ans=(left+right).print();
    ui->ans->setText(QString::fromStdString(ans));
}

void Widget::on_minus_clicked()
{
    Decimal left(ui->left->text().toStdString());
    Decimal right(ui->right->text().toStdString());
    string ans=(left-right).print();
    ui->ans->setText(QString::fromStdString(ans));
}

void Widget::on_multiply_clicked()
{
    Decimal left(ui->left->text().toStdString());
    Decimal right(ui->right->text().toStdString());
    string ans=(left*right).print();
    ui->ans->setText(QString::fromStdString(ans));
}

void Widget::on_divide_clicked()
{
    Decimal left(ui->left->text().toStdString());
    Decimal right(ui->right->text().toStdString());
    string ans=(left/right).second?string("ERROR"):(left/right).first.print();
    ui->ans->setText(QString::fromStdString(ans));
}

/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLineEdit *left;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *plus;
    QPushButton *minus;
    QPushButton *multiply;
    QPushButton *divide;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *right;
    QTextEdit *ans;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(210, 260);
        Widget->setMinimumSize(QSize(210, 260));
        Widget->setMaximumSize(QSize(210, 260));
        widget = new QWidget(Widget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 194, 241));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        left = new QLineEdit(widget);
        left->setObjectName(QString::fromUtf8("left"));
        left->setStyleSheet(QString::fromUtf8("font: 12pt \"Arial\";"));

        verticalLayout->addWidget(left);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        plus = new QPushButton(widget);
        plus->setObjectName(QString::fromUtf8("plus"));
        plus->setMinimumSize(QSize(40, 40));
        plus->setMaximumSize(QSize(40, 40));
        plus->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        horizontalLayout->addWidget(plus);

        minus = new QPushButton(widget);
        minus->setObjectName(QString::fromUtf8("minus"));
        minus->setMinimumSize(QSize(40, 40));
        minus->setMaximumSize(QSize(40, 40));
        minus->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        horizontalLayout->addWidget(minus);

        multiply = new QPushButton(widget);
        multiply->setObjectName(QString::fromUtf8("multiply"));
        multiply->setMinimumSize(QSize(40, 40));
        multiply->setMaximumSize(QSize(40, 40));
        multiply->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        horizontalLayout->addWidget(multiply);

        divide = new QPushButton(widget);
        divide->setObjectName(QString::fromUtf8("divide"));
        divide->setMinimumSize(QSize(40, 40));
        divide->setMaximumSize(QSize(40, 40));
        divide->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        horizontalLayout->addWidget(divide);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 4);
        horizontalLayout->setStretch(2, 4);
        horizontalLayout->setStretch(3, 4);
        horizontalLayout->setStretch(4, 4);
        horizontalLayout->setStretch(5, 1);

        verticalLayout->addLayout(horizontalLayout);

        right = new QLineEdit(widget);
        right->setObjectName(QString::fromUtf8("right"));
        right->setStyleSheet(QString::fromUtf8("font: 12pt \"Arial\";"));

        verticalLayout->addWidget(right);

        ans = new QTextEdit(widget);
        ans->setObjectName(QString::fromUtf8("ans"));
        ans->setStyleSheet(QString::fromUtf8("font: 12pt \"Arial\";"));

        verticalLayout->addWidget(ans);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        plus->setText(QCoreApplication::translate("Widget", "+", nullptr));
        minus->setText(QCoreApplication::translate("Widget", "-", nullptr));
        multiply->setText(QCoreApplication::translate("Widget", "\303\227", nullptr));
        divide->setText(QCoreApplication::translate("Widget", "\303\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

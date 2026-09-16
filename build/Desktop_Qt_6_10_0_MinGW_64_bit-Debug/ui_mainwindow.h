/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave_As_2;
    QAction *actionSave_2;
    QAction *actionUndo;
    QAction *actionRedo;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QListWidget *listWidget;
    QPushButton *btnRemoveAll;
    QPushButton *btnRemove;
    QLineEdit *txtItem;
    QPushButton *btnAdd;
    QSpinBox *spinQty;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(517, 1001);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionSave_As_2 = new QAction(MainWindow);
        actionSave_As_2->setObjectName("actionSave_As_2");
        actionSave_2 = new QAction(MainWindow);
        actionSave_2->setObjectName("actionSave_2");
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName("actionUndo");
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName("actionRedo");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");

        gridLayout->addWidget(listWidget, 1, 0, 1, 6);

        btnRemoveAll = new QPushButton(centralwidget);
        btnRemoveAll->setObjectName("btnRemoveAll");

        gridLayout->addWidget(btnRemoveAll, 2, 5, 1, 1);

        btnRemove = new QPushButton(centralwidget);
        btnRemove->setObjectName("btnRemove");

        gridLayout->addWidget(btnRemove, 2, 3, 1, 1);

        txtItem = new QLineEdit(centralwidget);
        txtItem->setObjectName("txtItem");

        gridLayout->addWidget(txtItem, 0, 0, 1, 4);

        btnAdd = new QPushButton(centralwidget);
        btnAdd->setObjectName("btnAdd");

        gridLayout->addWidget(btnAdd, 0, 5, 1, 1);

        spinQty = new QSpinBox(centralwidget);
        spinQty->setObjectName("spinQty");
        spinQty->setMinimum(1);
        spinQty->setMaximum(999);

        gridLayout->addWidget(spinQty, 0, 4, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 517, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName("menuFile");
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName("menuEdit");
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave_As_2);
        menuFile->addAction(actionSave_2);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionSave_As_2->setText(QCoreApplication::translate("MainWindow", "Save As", nullptr));
        actionSave_2->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionUndo->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
        actionRedo->setText(QCoreApplication::translate("MainWindow", "Redo", nullptr));
        btnRemoveAll->setText(QCoreApplication::translate("MainWindow", "Remove All", nullptr));
        btnRemove->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        btnAdd->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

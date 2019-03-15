/********************************************************************************
** Form generated from reading UI file 'EmulatorGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMULATORGUI_H
#define UI_EMULATORGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include "openglrenderwidget.h"

QT_BEGIN_NAMESPACE

class Ui_EmulatorGUIClass
{
public:
    QAction *actionOpen_ROM;
    QAction *actionExit;
    QAction *actionCPU_Debugger;
    QAction *actionMemory_Debugger;
    QAction *actionVidoe_Debugger;
    QAction *actionSound_Debugger;
    QAction *actionAbout;
    OpenGLRenderWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuDebugger;
    QMenu *menuHelp;

    void setupUi(QMainWindow *EmulatorGUIClass)
    {
        if (EmulatorGUIClass->objectName().isEmpty())
            EmulatorGUIClass->setObjectName(QStringLiteral("EmulatorGUIClass"));
        EmulatorGUIClass->resize(479, 360);
        EmulatorGUIClass->setMinimumSize(QSize(144, 160));
        actionOpen_ROM = new QAction(EmulatorGUIClass);
        actionOpen_ROM->setObjectName(QStringLiteral("actionOpen_ROM"));
        actionExit = new QAction(EmulatorGUIClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionCPU_Debugger = new QAction(EmulatorGUIClass);
        actionCPU_Debugger->setObjectName(QStringLiteral("actionCPU_Debugger"));
        actionMemory_Debugger = new QAction(EmulatorGUIClass);
        actionMemory_Debugger->setObjectName(QStringLiteral("actionMemory_Debugger"));
        actionVidoe_Debugger = new QAction(EmulatorGUIClass);
        actionVidoe_Debugger->setObjectName(QStringLiteral("actionVidoe_Debugger"));
        actionSound_Debugger = new QAction(EmulatorGUIClass);
        actionSound_Debugger->setObjectName(QStringLiteral("actionSound_Debugger"));
        actionAbout = new QAction(EmulatorGUIClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new OpenGLRenderWidget(EmulatorGUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        centralWidget->setContextMenuPolicy(Qt::NoContextMenu);
        EmulatorGUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EmulatorGUIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 479, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuDebugger = new QMenu(menuBar);
        menuDebugger->setObjectName(QStringLiteral("menuDebugger"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        EmulatorGUIClass->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuDebugger->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen_ROM);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuDebugger->addAction(actionCPU_Debugger);
        menuDebugger->addAction(actionMemory_Debugger);
        menuDebugger->addAction(actionVidoe_Debugger);
        menuDebugger->addAction(actionSound_Debugger);
        menuHelp->addAction(actionAbout);

        retranslateUi(EmulatorGUIClass);
        QObject::connect(actionOpen_ROM, SIGNAL(triggered()), EmulatorGUIClass, SLOT(OpenROM()));
        QObject::connect(actionCPU_Debugger, SIGNAL(triggered()), EmulatorGUIClass, SLOT(OpenCPUDebugger()));

        QMetaObject::connectSlotsByName(EmulatorGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *EmulatorGUIClass)
    {
        EmulatorGUIClass->setWindowTitle(QApplication::translate("EmulatorGUIClass", "Gameboy Emulator", nullptr));
        actionOpen_ROM->setText(QApplication::translate("EmulatorGUIClass", "Open ROM", nullptr));
        actionExit->setText(QApplication::translate("EmulatorGUIClass", "Exit", nullptr));
        actionCPU_Debugger->setText(QApplication::translate("EmulatorGUIClass", "CPU Debugger", nullptr));
        actionMemory_Debugger->setText(QApplication::translate("EmulatorGUIClass", "Memory Debugger", nullptr));
        actionVidoe_Debugger->setText(QApplication::translate("EmulatorGUIClass", "Vidoe Debugger", nullptr));
        actionSound_Debugger->setText(QApplication::translate("EmulatorGUIClass", "Sound Debugger", nullptr));
        actionAbout->setText(QApplication::translate("EmulatorGUIClass", "About", nullptr));
        menuFile->setTitle(QApplication::translate("EmulatorGUIClass", "File", nullptr));
        menuDebugger->setTitle(QApplication::translate("EmulatorGUIClass", " Debug", nullptr));
        menuHelp->setTitle(QApplication::translate("EmulatorGUIClass", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmulatorGUIClass: public Ui_EmulatorGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMULATORGUI_H

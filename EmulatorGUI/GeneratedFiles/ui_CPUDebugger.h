/********************************************************************************
** Form generated from reading UI file 'CPUDebugger.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CPUDEBUGGER_H
#define UI_CPUDEBUGGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CPUDebugger
{
public:
    QGroupBox *groupBox;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *RegAF;
    QLabel *label_2;
    QLineEdit *RegBC;
    QLabel *label_4;
    QLineEdit *RegDE;
    QLabel *label_6;
    QLineEdit *RegHL;
    QLabel *label_8;
    QLineEdit *RegPC;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLineEdit *FlagZ;
    QLineEdit *FlagN;
    QLineEdit *FlagH;
    QLineEdit *FlagC;
    QLabel *label_7;
    QLineEdit *RegSP;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLabel *Opcode;

    void setupUi(QWidget *CPUDebugger)
    {
        if (CPUDebugger->objectName().isEmpty())
            CPUDebugger->setObjectName(QStringLiteral("CPUDebugger"));
        CPUDebugger->resize(222, 213);
        groupBox = new QGroupBox(CPUDebugger);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 40, 161, 161));
        formLayoutWidget = new QWidget(groupBox);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 20, 75, 131));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        RegAF = new QLineEdit(formLayoutWidget);
        RegAF->setObjectName(QStringLiteral("RegAF"));
        RegAF->setMaximumSize(QSize(45, 16777215));

        formLayout->setWidget(0, QFormLayout::FieldRole, RegAF);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        RegBC = new QLineEdit(formLayoutWidget);
        RegBC->setObjectName(QStringLiteral("RegBC"));
        RegBC->setMaximumSize(QSize(45, 16777215));

        formLayout->setWidget(1, QFormLayout::FieldRole, RegBC);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        RegDE = new QLineEdit(formLayoutWidget);
        RegDE->setObjectName(QStringLiteral("RegDE"));
        RegDE->setMaximumSize(QSize(45, 16777215));

        formLayout->setWidget(2, QFormLayout::FieldRole, RegDE);

        label_6 = new QLabel(formLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_6);

        RegHL = new QLineEdit(formLayoutWidget);
        RegHL->setObjectName(QStringLiteral("RegHL"));
        RegHL->setMaximumSize(QSize(45, 16777215));

        formLayout->setWidget(3, QFormLayout::FieldRole, RegHL);

        label_8 = new QLabel(formLayoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_8);

        RegPC = new QLineEdit(formLayoutWidget);
        RegPC->setObjectName(QStringLiteral("RegPC"));
        RegPC->setMaximumSize(QSize(45, 16777215));

        formLayout->setWidget(4, QFormLayout::FieldRole, RegPC);

        formLayoutWidget_2 = new QWidget(groupBox);
        formLayoutWidget_2->setObjectName(QStringLiteral("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(90, 20, 65, 131));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_12 = new QLabel(formLayoutWidget_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_12);

        label_13 = new QLabel(formLayoutWidget_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_13);

        label_14 = new QLabel(formLayoutWidget_2);
        label_14->setObjectName(QStringLiteral("label_14"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_14);

        label_15 = new QLabel(formLayoutWidget_2);
        label_15->setObjectName(QStringLiteral("label_15"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_15);

        FlagZ = new QLineEdit(formLayoutWidget_2);
        FlagZ->setObjectName(QStringLiteral("FlagZ"));
        FlagZ->setMaximumSize(QSize(15, 16777215));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, FlagZ);

        FlagN = new QLineEdit(formLayoutWidget_2);
        FlagN->setObjectName(QStringLiteral("FlagN"));
        FlagN->setMaximumSize(QSize(15, 16777215));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, FlagN);

        FlagH = new QLineEdit(formLayoutWidget_2);
        FlagH->setObjectName(QStringLiteral("FlagH"));
        FlagH->setMaximumSize(QSize(15, 16777215));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, FlagH);

        FlagC = new QLineEdit(formLayoutWidget_2);
        FlagC->setObjectName(QStringLiteral("FlagC"));
        FlagC->setMaximumSize(QSize(15, 16777215));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, FlagC);

        label_7 = new QLabel(formLayoutWidget_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_7);

        RegSP = new QLineEdit(formLayoutWidget_2);
        RegSP->setObjectName(QStringLiteral("RegSP"));
        RegSP->setMaximumSize(QSize(45, 16777215));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, RegSP);

        horizontalLayoutWidget = new QWidget(CPUDebugger);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 161, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(45, 16777215));

        horizontalLayout->addWidget(label_3);

        Opcode = new QLabel(horizontalLayoutWidget);
        Opcode->setObjectName(QStringLiteral("Opcode"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Opcode->sizePolicy().hasHeightForWidth());
        Opcode->setSizePolicy(sizePolicy);
        Opcode->setFrameShape(QFrame::StyledPanel);
        Opcode->setFrameShadow(QFrame::Sunken);
        Opcode->setLineWidth(2);

        horizontalLayout->addWidget(Opcode);


        retranslateUi(CPUDebugger);

        QMetaObject::connectSlotsByName(CPUDebugger);
    } // setupUi

    void retranslateUi(QWidget *CPUDebugger)
    {
        CPUDebugger->setWindowTitle(QApplication::translate("CPUDebugger", "CPU Debugger", nullptr));
        groupBox->setTitle(QApplication::translate("CPUDebugger", "Registers", nullptr));
        label->setText(QApplication::translate("CPUDebugger", "AF", nullptr));
        RegAF->setText(QApplication::translate("CPUDebugger", "0x0000", nullptr));
        label_2->setText(QApplication::translate("CPUDebugger", "BC", nullptr));
        RegBC->setText(QApplication::translate("CPUDebugger", "0x0000", nullptr));
        label_4->setText(QApplication::translate("CPUDebugger", "DE", nullptr));
        RegDE->setText(QApplication::translate("CPUDebugger", "0x0000", nullptr));
        label_6->setText(QApplication::translate("CPUDebugger", "HL", nullptr));
        RegHL->setText(QApplication::translate("CPUDebugger", "0x0000", nullptr));
        label_8->setText(QApplication::translate("CPUDebugger", "PC", nullptr));
        RegPC->setText(QApplication::translate("CPUDebugger", "0x0000", nullptr));
        label_12->setText(QApplication::translate("CPUDebugger", "z", nullptr));
        label_13->setText(QApplication::translate("CPUDebugger", "n", nullptr));
        label_14->setText(QApplication::translate("CPUDebugger", "h", nullptr));
        label_15->setText(QApplication::translate("CPUDebugger", "c", nullptr));
        FlagZ->setText(QApplication::translate("CPUDebugger", "0", nullptr));
        FlagN->setText(QApplication::translate("CPUDebugger", "0", nullptr));
        FlagH->setText(QApplication::translate("CPUDebugger", "0", nullptr));
        FlagC->setText(QApplication::translate("CPUDebugger", "0", nullptr));
        label_7->setText(QApplication::translate("CPUDebugger", "SP", nullptr));
        RegSP->setText(QApplication::translate("CPUDebugger", "0x0000", nullptr));
        label_3->setText(QApplication::translate("CPUDebugger", "Opcode: ", nullptr));
        Opcode->setText(QApplication::translate("CPUDebugger", "NOP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CPUDebugger: public Ui_CPUDebugger {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CPUDEBUGGER_H

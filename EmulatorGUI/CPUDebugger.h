#pragma once

#include <QWidget>
#include "ui_CPUDebugger.h"
#include "Emulator.h"

class CPUDebugger : public QWidget
{
	Q_OBJECT

public:
	CPUDebugger(QWidget *parent = Q_NULLPTR);
	~CPUDebugger();
	void Initialize(Emulator* emulator);
private:
	void SetRegisters();
	void NextInstruction();
	bool eventFilter(QObject *obj, QEvent *event);

private:
	Ui::CPUDebugger ui;
	Emulator* emulator;
};

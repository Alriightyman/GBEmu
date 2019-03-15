#pragma once
// Qt headers
#include <QtWidgets/QMainWindow>
#include "ui_EmulatorGUI.h"
// emulator headers
#include "Emulator.h"
class CPUDebugger;

class EmulatorGUI : public QMainWindow
{
	Q_OBJECT

public:
	EmulatorGUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::EmulatorGUIClass ui;
	Emulator emulator;
	CPUDebugger* cpuDebuggerWindow;
private slots:

	void UpdateEmulator();
	void OpenROM();
	void Exit();
	void OpenCPUDebugger();
};

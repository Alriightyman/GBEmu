#include "EmulatorGUI.h"
#include "OpenGLRenderWidget.h"
#include <qtimer.h>
#include <qopenglwidget.h>
#include <qfiledialog.h>
#include "CPUDebugger.h"

EmulatorGUI::EmulatorGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	emulator.Initialize();

	auto pTimer = new QTimer(this);
	connect(pTimer, &QTimer::timeout, this, &EmulatorGUI::UpdateEmulator);
	pTimer->start(1000 / 60.0);
}

void EmulatorGUI::UpdateEmulator()
{
	emulator.Run();
}

void EmulatorGUI::OpenROM()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Gameboy ROM"),".//", tr("Gameboy ROM Files (*.gb *.bin )"));
	emulator.LoadROM(fileName.toStdString());
}

void EmulatorGUI::Exit()
{
}

void EmulatorGUI::OpenCPUDebugger()
{
	cpuDebuggerWindow = new CPUDebugger();
	cpuDebuggerWindow->Initialize(&emulator);
	cpuDebuggerWindow->show();
}

#include "CPUDebugger.h"
#include <string>
#include <QKeyEvent>

using namespace Gameboy;

CPUDebugger::CPUDebugger(QWidget *parent)
	: QWidget(parent)
{
	qApp->installEventFilter(this);
	ui.setupUi(this);
}

CPUDebugger::~CPUDebugger()
{
	this->emulator->Pause(false);
	this->emulator = nullptr;
}

void CPUDebugger::Initialize(Emulator * emulator)
{
	this->emulator = emulator;
	this->emulator->Pause(true);
	SetRegisters();
}

void CPUDebugger::NextInstruction()
{
	emulator->Step();
	SetRegisters();
}

bool CPUDebugger::eventFilter(QObject * obj, QEvent * event)
{
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = (QKeyEvent *)(event);
		if (keyEvent->key() == Qt::Key_F5)
		{
			NextInstruction();
		}	
	}
	return QObject::eventFilter(obj, event);
}

void CPUDebugger::SetRegisters()
{
	auto cpu = emulator->GetCPU();
	std::string opcode = cpu->PrintOpcode();
	ui.Opcode->setText(QString::fromStdString(opcode));
	ui.RegAF->setText(QString::fromStdString(cpu->PrintRegister("AF")));
	ui.RegBC->setText(QString::fromStdString(cpu->PrintRegister("BC")));
	ui.RegDE->setText(QString::fromStdString(cpu->PrintRegister("DE")));
	ui.RegHL->setText(QString::fromStdString(cpu->PrintRegister("HL")));
	ui.RegSP->setText(QString::fromStdString(cpu->PrintRegister("SP")));
	ui.RegPC->setText(QString::fromStdString(cpu->PrintRegister("PC")));
	ui.FlagZ->setText(QString::fromStdString(cpu->PrintRegister("FlagZ")));
	ui.FlagN->setText(QString::fromStdString(cpu->PrintRegister("FlagN")));
	ui.FlagH->setText(QString::fromStdString(cpu->PrintRegister("FlagH")));
	ui.FlagC->setText(QString::fromStdString(cpu->PrintRegister("FlagC")));
}

#pragma once

#include <QWidget>

class OpenGLRenderWidget : public QWidget
{
	Q_OBJECT

public:
	OpenGLRenderWidget(QWidget *parent);
	~OpenGLRenderWidget();
};

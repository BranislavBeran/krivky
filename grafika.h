#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Grafika.h"
#include <QDebug>
#include <math.h>
#include "QtClass.h"
#include <QMessageBox>

class Grafika : public QMainWindow
{
	Q_OBJECT

public:
	Grafika(QWidget *parent = Q_NULLPTR);

private:
	Ui::GrafikaClass ui;
	QtClass widgetNaKreslenie;
	public slots:
	void bezier() { widgetNaKreslenie.typKrivky(0); }
	void bsplain() { widgetNaKreslenie.typKrivky(1); }
	void vymaz() { widgetNaKreslenie.vymaz();}
};

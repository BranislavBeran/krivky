#include "Grafika.h"

Grafika::Grafika(QWidget *parent)
	: QMainWindow(parent)
{
	
	test
	
	
	
	ui.setupUi(this);
	
	
	
	
	ui.scrollArea->setWidget(&this->widgetNaKresl       enie);
	ui.scrollArea->setBackgroundRole(QPalette::Dark);
	widgetNaKreslenie.newImage(700, 700);
	widgetNaKreslenie.initImage(); 
}


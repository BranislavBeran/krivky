#pragma once

#include <QWidget>
#include <QImage>
#include <QColor>
#include <QtWidgets>
#include <vector>
#include <QColorDialog>
#include <algorithm>
//#include <QPainter> nepotrebujeme, lebo QtWidgets to zahrna
//#include <QRect>
#define h 0.1


class QtClass : public QWidget
{
	Q_OBJECT

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	std::vector<QPoint> points;
	QRgb* data;
	int row;
	std::vector< std::vector<QPoint> > vypocitaneBody;
	std::vector<QPoint> medziVypocet;
	int a;
public:
	QtClass(QWidget *parent = Q_NULLPTR);
	~QtClass();
	void newImage(int x, int y);
	QColor colorLines=Qt::black;
	QImage *obrazok;
	void SaveImg(QString menoSuboru);
	void drawPoints();
	void drawLine(QPoint A, QPoint B);
	void ulozBod(QPoint &bod);
	void clear();
	int pointsSize() { return points.size(); }
	void initImage();
	void setPixel(int x, int y, QColor color);
	int pocetBodov() { return points.size(); }
	void bezier();
	std::vector<QPoint> prepocet(std::vector<QPoint> P,double t);
	void bspline();
	double C0(double t) { return ((-(t*t*t)/6.0) + (0.5*t*t) - (0.5*t) + 1 / 6.0); }
	double C1(double t) { return ((0.5*(t*t*t)) - (t*t) + (2 / 3.0)); }
	double C2(double t) { return ((-0.5*t*t*t) + (0.5*t*t) + (0.5*t) + (1 / 6.0)); }
	double C3(double t) { return ((t*t*t)/6.0); }
	QPoint prepocet_bspline(QPoint A, QPoint B, QPoint C, QPoint D,double t);
	void typKrivky(int x) { a = x; }
	void vymaz();
};


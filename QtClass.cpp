#include "QtClass.h"

QtClass::QtClass(QWidget *parent)
	: QWidget(parent)
{

}
QtClass::~QtClass()
{
}

void QtClass::drawPoints(             )
{
	for (int i = 0; i < points.size(); i++) {
		setPixel(points[i].x()-1, points[i].y()+1, colorLines);
		setPixel(points[i].x()-1, points[i].y(), colorLines);
		setPixel(points[i].x()-1, points[i].y()-1, colorLines);
		setPixel(points[i].x(), points[i].y()+1, colorLines);
		setPixel(points[i].x(), points[i].y(), colorLines);
		setPixel(points[i].x(), points[i].y()-1, colorLines);
		setPixel(points[i].x()+1, points[i].y()+1, colorLines);
		setPixel(points[i].x()+1, points[i].y(), colorLines);
		setPixel(points[i].x()+1, points[i].y()-1, colorLines);
	}
	update();
}
void QtClass::drawLine(QPoint A,QPoint B)
{
	double m,x,y;
	int dx, dy;
	QPoint C;
	
	dy = B.y() - A.y();
	dx = B.x() - A.x();
	m =dy / (double)dx;
	
	if ((fabs(m)) <= 1) {
		if (A.x() > B.x()) {
			C = B;
			B = A;
			A = C;
		}
		x = A.x();
		y = A.y();
		for (int i = A.x(); i < B.x(); i++) {
			x = x + 1;
			y = y + m;
			setPixel(x,round(y), colorLines);
		}
		
	}
	else {
		if (A.y() > B.y()) {
			C = B;
			B = A;
			A = C;
		}
		x = A.x();
		y = A.y();
		for (int i = A.y(); i < B.y(); i++) {
			x = x + 1/m;
			y = y + 1;
			setPixel(round(x), y, colorLines);
		}

	}
	
	
	update();
}

void QtClass::clear()
{
	obrazok->fill(Qt::white);

	update();
}

void QtClass::initImage()
{
	this->resize(obrazok->size());
	this->setMinimumSize(obrazok->size());

	row = obrazok->bytesPerLine() / 4;
	data = (QRgb *)obrazok->bits();
}

void QtClass::setPixel(int x, int y, QColor color)
{
	data[x + y*row] = color.rgb();
}

void QtClass::bezier()
{
	QPoint Pomocny, P0 = points[0];
	double t;

	while (t <= 1-h) {
		t = t + h;
		vypocitaneBody.push_back(prepocet(points, t));
		for (int i = 0; i < points.size() - 2; i++) {
			if (vypocitaneBody[i].size() != 2) {
				vypocitaneBody.push_back(prepocet(vypocitaneBody[i], t));
			}
			else {
				medziVypocet=prepocet(vypocitaneBody[i], t);
				Pomocny = medziVypocet[0];
				drawLine(P0, Pomocny);
				P0 = Pomocny;
				medziVypocet.clear();
			}

		}
		vypocitaneBody.clear();
	}

}

std::vector<QPoint> QtClass::prepocet(std::vector<QPoint> P,double t)
{
	std::vector<QPoint> R;

	for (int i = 0; i < P.size() - 1; i++) {
		R.push_back(QPoint(P[i].x() + (int)(t*(P[i+1].x() - P[i].x())), P[i].y() + (int)(t*(P[i+1].y() - P[i].y()))));
	}
	
	return R;
}

void QtClass::bspline()
{
	double t=0;
	QPoint a, b;

	a = prepocet_bspline(points[0], points[1], points[2], points[3], t);

	for (int i = 0; i < points.size() - 3; i++) {
		while (t <= 1 - 2*h) {			b = prepocet_bspline(points[i], points[i + 1], points[i + 2], points[i + 3], t+h);
			drawLine(a, b);
			a = b;
			t = t + h;
		}
		t = 0;
	}
}

QPoint QtClass::prepocet_bspline(QPoint A, QPoint B, QPoint C, QPoint D,double t)
{
	return QPoint(A.x()*C0(t) + B.x()*C1(t) + C.x()*C2(t) + D.x()*C3(t), A.y()*C0(t) + B.y()*C1(t) + C.y()*C2(t) + D.y()*C3(t));
}

void QtClass::vymaz()
{
	clear();
	points.clear();
}


void QtClass::ulozBod(QPoint &bod)
{
	points.push_back(bod);
}

void QtClass::newImage(int x, int y)
{
	obrazok = new QImage(x, y, QImage::Format_RGB32);
	obrazok->fill(Qt::white);
	
	this->setMinimumSize(obrazok->size());

	update();
}

void QtClass::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QRect area = event->rect();
	painter.drawImage(area, *obrazok, area);
}

void QtClass::mousePressEvent(QMouseEvent *event)
{
	clear();
	if (event->button() == Qt::LeftButton)
	{
		
		ulozBod(event->pos());
		drawPoints();

	}
	if (event->button() == Qt::RightButton && points.size()>2)
	{
		drawPoints();
		if (a == 0&& points.size()>2) {
			bezier();
		}
		else if(a==1&& points.size()>3) {
			bspline();
		}
	}
}


void QtClass::SaveImg(QString menoSuboru)
{
	if (obrazok->save(menoSuboru, "png"))
		qDebug() << "ulozene";
	else
		qDebug() << "zlyhalo";
}



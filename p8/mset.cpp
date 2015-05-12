#include <QtGui>
#include "mset.h"

// for our timer function:
#include <time.h>
#include <inttypes.h>

// for debugging:
#include <iostream>
using std::cout;
using std::endl;


// hack: keep a variable to let us know if the application
// has been initialized so that we can draw the set on startup
bool drawnYet = false;


// In case you want to time your routines, the following function
// should give you a microsecond timer.
uint64_t clockGetTime_mu()
{
	timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (uint64_t)ts.tv_sec * 1000000LL + (uint64_t)ts.tv_nsec / 1000LL;
}

mandelbrotArea::mandelbrotArea(QWidget *parent) : QWidget(parent)
{
	// set our inital view to hold the entire mandelbrot set.
	// a 3x3 square with -2,-1.5 as the lower left should work.
	llCoord.real = -2;
	llCoord.imag = 1.5;
	windowWidth = 3;
	this->maxIterations = 200; // a decent default
	setAttribute(Qt::WA_StaticContents);
}

bool mandelbrotArea::saveImage(const QString &fileName, const char *fileFormat)
{
	QImage visibleImage = image;
	resizeImage(&visibleImage, size());
	visibleImage.save(fileName, fileFormat);
	return true;
}

void mandelbrotArea::refreshImage()
{
	//if(!drawnYet){ this-> render();} 
	
	update(); // repaint screen contents
	return;
}

void mandelbrotArea::mouseDoubleClickEvent(QMouseEvent *event)
{
	QImage visibleImage = image;
	if(event->button() == Qt::LeftButton){
	cout << "left double click" << endl;
	resizeImage(&visibleImage, (size()/2));
	}
	else if(event->button() == Qt::RightButton){
	cout << "right double click"<<endl;
	resizeImage(&visibleImage, (size()/2));
	}
	update();
	return;
	// TODO: write the code for the zoom operation.  You can get
	// the mouse button from event->button() and check for 
	// event->button() == Qt::LeftButton, etc. to figure out what
	// button is being pressed.
}

void mandelbrotArea::mousePressEvent(QMouseEvent *event)
{
	// if you want your application to respond to mouse
	// clicks, implement this function.  You can figure out
	// which mouse button was pressed by examining event->button()
	// and you can get the position from event->pos()
}

void mandelbrotArea::mouseMoveEvent(QMouseEvent *event)
{
	// This will be called whenever the mouse moves across your
	// window.  Might be useful for dragging the image, should
	// you decide to implement it.
}

void mandelbrotArea::mouseReleaseEvent(QMouseEvent *event)
{
	// this would be useful to implement the drag operation.
}

void mandelbrotArea::paintEvent(QPaintEvent *event)
{
	// check: if blank, render first.
	if (!drawnYet) {
		drawnYet = true;
		this->render();
	}
	// otherwise, just repaint the portion of the screen that needs it.
	QPainter painter(this);
	QRect dirtyRect = event->rect();
	painter.drawImage(dirtyRect, image, dirtyRect);
}

void mandelbrotArea::resizeEvent(QResizeEvent *event)
{
	resizeImage(&image, QSize(width(), height()));
	update();
	QWidget::resizeEvent(event);
	return;
}

void mandelbrotArea::render()
{
	// TODO: write this function.
	// draw the portion of the mandelbrot set that lies in our window.
	// idea: loop through all the pixels, iterate the function figure out how
	// quickly the  is diverging, and color it based on the result

	// to give you some idea of what you need to do, I've drawn a nice green
	// gradient on the screen.  You will want to set the individual pixels
	// using the qp.drawPoint(x,y) function, instead of drawing a line.

	QPainter qp(&image);
	QColor qc;
	QPen qpen;
	// get the dimensions of our image in terms of pixels:
	unsigned long iwidth = image.width();
	unsigned long iheight = image.height();
	double unit = 3.0 / iwidth; // on a scale of 0-1, how wide is a pixel?
	double unitY = 3.0 / iheight;

	for (unsigned long i = 0; i < iwidth; i++)
	{
		double x_real = ((unit*i)-2);
		for (unsigned long j = 0; j < iheight; j++){
			double y_imag = (-(unitY*j)+1.5);
			complex* point = new complex(x_real,y_imag);
			complex* cons = new complex(x_real,y_imag);		
			bool inSet = true;
			for(unsigned n = 0; n<30; n++){
				if (point->norm()>2) {
					inSet = false; 
					qc.setRgbF(n*unit,sqrt(n*unit),n*unit);
					break ; }
				//*point = ((*point)*(*point))+(*cons);	
				double oldReal = point->real; double oldImag = point->imag ;
				point->real = ((oldReal*oldReal))-(oldImag*oldImag)+(cons->real);
				point->imag = (2.0*(oldImag*oldReal)+(cons->imag));			
			}
			if(inSet){
				qc.setRgbF(0,0,0);
			}
			qpen.setColor(qc);
			qp.setPen(qpen);
			qp.drawPoint(i,j);
		}
	}

	//for (unsigned long i = 0; i < iwidth; i++) {
	//	qc.setRgbF(i*unit,sqrt(i*unit),i*unit); // set the color we want to draw.
	//	qpen.setColor(qc); // apply the color to the pen
	//	qp.setPen(qpen);   // set the painter to use that pen
	//	qp.drawLine(i,0,i,iheight); // draw a line of the specified color.
	//}
	update(); // repaint screen contents
	return;
}

void mandelbrotArea::resizeImage(QImage *image, const QSize &newSize)
{
	// your custom resize code would go here...
	image->size() = newSize;
		
	if (image->size() == newSize)
		return;

	// for now, we will just expand our image with blank (white) space.
	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));
	QPainter painter(&newImage);
	painter.drawImage(QPoint(0, 0), *image);
	*image = newImage;
}

unsigned long mandelbrotArea::getIterations()
{
	/* NOTE: this is used by MainWindow for the initial value to place
	 * in the iteration control dialog. */
	return this->maxIterations;
}

void mandelbrotArea::setIterations(unsigned long newMax)
{
	/* NOTE: this is called by MainWindow once the iterations
	 * dialog has been processed. */
	this->maxIterations = newMax;
}

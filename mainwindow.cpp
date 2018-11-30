#include "mainwindow.h"
//#include <QtDebug>

extern bool showNestedBall;

MainWindow::MainWindow(unique_ptr<UniversalEngine> pool_scene, QWidget *parent)
    : QMainWindow(parent), updater(this), ticker(this), timer(), scene(std::move(pool_scene)), button("Toggle", this)
{
    this->resize(this->scene->size());
	connect(&this->updater, SIGNAL(timeout()), this, SLOT(nextFrame()));
	connect(&this->ticker, SIGNAL(timeout()), this, SLOT(tick()));

	this->updater.start(1000 / FRAME_RATE);
	this->ticker.start(1000 / TICK_RATE);
	this->timer.start();
    connect(&button, SIGNAL(clicked(bool)), this,  SLOT(onButtonPress()));
    button.setGeometry(-2, scene->size().height() - 100, scene->size().width()+5, 40);
//    button.pos()

//    qDebug() << "constructor mainwindow";
}

void MainWindow::nextFrame() {
	this->update();
//    qDebug() << "updating";
}

void MainWindow::onButtonPress(){showNestedBall = !showNestedBall;}

void MainWindow::tick() {
    double dtime = timer.restart() / 1000.0;
	this->scene->tick(dtime);
}

void MainWindow::paintEvent(QPaintEvent *) {
//    qDebug() << "paintevent";
	QPainter painter(this);
	this->scene->draw(painter);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
//    scene->
    scene->mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    scene->mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    scene->mouseMoveEvent(event);
}

MainWindow::~MainWindow()
{
//    delete scene;
}

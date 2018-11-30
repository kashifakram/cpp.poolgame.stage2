#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>
#include <QPainter>
#include <QPushButton>

#include "util.h"
#include "universalengine.h"

/**
 * @brief The top level class for controlling the window
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
		/**
		 * @brief Constructor
		 *
		 * @param scene a Scene for the program to render
		 * @param parent the parent Qt Object
		 */
    MainWindow(unique_ptr<UniversalEngine> scene, QWidget* parent = 0);
    ~MainWindow();
public slots:
	/**
	 * @brief move the scene by a small timestep
	 */
	void tick();
	/**
	 * @brief draws the next frame
	 */
	void nextFrame();

    void onButtonPress();

protected:
/**
 * @brief draws objects on the window
 *
 * @param event specifies regions to render
 */
	void paintEvent(QPaintEvent* event);

    /*!
     * \brief mouse events to be used in stage 2 engine
     * to handle power bar, strength and click power of
     * cueue bar by calculalting the time elapsed between mouse
     * \param event
     */
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
	QTimer updater;
	QTimer ticker;
	QElapsedTimer timer;
    unique_ptr<UniversalEngine> scene;
    QPushButton button;

};

#endif // MAINWINDOW_H

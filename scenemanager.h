#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "util.h"
#include "graphic.h"
#include "table.h"
#include "ball.h"

#include <QElapsedTimer>
#include <QSize>
#include <QPaintEvent>

class SceneManager : public Graphic
{
public:
	/**
	 * @brief SceneManager Constructor
	 *
	 * @param table
	 * @param balls
	 */
	SceneManager(unique_ptr<Table> table, vector<unique_ptr<Ball>>& balls);
    virtual ~SceneManager() {}
	/**
	 * @brief take a timestep of size dtime
	 *
	 * @param dtime
	 */
    virtual void tick(float dtime);
	/**
	 * @brief draw the current scene
	 *
	 * @param painter for rendering objects
	 */
    virtual void draw(QPainter& painter, QVector2D offset = QVector2D(0,0)) const;
	/**
	 * @brief retrives the size of the scene
	 *
	 * @return the size of the scene
	 */
    QSize veiwPort() const;

protected:
	unique_ptr<Table> table;
	vector<unique_ptr<Ball>> balls;
	QPoint offset;
};


void collideBalls(Ball&, Ball&);
void collideTable(const Table&, Ball&);
QVector2D isTouching(const Ball&, const Ball&);
QVector2D isTouching(const Table&, const Ball&);


#endif // SCENEMANAGER_H

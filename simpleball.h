#ifndef SIMPLEBALL_H
#define SIMPLEBALL_H

#include "ball.h"
#include <QColor>

class SimpleBall : public Ball
{
public:
	/**
	 * @brief SimpleBall Constructor
	 *
	 * @param radius
	 * @param color
	 * @param mass : use 0 for infinite mass
	 * @param position
	 * @param velocity
	 */
	SimpleBall(
		float radius, const QColor& color,
		float mass = 0,
		const QVector2D& position = NULL_2D,
		const QVector2D& velocity = NULL_2D
	);
	/**
	 * @brief Draws the ball onto the scene
	 *
	 * @param painter for rendering the ball
	 */
    void draw(QPainter& painter, QVector2D offset = QVector2D(0, 0)) const;

    QColor getBallColor();
private:
	QColor color;
};

#endif // SIMPLEBALL_H

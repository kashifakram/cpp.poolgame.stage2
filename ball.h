#ifndef BALL_H
#define BALL_H

#include "util.h"
#include "graphic.h"
#include <QVector2D>
#include <QColor>

/**
 * @brief The Ball class is not responsible for physics calculation
 *        it exposes public radius position, velocity and mass fields
 *        so the responsible class can access them directly.
 *        You can pretend it's a struct if you like.
 */
class Ball : public Graphic
{
public:
    bool m_isDestroyed;
	float radius;
	float mass;
	QVector2D position;
	QVector2D velocity;
	/**
	 * @brief Constructor for ball
	 *
	 * @param radius used for collision detection
	 * @param mass used for physics
	 * @param pos initial poisiton for the ball
	 * @param vel inital velocity for the ball
	 */
	Ball(
		float radius = 0, float mass = 0,
		const QVector2D& pos = NULL_2D,
		const QVector2D& vel = NULL_2D
    ) : m_isDestroyed(false), radius(radius), mass(mass), position(pos), velocity(vel) {}
	virtual ~Ball() {}
    virtual bool getIsDestroyed(){return m_isDestroyed;}
    virtual void setIsDestroyed(){m_isDestroyed = !m_isDestroyed;}
    virtual QColor getBallColor() = 0;
    virtual bool isCueBall(){return false;}
    virtual void setCueBall(){}
    virtual std::vector<std::unique_ptr<Ball>>* manageBallCollision(const QVector2D&){return nullptr;}
protected:
    void addBalls(Ball*){}
private:

};

#endif // BALL_H

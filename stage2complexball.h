#ifndef STAGE2COMPLEXBALL_H
#define STAGE2COMPLEXBALL_H

#include "util.h"
#include "ball.h"
#include <QVector2D>
#include <QColor>

class Stage2ComplexBall : public Ball
{
public:
    float radius;
    float mass;
    QVector2D position;
    QVector2D velocity;

    /**
     * @brief Constructor for Stage2ComplexBall
     *
     * @param radius used for collision detection
     * @param mass used for physics
     * @param pos initial poisiton for the ball
     * @param vel inital velocity for the ball
     */
    Stage2ComplexBall(
        float radius = 0, float mass = 0,
        const QVector2D& pos = NULL_2D,
        const QVector2D& vel = NULL_2D
    ) : radius(radius), mass(mass), position(pos), velocity(vel) {}
    virtual ~Stage2ComplexBall() {}
};

#endif // STAGE2COMPLEXBALL_H

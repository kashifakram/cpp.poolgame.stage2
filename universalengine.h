#ifndef UNIVERSALENGINE_H
#define UNIVERSALENGINE_H

#include "ball.h"
#include "table.h"

#include <QMouseEvent>
#include <QPainter>
#include <QSize>
class UniversalEngine : public Graphic
{
public:
    /*!
     * \brief UniversalEngine constructor
     */
    UniversalEngine(){}

    virtual ~UniversalEngine(){}

    /*!
     * \brief mousePressEvent to be used by stage 2 engine
     * to handle mouse press event
     * \param event
     */
    virtual void mousePressEvent(QMouseEvent *event) = 0;

    /*!
     * \brief mouseReleaseEvent to be used by stage 2 engine
     * to handle mouse release event
     * \param event
     */
    virtual void mouseReleaseEvent(QMouseEvent *event) = 0;

    /*!
     * \brief mouseMoveEvent to be used by stage 2 engine
     * to handle mouse move event
     * \param event
     */
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;

    /**
     * @brief take a timestep of size dtime
     *
     * @param dtime
     */
    virtual void tick(float dtime) = 0;

    /*!
     * \brief findCueBall
     * \return ball marked as cueue ball
     */
    virtual Ball * findCueBall() = 0;

    /*!
     * \brief IsGameFinished
     * \return
     */
    virtual bool IsGameFinished() = 0;

    /*!
     * \brief size
     * \return scene size
     */
    virtual QSize size() = 0;
};

#endif // UNIVERSALENGINE_H

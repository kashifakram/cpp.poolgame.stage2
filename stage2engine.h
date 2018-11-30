#ifndef STAGE2ENGINE_H
#define STAGE2ENGINE_H

#include "util.h"
#include "graphic.h"
#include "ball.h"
#include "table.h"
#include "universalengine.h"
#include "pocket.h"

#include <QMouseEvent>
#include <QElapsedTimer>
#include <QSize>
#include <QPaintEvent>

/*!
 *\brief The Stage2Engine class
 */
class Stage2Engine : public UniversalEngine
{
public:
    /*!
     * \brief mousePressEvent to record initial velocity
     * and start timer upon clicking on cueue ball
     * \param event
     */
    void mousePressEvent(QMouseEvent *event) override;

    /*!
     * \brief mouseReleaseEvent to handle mouse release
     * hit cueue ball, set collided ball velocity,
     * break ball based on strength
     * \param event
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

    /*!
     * \brief mouseMoveEvent to set mouse position and
     * direction to release cueue ball
     * \param event
     */
    void mouseMoveEvent(QMouseEvent *event) override;

    /**
     * @brief SceneManager Constructor
     *
     * @param table
     * @param balls
     */
    Stage2Engine(std::unique_ptr<Table> table, vector<std::unique_ptr<Ball>> balls);

    ~Stage2Engine(){}
    /**
     * @brief take a timestep of size dtime
     *
     * @param dtime
     */

    void tick(float dtime) override;
    /**
     * @brief draw the current scene
     *
     * @param painter for rendering objects
     */

    void draw(QPainter& painter, QVector2D offset = QVector2D(0,0)) const override;

    /*!
     * \brief size
     * \return stage 2 scene size
     */
    QSize size() override;

    /*!
     * \brief findCueBall
     * \return pointer to cueue ball
     */
    Ball * findCueBall();

    /*!
     * \brief IsGameFinished
     * \return
     */
    bool IsGameFinished();

    /*!
     * \brief setIsClicked setting ball clicked property
     * \param clicked
     */
    void setIsClicked(bool clicked);

    /*!
    * \brief pushCueueBall
    */
   void pushCueueBall();

private:
   void BallToBallCollision(Ball *ballA, Ball *ballB);
   void BallToTableCollision(Table *table, Ball *ballA);
   void CalculateFriction(Ball *ball, double friction, qint64 prevTime, qint64 currTime);

   double GetDistanceBetweenPositions(QVector2D positionA, QVector2D positionB);

   bool WereBallsCollided(Ball *ballA, Ball *ballB);

   void BallInPocket(Table *table, Ball *ball);

    std::unique_ptr<Table> m_table;
    vector<std::unique_ptr<Ball>> m_balls;
    vector<std::unique_ptr<Ball>> m_tempBalls;
    QPoint m_offset;
    QElapsedTimer m_timer;
    QVector2D m_mousePos;
    bool m_clicked;
    float m_clickPower;
    bool m_showIndicators;
};

#endif // STAGE2ENGINE_H

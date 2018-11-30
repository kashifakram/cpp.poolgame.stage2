#ifndef STAGE2COMPLEXCONCRETEBALL_H
#define STAGE2COMPLEXCONCRETEBALL_H

#include <iostream>
#include <QBrush>
#include <QPen>
#include "ball.h"
#include <QVector2D>


/*!
 * \brief The Stage2ComplexConcreteBall class is extension of original ball to be used in stage 2
 */
class Stage2ComplexConcreteBall : public Ball
{
public:
    /*!
     * \brief Stage2ComplexConcreteBall constructor
     * \param color to set ball color
     * \param strength stage 2 ball strength
     * \param m_isCueBall flag to set cueue ball
     * \param radius ball radius
     * \param mass ball mass
     * \param position ball position on table
     * \param velocity ball velocity
     */
    Stage2ComplexConcreteBall(
        const QColor& color,
        const float strength,
        bool m_isCueBall = false,
        float radius = 0,
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
    void addBalls(unique_ptr<Ball> ball);

    /*!
     * \brief getStrength ball strength getter
     * \return
     */
    float getStrength();

    /*!
     * \brief getBallColor ball color getter
     * \return
     */
    QColor getBallColor();

    /*!
     * \brief getCombinedMass ball mass including child balls
     * \return
     */
    float getCombinedMass();

    /*!
     * \brief getNumberOfChildBalls return total child balls inside parent
     * \return
     */
    int getNumberOfChildBalls();

    /*!
     * \brief getRadius
     * \return ball radius
     */
    float getRadius();

    /*!
     * \brief getPosition
     * \return ball position vecotr
     */
    QVector2D getPosition();

    /*!
     * \brief getVelocity
     * \return ball velocity vector
     */
    QVector2D getVelocity();

    /*!
     * \brief isCueBall
     * \return if ball is cueue
     */
    bool isCueBall();

    /*!
     * \brief setCueBall set current ball as cueue ball
     */
    void setCueBall();

    /*!
     * \brief manageBallCollision to process ball collision accoording to change in velocity
     * ball mass, strength, radius, child balls, to check if ball is destroyed bcoze of
     * stronger collision than it mass
     * \param inputDeltaV change in ball velocity
     * \return
     */
    std::vector<std::unique_ptr<Ball>>* manageBallCollision(const QVector2D& inputDeltaV);

    /*!
     * \brief getIsDestroyed
     * \return flag if ball is destroyed
     */
    bool getIsDestroyed();

    /*!
     * \brief setIsDestroyed set when ball is destroyed
     */
    void setIsDestroyed();

    /*!
     * \brief getChildren
     * \return vector of childern ball
     */
    std::vector<std::unique_ptr<Ball>> *getChildren();

private:
    QColor m_color;
    float m_strength;
    std::vector<std::unique_ptr<Ball>> m_balls;
    bool m_isCueBall;
//    QJsonArray m_jsonballs;
};

#endif // STAGE2COMPLEXCONCRETEBALL_H

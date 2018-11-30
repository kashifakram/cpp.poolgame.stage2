#ifndef POCKET_H
#define POCKET_H

#include "util.h"
#include "graphic.h"
#include <QVector2D>

class Pocket : public Graphic
{
public:
    /*!
     * \brief Pocket Constructor
     * \param position from config file
     * \param radius of pocket, default is 20
     */
    Pocket(QVector2D position, float radius = 20);

    /*!
     * \brief GetPosition helper getter method
     * \return m_position vector
     */
    QVector2D GetPosition();

    /*!
     * \brief GetRadius helper getter method
     * \return pocket radius
     */
    float GetRadius();

    /*!
     * \brief graphic draw method to be used to draw pockets
     * \param painter
     * \param offset
     */
    void draw(QPainter& painter, QVector2D offset = QVector2D(0, 0)) const;

private:
    /*!
     * \brief m_position private position
     */
    QVector2D m_position;

    /*!
     * \brief m_radius
     */
    float m_radius;
};

#endif // POCKET_H

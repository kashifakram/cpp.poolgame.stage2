#include "pocket.h"

Pocket::Pocket(
    QVector2D position,
    float radius
):m_position(position), m_radius(radius){}

void Pocket::draw(QPainter& painter, QVector2D) const {
    QBrush brush("black");
    painter.setBrush(brush);
    painter.drawEllipse(
        this->m_position.toPointF(),
        this->m_radius, this->m_radius
    );
}

QVector2D Pocket::GetPosition()
{
    return m_position;
}

float Pocket::GetRadius()
{
    return m_radius;
}

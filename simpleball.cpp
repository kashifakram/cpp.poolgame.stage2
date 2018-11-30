#include "simpleball.h"
#include <QBrush>
#include <QPen>

SimpleBall::SimpleBall(
	float radius, const QColor& color, float mass,
	const QVector2D& pos, const QVector2D& vel
) : Ball(radius, mass, pos, vel), color(color) {}

void SimpleBall::draw(QPainter& painter, QVector2D) const {
	QBrush brush(this->color);
	painter.setBrush(brush);
	painter.drawEllipse(
		this->position.toPointF(),
		this->radius, this->radius
	);
}

QColor SimpleBall::getBallColor()
{
    return color;
}

#include "simpletable.h"
#include <QBrush>
#include <QPolygon>

SimpleTable::SimpleTable(const QSize& dim, const QColor& color, float friction)
: Table(dim, friction), color(color) {}

void SimpleTable::draw(QPainter& painter, QVector2D) const {
	QBrush brush(this->color);
	painter.setBrush(brush);
	painter.drawRect(QRect(QPoint(), this->dimension));
}

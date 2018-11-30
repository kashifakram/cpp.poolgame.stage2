#include "stage2complexconcretetable.h"

Stage2ComplexConcreteTable::Stage2ComplexConcreteTable(const QSize& dim,
                                                       const QColor& color,
                                                       float friction
                                                       )
: Table(dim, friction), m_color(color){}

void Stage2ComplexConcreteTable::draw(QPainter& painter, QVector2D) const {
    QBrush brush(this->m_color);
    painter.setBrush(brush);
    painter.drawRect(QRect(QPoint(), this->dimension));
    for(const auto & p : m_pockets){
        p->draw(painter);
    }
}

void Stage2ComplexConcreteTable::addPockets(unique_ptr<Pocket> pocket)
{
    m_pockets.emplace_back(std::move(pocket));
}

const vector<std::unique_ptr<Pocket>>* Stage2ComplexConcreteTable::getPockets()
{
    return &m_pockets;
}

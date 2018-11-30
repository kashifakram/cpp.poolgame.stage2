#include "stage1engine.h"

Stage1Engine::Stage1Engine(unique_ptr<Table> table, vector<unique_ptr<Ball>>& balls)
    : m_manager(std::move(table), balls)
{

}

Stage1Engine::~Stage1Engine(){}

void Stage1Engine::mousePressEvent(QMouseEvent *event)
{

}

void Stage1Engine::mouseReleaseEvent(QMouseEvent *event)
{
}

void Stage1Engine::mouseMoveEvent(QMouseEvent *event)
{
}

void Stage1Engine::tick(float dtime)
{
    m_manager.tick(dtime);
}

void Stage1Engine::draw(QPainter &painter, QVector2D) const
{
    m_manager.draw(painter);
}

Ball *Stage1Engine::findCueBall()
{
    return nullptr;
}

bool Stage1Engine::IsGameFinished()
{
    return false;
}

QSize Stage1Engine::size()
{
    return m_manager.veiwPort();
}

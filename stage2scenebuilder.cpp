#include "stage2scenebuilder.h"

Stage2SceneBuilder::Stage2SceneBuilder(){}

void Stage2SceneBuilder::setTable(unique_ptr<Table> table) {
    this->m_table = std::move(table);
}

void Stage2SceneBuilder::addBall(unique_ptr<Ball> ball) {
    this->m_balls.push_back(std::move(ball));
}

unique_ptr<UniversalEngine> Stage2SceneBuilder::build() {
    return unique_ptr<Stage2Engine>(
        new Stage2Engine(std::move(m_table), std::move(m_balls))
    );
}

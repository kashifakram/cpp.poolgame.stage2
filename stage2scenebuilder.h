#ifndef STAGE2SCENEBUILDER_H
#define STAGE2SCENEBUILDER_H

#include "stage2engine.h"
#include "scenemanager.h"


class Stage2SceneBuilder
{
public:
    Stage2SceneBuilder();
    ~Stage2SceneBuilder(){}

    /**
     * @brief sets the table for the scene
     *        table can only be used once
     *
     * @param table
     */
    void setTable(unique_ptr<Table> table);

    /**
     * @brief adds ball to scene
     *        ball can only be used once
     *
     * @param ball
     */
    void addBall(unique_ptr<Ball> ball);

    /**
     * @brief remove all balls from scene
     */
    void resetBalls();

    /**
     * @brief creates scene
     *        a table must be set
     *
     * @return the scene with set table and balls
     */
    unique_ptr<UniversalEngine> build();

private:
    unique_ptr<Table> m_table;
    vector<unique_ptr<Ball>> m_balls;
};

#endif // STAGE2SCENEBUILDER_H

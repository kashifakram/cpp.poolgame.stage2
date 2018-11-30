#ifndef SCENEBUILDER_H
#define SCENEBUILDER_H

#include "universalengine.h"
#include "stage1engine.h"

class SceneBuilder
{
public:
	/**
	 * @brief Constructor
	 */
	SceneBuilder() {}
    virtual ~SceneBuilder() {}

	/**
	 * @brief sets the table for the scene
	 *        table can only be used once
	 *
	 * @param table
	 */
    virtual void setTable(unique_ptr<Table> table);
	/**
	 * @brief adds ball to scene
	 *        ball can only be used once
	 *
	 * @param ball
	 */
    virtual void addBall(unique_ptr<Ball> ball);
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
    virtual unique_ptr<UniversalEngine> build();

private:
	unique_ptr<Table> table;
	vector<unique_ptr<Ball>> balls;
};

#endif // SCENEBUILDER_H

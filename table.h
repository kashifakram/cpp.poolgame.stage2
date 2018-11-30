#ifndef TABLE_H
#define TABLE_H

#include "util.h"
#include "graphic.h"
#include "pocket.h"

#include <QtDebug>

class Table : public Graphic
{
public:
	QSize dimension;
	float surface_friction;

	/**
	 * @brief Constructor for Table
	 *
	 * @param dimension
	 * @param friction
	 */
    Table(const QSize& dimension, float friction = 0)
	: dimension(dimension), surface_friction(friction) {}
    virtual ~Table() {}
    virtual const vector<std::unique_ptr<Pocket>>* getPockets(){return nullptr;}
};

#endif // TABLE_H

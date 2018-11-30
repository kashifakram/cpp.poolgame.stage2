#ifndef SIMPLECREATOR_H
#define SIMPLECREATOR_H

#include "creator.h"

class SimpleCreator : public Creator
{
protected:
	/**
	 * @brief makes a SimpleTable from JSON config
	 *
	 * @param spec a JSON configuration for the table
	 *
	 * @return a SimpleTable with the specified configuration
	 */
	unique_ptr<Table> makeTable(const QJsonObject &spec);
	/**
	 * @brief makes a SimpleBall from the JSON config
	 *
	 * @param spec a JSON configuration for the ball
	 *
	 * @return a SimpleBall with the specified configuration
	 */
	unique_ptr<Ball> makeBall(const QJsonObject &spec);
};

#endif // SIMPLECREATOR_H

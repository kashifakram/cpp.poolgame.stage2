#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QPainter>

class Graphic {
public:
	/**
	 * @brief an interface for rendering object on Qt
	 *
	 * @param painter for rendering the object
	 */
    virtual void draw(QPainter& painter, QVector2D offset = QVector2D(0,0)) const = 0;
};

#endif // GRAPHIC_H

#ifndef STAGE2COMPLEXCONCRETETABLE_H
#define STAGE2COMPLEXCONCRETETABLE_H

#include <QBrush>
#include <QPolygon>
#include "pocket.h"
#include "table.h"

class Stage2ComplexConcreteTable : public Table
{
public:
    /*!
    * \brief Stage2ComplexConcreteTable constructor
    * \param dim table size dimensions
    * \param color table color
    * \param friction friction
    */

   Stage2ComplexConcreteTable(const QSize& dim,
                              const QColor& color,
                              float friction = 0.f);
   /**
    * @brief Draws the table onto the scene
    *
    * @param painter for rendering the table
    */
   void draw(QPainter& painter, QVector2D offset = QVector2D(0, 0)) const;

   /*!
    * \brief addPockets to add pocket on table
    * \param pocket to add
    */
   void addPockets(unique_ptr<Pocket> pocket);

   /*!
    * \brief getPockets
    * \return vector of pocket objects on table
    */
   const std::vector<std::unique_ptr<Pocket>>* getPockets();

private:
   QColor m_color;
   std::vector<std::unique_ptr<Pocket>> m_pockets;
};

#endif // STAGE2COMPLEXCONCRETETABLE_H

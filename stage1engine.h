#ifndef STAGE1ENGINE_H
#define STAGE1ENGINE_H

#include "scenemanager.h"
#include "universalengine.h"

#include <memory>

/*!
 * \brief The Stage1Engine class to be used as adapter between stage2 engine and universal engine
 */
class Stage1Engine : public UniversalEngine
{
public:
    /*!
     * \brief Stage1Engine constructor
     * \param table unique pointer to table
     * \param balls unique pointer to set of balls
     */
    Stage1Engine(unique_ptr<Table> table, vector<unique_ptr<Ball>>& balls);

    ~Stage1Engine();

    /*!
     * \brief mousePressEvent to be used in stage2 engine
     * \param event
     */
    void mousePressEvent(QMouseEvent *event) override;

    /*!
     * \brief mouseReleaseEvent to be used in stage2 engine
     * \param event
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

    /*!
     * \brief mouseMoveEvent to be used in stage2 engine
     * \param event
     */
    void mouseMoveEvent(QMouseEvent *event) override;

    /*!
     * \brief tick
     * \param dtime
     */
    void tick(float dtime) override;

    /*!
     * \brief graphic draw
     * \param painter
     */
    virtual void draw(QPainter &painter, QVector2D) const override;

    /*!
     * \brief findCueBall to find cueue ball to be used in stage 2 engine
     * \return
     */
    Ball *findCueBall() override;

    bool IsGameFinished() override;

    /*!
     * \brief size return scene size
     * \return
     */
    QSize size() override;

private:
    SceneManager m_manager;
};

#endif // STAGE1ENGINE_H

#ifndef STAGE2COMPLEXCONCRETECREATOR_H
#define STAGE2COMPLEXCONCRETECREATOR_H

#include "creator.h"
#include "stage2complexconcreteball.h"
#include "stage2complexconcretetable.h"
#include "pocket.h"
#include "stage2scenebuilder.h"
#include <QVector2D>
#include <QJsonArray>

/*!
 * \brief The Stage2ComplexConcreteCreator class is extension of original creator class
 */
class Stage2ComplexConcreteCreator : public Creator
{
public:
    /*!
     * \brief Stage2ComplexConcreteCreator constructor
     */
    Stage2ComplexConcreteCreator();

    /*!
     * \brief makeScene creating stge 2 game based on config file
     * \param spec
     * \return
     */
    unique_ptr<UniversalEngine> makeScene(const QJsonObject& spec);
protected:
    /*!
     * \brief makeTable to create table based on specifications mentioned in config file
     * \param spec
     * \return
     */
    unique_ptr<Table> makeTable(const QJsonObject &spec);

    /*!
     * \brief makeBall to create ball based on specification in config file
     * \param spec
     * \return
     */
    unique_ptr<Ball> makeBall(const QJsonObject &spec);


private:
    /*!
     * \brief makeChildBall specific to stage 2 engine only
     * where balls can have child balls
     * \param spec child balls specifications from config file
     * \param position child balls position inside parent
     * \return
     */
    unique_ptr<Ball> makeChildBall(const QJsonObject &spec, QVector2D position);

    bool m_cueBallFound;

};

#endif // STAGE2COMPLEXCONCRETECREATOR_H

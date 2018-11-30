#ifndef STAGE2COMPLEXCREATOR_H
#define STAGE2COMPLEXCREATOR_H

#include "creator.h"
#include "scenemanager.h"
#include "scenebuilder.h"
#include <QJsonObject>
#include <QJsonArray>

class Stage2ComplexCreator : public Creator
{
public:
    unique_ptr<SceneManager> makeScene(const QJsonObject& spec);

protected:
    virtual unique_ptr<Table> makeTable(const QJsonObject& spec) = 0;
    virtual unique_ptr<Ball> makeBall(const QJsonObject& spec) = 0;
};

#endif // STAGE2COMPLEXCREATOR_H

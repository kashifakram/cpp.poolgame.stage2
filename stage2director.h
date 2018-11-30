#ifndef STAGE2DIRECTOR_H
#define STAGE2DIRECTOR_H

#include "util.h"
#include "scenemanager.h"
#include "scenebuilder.h"
#include <QJsonObject>
#include "stage2complexconcretecreator.h"

class Stage2Director : Stage2ComplexConcreteCreator
{
public:
    unique_ptr<SceneManager> makeScene(const QJsonObject& spec);
};

#endif // STAGE2DIRECTOR_H

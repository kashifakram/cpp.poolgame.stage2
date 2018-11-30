#include "stage2complexconcretecreator.h"




Stage2ComplexConcreteCreator::Stage2ComplexConcreteCreator() : m_cueBallFound(false){}


unique_ptr<Table> Stage2ComplexConcreteCreator::makeTable(const QJsonObject &spec) {
    unique_ptr<Stage2ComplexConcreteTable> table (new Stage2ComplexConcreteTable(
                                                      QSize(spec["size"].toObject()["x"].toInt(),
                                                      spec["size"].toObject()["y"].toInt()),
                                                      spec["colour"].toString(),
                                                      spec["friction"].toDouble()
                                                      ));


    for(const auto &pocket : spec["pockets"].toArray()){
        unique_ptr<Pocket> p(new Pocket(QVector2D(pocket.toObject()["position"].toObject()["x"].toInt(),
                                                  pocket.toObject()["position"].toObject()["y"].toInt()),
                                        pocket.toObject()["radius"].toDouble(20)));

        table->addPockets(std::move(p));
    }


    // create pockets


    // attach to table
    // return table
    return unique_ptr<Stage2ComplexConcreteTable>(std::move(table));
}

unique_ptr<Ball> Stage2ComplexConcreteCreator::makeChildBall(const QJsonObject &spec, QVector2D position)
{
    unique_ptr<Stage2ComplexConcreteBall> ball (new Stage2ComplexConcreteBall(
                                               spec["colour"].toString("white"),
                                               spec["strength"].toDouble(-1),
                                               false,
                                               spec["radius"].toDouble(10),
                                               spec["mass"].toDouble(1),
                                               QVector2D(spec["position"].toObject()["x"].toDouble(0), spec["position"].toObject()["y"].toDouble(0)),
                                               QVector2D(spec["velocity"].toObject()["x"].toDouble(0), spec["velocity"].toObject()["y"].toDouble(0))
                                               ));
    qDebug() << "nested ball created";
    if (!spec["balls"].isUndefined()){
        for (const auto b : spec["balls"].toArray()){
            if (!b.isUndefined())
                ball->addBalls(std::move(makeChildBall(b.toObject(), ball->position)));
        }
    }
    return ball;

}

unique_ptr<Ball> Stage2ComplexConcreteCreator::makeBall(const QJsonObject &spec) {

    unique_ptr<Stage2ComplexConcreteBall> ball (new Stage2ComplexConcreteBall(
                                               spec["colour"].toString("white"),
                                               spec["strength"].toDouble(-1), false,
                                               spec["radius"].toDouble(10),
                                               spec["mass"].toDouble(1),
                                               QVector2D(spec["position"].toObject()["x"].toDouble(50), spec["position"].toObject()["y"].toDouble(50)),
                                               QVector2D(spec["velocity"].toObject()["x"].toDouble(50), spec["velocity"].toObject()["y"].toDouble(50))
                                               ));
    if(!m_cueBallFound && ball->getBallColor() == QColor(Qt::white)){
        ball->setCueBall();
        m_cueBallFound = true;
    }
    if (!spec["balls"].isUndefined()){
        for (const auto b : spec["balls"].toArray()){
            if (!b.isUndefined())
                ball->addBalls(std::move(makeChildBall(b.toObject(), ball->position)));
        }
    }
    return ball;
}

unique_ptr<UniversalEngine> Stage2ComplexConcreteCreator::makeScene(const QJsonObject& spec)
{   
    Stage2SceneBuilder builder;
    builder.setTable(
        this->makeTable(spec["table"].toObject())
    );
    for (const auto& item : spec["balls"].toArray())
        builder.addBall(
            this->makeBall(item.toObject())
        );


    if(!m_cueBallFound){
        builder.addBall(unique_ptr<Ball>(new Stage2ComplexConcreteBall(QColor(Qt::white), -1, true, 10, 1, QVector2D(10, 10))));
        m_cueBallFound = true;
    }

    return builder.build();
}

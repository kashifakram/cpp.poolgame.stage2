#include "stage2complexcreator.h"

unique_ptr<SceneManager> Stage2ComplexCreator::makeScene(const QJsonObject &spec) {
    SceneBuilder builder;
    if (spec["stage2"] == true){

    } else {
        builder.setTable(
            this->makeTable(spec["table"].toObject())
        );
        for (const auto& item : spec["balls"].toArray())
            builder.addBall(
                this->makeBall(item.toObject())
            );

        return builder.build();
    }

}

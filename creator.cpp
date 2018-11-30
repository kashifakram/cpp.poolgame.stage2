#include "creator.h"
#include "scenebuilder.h"
#include <QJsonArray>

unique_ptr<UniversalEngine> Creator::makeScene(const QJsonObject &spec) {
	SceneBuilder builder;
	builder.setTable(
		this->makeTable(spec["table"].toObject())
	);
	for (const auto& item : spec["balls"].toArray())
		builder.addBall(
			this->makeBall(item.toObject())
		);

    std::unique_ptr<UniversalEngine> scene = builder.build();
    return std::move(scene);
}

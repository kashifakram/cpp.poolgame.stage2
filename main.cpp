#include "mainwindow.h"
#include "simplecreator.h"
#include "stage2complexconcretecreator.h"
#include <QApplication>

#include <QFile>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#define CONFIG_PATH "../Pool/config.json"

bool showNestedBall = true;

int main(int argc, char *argv[])
{
	QFile conf_file(CONFIG_PATH);
    conf_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString content = conf_file.readAll();
    conf_file.close();

	QJsonObject config = QJsonDocument::fromJson(content.toUtf8()).object();

    bool isStage2 = config.take("stage2").toBool(false);
    QApplication a(argc, argv);

    if (isStage2){
        MainWindow w(Stage2ComplexConcreteCreator().makeScene(config));
        w.show();

        return a.exec();
    } else {
        MainWindow w(SimpleCreator().makeScene(config));
        w.show();

        return a.exec();
    }

}

#include "structureReader.h"
#include <QFileInfo>
#include <iostream>
#include <exception>
#include <spdlog/spdlog.h>

structureReader::structureReader()
{

}

QJsonObject structureReader::readStruct(QString fileName)
{
    if(!QFileInfo::exists(fileName)){
        spdlog::error("Read Json Struct: File not exists");
        return QJsonObject();
    }

    QFile jsonFile(fileName);
    jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString jsonContent = jsonFile.readAll();
    jsonFile.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonContent.toUtf8());

    return doc.object();
}

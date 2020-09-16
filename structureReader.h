#ifndef STRUCTUREREADER_H
#define STRUCTUREREADER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class structureReader
{
public:
    structureReader();

    static QJsonObject readStruct(QString fileName);
};

#endif // STRUCTUREREADER_H

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QFile>

#include "include/png2bipcache.h"

Png2BipCache::Png2BipCache()
{
}

bool Png2BipCache::load(const QString &path)
{
    m_map.clear();
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QByteArray jsonData = file.readAll();

    file.close();

    QJsonDocument doc(QJsonDocument::fromJson(jsonData));

    QJsonObject json = doc.object();

    QJsonObject::iterator iterator = json.begin();
    for (; iterator != json.end(); iterator++)
    {
        QJsonObject value = iterator.value().toObject();

        Png2BipCahceVO p2bvo;
        p2bvo.setPngFilePath(value["pngFile"].toString());
        p2bvo.setPngFileMd5String(value["pngFileMd5"].toString());
        p2bvo.setBipFilePath(value["bipFile"].toString());
        p2bvo.setBipFileMd5String(value["bipFileMd5"].toString());

        m_map.insert(iterator.key(), p2bvo);
    }

    return true;
}


bool Png2BipCache::save(const QString &path)
{
    if (m_map.size() < 1)
    {
        return false;
    }

    QJsonObject json;

    QMap<QString, Png2BipCahceVO>::iterator iterator = m_map.begin();
    for( ; iterator != m_map.end(); iterator++)
    {
        QJsonObject value;
        value.insert("pngFile", iterator->pngFilePath());
        value.insert("pngFileMd5", iterator->pngFileMd5String());

        value.insert("bipFile", iterator->bipFilePath());
        value.insert("bipFileMd5", iterator->bipFileMd5String());

        json.insert(iterator->pngFilePath(), value);
    }

    QJsonDocument doc(json);

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
    {
        return false;
    }

    file.write(doc.toJson());
    file.close();

    return true;
}

void Png2BipCache::add(const Png2BipCahceVO &value)
{
    m_map.insert(value.pngFilePath(), value);
}

const Png2BipCahceVO *Png2BipCache::getCacheVO(const QString &key) const
{
    QMap<QString, Png2BipCahceVO>::const_iterator iterator =  m_map.constFind(key);
    if (iterator == m_map.constEnd())
    {
        return NULL;
    }

    return (&iterator.value());
}
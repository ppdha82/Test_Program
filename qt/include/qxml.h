#ifndef QXML_H
#define QXML_H

#include <QtXml>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QAbstractMessageHandler>
#include <QMap>
#include <QDomDocument>

#include "globalDef.h"

class QXml: public QAbstractMessageHandler
{
public:
    QXml();

    QXmlStreamReader xmlReader;
    QXmlStreamReader xmlWriter;
    QXmlStreamAttributes attr_Devices;
    QMap<QString, QString> xmlSettings;
    QString strKeyName;
    QDomDocument xmlSave;

    bool readFile(const QString &fileName);
    bool validation(const QString &xsdFile, const QString &xmlfile);
    bool paserSettings();
    void SaveXml(QString xmlfile, QString key, QString value);
    bool SetAttr(QDomNode& parent, QStringList& key, QString value);
    void SetXmlContent(QString xml);

private:

protected:
    virtual void handleMessage(QtMsgType type, const QString& description, const QUrl& identifier, const QSourceLocation& sourceLocation);


};

#endif // QXML_H

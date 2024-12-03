#include "include/qxml.h"
#include "include/mainwindow.h"

#include <QMessageBox>

QXml::QXml()
{
    SetXmlContent(Table::XmlFile);
}

void QXml::SetXmlContent(QString xml)
{
#if defined(__ENABLE_QT4__)
    QFile file(xml.toAscii());
#else
    QFile file(xml.toLatin1());
#endif  /* __ENABLE_QT4__ */
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    xmlSave.setContent(&file);
    file.close();
}


bool QXml::SetAttr(QDomNode& n, QStringList& key, QString value)
{
    if (n.isNull()) {
        return false;
    }

    if (n.isElement() && n.nodeName() == key.at(0)) {

        QString tmpNodeName = key.at(0);
        key.pop_front();

        while (!n.isNull()) {
            //count 5       4   3       2   1
            //Key   Device  ID  Motor   Ch  Attributes
            if (n.isElement() && (n.toElement().attribute("ID") == key.at(0) || (n.isElement() && n.toElement().attribute("Ch") == key.at(0)) & (n.nodeName() == tmpNodeName))) {
                key.pop_front();

                if (key.count() > 2) {
                    return SetAttr(n, key, value);
                }
                else {
                    QDomElement e = n.toElement();
                    e.setAttribute(key.at(0), value);
                    // e.parentNode().appendChild(e);// if there is no attr, it will be added.

                    return true;
                }
            }
            n = n.nextSibling();
        }
    }

    QDomNode child = n.firstChild();

    if(child.isNull()) {
        child = n.nextSibling();
    }

    return SetAttr(child, key, value);
}

void QXml::SaveXml(QString xmlfile, QString key, QString value)
{
    if (key.isNull()) {
#if defined(__DEBUG_ON__)
        qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] Save xml file~~~~~~" << xmlfile;
#endif  /* __DEBUG_ON__ */
        QFile file(xmlfile);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream stream(&file);
        xmlSave.save(stream, 4);
        file.close();
        readFile(xmlfile); // must read again after save.

        return;
    }

    QStringList findkey = key.split(' ');
    QDomNodeList list = xmlSave.elementsByTagName(findkey.at(0));

    for (int i= 0; i < list.count() ; i++) {
        /*Device Master_R Motor 0 Model*/
        QDomNode parent = list.at(i);

        if(SetAttr(parent, findkey, value)) {
            return;
        }
    }
}

bool QXml::readFile(const QString &fileName)
{
#if defined(__DEBUG_ON__)
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] Enter" << __func__;
#endif  /* __DEBUG_ON__ */
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug()<< "Error: Cannot read file " << qPrintable(fileName) << ": " << qPrintable(file.errorString());
    }

    xmlReader.setDevice(&file);

    QQueue<int> lastKeyLength;
    QMap<QString, int> index;
    int count = 0;

    xmlSettings.clear();

    while (!xmlReader.atEnd()) {
        if (xmlReader.tokenType() == QXmlStreamReader::StartElement) {
            lastKeyLength.push_back(strKeyName.length());
#if defined(__DEBUG_ON__)
            qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] lastKeyLength.count(" << lastKeyLength.count() << ")[" << lastKeyLength.last() << "]; strKeyName[" << strKeyName << "]";
#endif  /* __DEBUG_ON__ */

            QXmlStreamAttributes attr = xmlReader.attributes();

            int count = attr.size();

            if (xmlReader.name() == QString("Settings")) {
                xmlReader.readNext();
                continue;
            }
            else if (xmlReader.name() == QString("DeviceList")) {
                if (strKeyName.isEmpty()) {
                    strKeyName.append(xmlReader.name().toString());
#if defined(__DEBUG_ON__)
                    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] strKeyName[" << strKeyName << "] xmlReader.name()[" << xmlReader.name() << "]";
#endif  /* __DEBUG_ON__ */
                }

                for (int i = 0; i < count; i++) {
                    QString tmpKey(strKeyName);
                    tmpKey.append('.').append(attr.at(i).name().toString());
#if defined(__DEBUG_ON__)
                    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] strKeyName[" << strKeyName << "] attr.at(" << i << ").name()[" << attr.at(i).name() << "]";
#endif  /* __DEBUG_ON__ */
                    if (attr.at(i).name() == "ID") {
                        continue;
                    }
                    else {
                        xmlSettings[tmpKey].append(attr.at(i).value()) ;
                    }
                }
                strKeyName.clear();
                xmlReader.readNext();
                continue;
            }

#if defined(__DEBUG_ON__)
            qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] strKeyName[" << strKeyName << "] count[" << count << "]";
#endif  /* __DEBUG_ON__ */
            if (count > 0) {
                if (strKeyName.isEmpty()) {
                    strKeyName.append(xmlReader.name().toString());
#if defined(__DEBUG_ON__)
                    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] strKeyName[" << strKeyName << "] xmlReader.name()[" << xmlReader.name() << "]";
#endif  /* __DEBUG_ON__ */
                }
                else {
#if defined(__DEBUG_ON__)
                    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] strKeyName[" << strKeyName << "] xmlReader.name()[" << xmlReader.name() << "]";
#endif  /* __DEBUG_ON__ */
                    strKeyName.append('.').append(xmlReader.name().toString());

                    if(index.count(strKeyName) == 0) {  //Add key and intialize to 0
                        index[strKeyName] = 0;
#if defined(__DEBUG_ON__)
                        qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] strKeyName[" << strKeyName << "] index[strKeyName][" << index[strKeyName] << "]";
#endif  /* __DEBUG_ON__ */
                    }
                }

                if (attr.value("ID").isEmpty()) {    //If there is not ID, The sequence of elements is ID
#if defined(__DEBUG_ON__)
                    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] strKeyName[" << strKeyName << "] index[strKeyName][" << index[strKeyName] << "]";
#endif  /* __DEBUG_ON__ */
                    QString tmp = strKeyName;
                    strKeyName.append('(').append(QString("%1").arg(index[tmp])).append(')');  // Make unique

                    index[tmp] += 1;
#if defined(__DEBUG_ON__)
                    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] strKeyName[" << strKeyName << "] tmp[" << tmp << "] index[tmp][" << index[tmp] << "]";
#endif  /* __DEBUG_ON__ */
                }
                else {
#if defined(__DEBUG_ON__)
                    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] strKeyName[" << strKeyName << "] attr.value(\"ID\")[" << attr.value("ID") << "]";
#endif  /* __DEBUG_ON__ */
                    strKeyName.append('(').append(attr.value("ID").toString()).append(')');   //Make unique
                }

                for (int i = 0; i < count; i++) {
                    QString tmpKey(strKeyName);
                    tmpKey.append('.').append(attr.at(i).name().toString());
#if defined(__DEBUG_ON__)
                    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] strKeyName[" << strKeyName << "] tmpKey[" << tmpKey << "] attr.at(" << i << ")[" << attr.at(i).name() << "][" << attr.at(i).value() << "]";
#endif  /* __DEBUG_ON__ */
                    if (attr.at(i).name() == "ID") {
                        continue;
                    }
                    else {
                        xmlSettings[tmpKey].append(attr.at(i).value()) ;
                    }
                }
            }
        }
        else if (xmlReader.tokenType() == QXmlStreamReader::EndElement) {
            strKeyName = strKeyName.left(lastKeyLength.back());// remove previous element.
            lastKeyLength.pop_back();
        }

        xmlReader.readNext();
    }

    file.close();

    if (xmlReader.hasError()) {
        qDebug() << "Error: Failed to parse file " << qPrintable(fileName) << ": " << qPrintable(xmlReader.errorString());

        return false;
    }
    else if (file.error() != QFile::NoError) {
        qDebug() << "Error: Cannot read file " << qPrintable(fileName) << ": " << qPrintable(file.errorString());

        return false;
    }

    return true;
}

bool QXml::validation(const QString &xsdFile, const QString &xmlfile)
{
    bool ret = true;
    QXmlSchema schema;
    QFile xsd(xsdFile);
    xsd.open(QIODevice::ReadOnly);

    QFile xml(xmlfile);
    xml.open(QIODevice::ReadOnly);

    schema.load(&xsd, QUrl::fromLocalFile(xsd.fileName()));

    if (schema.isValid()) {
        QXmlSchemaValidator validator(schema);
        validator.setMessageHandler(this);  //if there are errors, call handleMessage() bellow.

        if (!validator.validate(&xml, QUrl::fromLocalFile(xml.fileName()))) {
            NOTIFY_ON_TITLE(STR_XML_INVALID);
            ret = false;
#if defined(__DEBUG_ON__)
            qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] ret[" << ret << "]";
#endif  /* __DEBUG_ON__ */
        }
    }
    else {
        NOTIFY_ON_TITLE(STR_XSD_INVALID);
        ret = false;
#if defined(__DEBUG_ON__)
        qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] ret[" << ret << "]";
#endif  /* __DEBUG_ON__ */
    }

    xsd.close();
    xml.close();
    return ret;
}

void QXml::handleMessage(QtMsgType type, const QString& description, const QUrl& identifier, const QSourceLocation& sourceLocation)
{
    QString Error = QString("%1(line:%2, column:%3)").arg(sourceLocation.uri().toLocalFile()).arg(sourceLocation.line()).arg(sourceLocation.column());
#if defined(__ENABLE_QT4__)
    QMessageBox::warning(NULL, trUtf8(Error.toAscii()), description, QMessageBox::Ok);
#else
    QMessageBox::warning(NULL, trUtf8(Error.toLatin1()), description, QMessageBox::Ok);
#endif  /* __ENABLE_QT4__ */
}

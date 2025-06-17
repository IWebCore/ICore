#include "IFileUtil.h"

$PackageWebCoreBegin

QString IFileUtil::readFileAsString(const QString &path, bool& ok)
{
    return readFileAsByteArray(path, &ok);
}

IResult<QString> IFileUtil::readFileAsString(const QString &path)
{
    bool ok;
    auto content = readFileAsString(path, ok);
    if(ok){
        return content;
    }
    return std::nullopt;
}

QByteArray IFileUtil::readFileAsByteArray(const QString &path, bool* ok)
{
    QFile file(path);
    if(!file.exists() || !file.open(QFile::ReadOnly)){
        if(ok){
            *ok = false;
        }
        return {};
    }

    QByteArray content = file.readAll();
    file.close();
    if(ok){
        *ok = true;
    }
    return content;
}

$PackageWebCoreEnd

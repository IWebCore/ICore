#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/base/IResult.h"

$PackageWebCoreBegin

namespace IFileUtil
{
    QString readFileAsString(const QString& path, bool& ok);
    IResult<QString> readFileAsString(const QString& path);
    QString readFileAsStringOrDefault(const QString& path);

    std::string readFileAsString(const std::string& path, bool& ok);
    IResult<std::string> readFileAsString(const std::string& path);
    std::string readFileAsStringOrDefault(const std::string& path);

    QByteArray readFileAsByteArray(const QString& path, bool* ok=nullptr);
    QStringList readFileAsStringList(const QString& path);

    void writeToFile(const QString& path, const QString& content);
    void writeToFile(const QString& path, const QByteArray& content);
}

$PackageWebCoreEnd


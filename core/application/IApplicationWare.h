#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IApplicationWare
{
public:
    IApplicationWare();

public:
    virtual QString applicationName() const = 0;
    virtual QString applicationPath() const = 0;
    virtual QString workingDirectory() const = 0;
    virtual QStringList arguments() const = 0;
    virtual std::int64_t time() const = 0;
};

$PackageWebCoreEnd

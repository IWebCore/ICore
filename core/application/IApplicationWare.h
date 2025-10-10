#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IApplicationTimerWare;
class IApplicationWare
{
public:
    IApplicationWare() = default;
    virtual ~IApplicationWare() = default;

public:
    virtual QString applicationName() const;
    virtual QString applicationPath() const;
    virtual QString workingDirectory() const;
    virtual QStringList arguments() const;
    virtual IApplicationTimerWare& time() const = 0;


    virtual int exec() = 0;

protected:
    virtual QString applicationType() const = 0;
    virtual void invoke(int, const char**) = 0;

protected:
    QString m_applicationName;
    QString m_applicationPath;
    QString m_workingDirectory;
    QStringList m_arguments;
};

$PackageWebCoreEnd

#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISoloUnit.h"
#include "core/base/IHandle.h"

$PackageWebCoreBegin

class IApplicationWare;
class IApplicationManage : public ISoloUnit<IApplicationManage>
{
public:
    using Task = std::function<void()>;

public:
    IApplicationManage();

public:
    QString applicationName() const;
    QString applicationPath() const;
    QString workingDirectory() const;
    QStringList arguments() const;
    std::int64_t time() const;

    IHandle startTimer(std::chrono::milliseconds duration, Task);
    void stopTimer(IHandle id);

public:
    void registerApplicationWare(IApplicationWare* ware);

private:
    IApplicationWare* m_applicationWare{};
};

$PackageWebCoreEnd

#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/base/IHandle.h"

$PackageWebCoreBegin

class IApplicationTimerWare
{
public:
    using Task = std::function<void()>;

public:
    IApplicationTimerWare() = default;
    virtual ~IApplicationTimerWare() = default;

public:
    virtual std::int64_t time() = 0;
    virtual IHandle startTimer(std::chrono::milliseconds duration, Task task) = 0;
    virtual IHandle stopTimer(IHandle) = 0;
};

$PackageWebCoreEnd

#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class ITimer
{
public:
    using Task = std::function<void()>;

public:
    ITimer(std::chrono::milliseconds duration, Task );
    ~ITimer();

public:
    void cancelTimer();
    void startTimer();

private:
    std::chrono::milliseconds m_duration;
    Task m_task;
    asio::steady_timer m_timer;
    bool m_isContinue{true};
};

$PackageWebCoreEnd

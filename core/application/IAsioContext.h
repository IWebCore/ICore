#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISoloUnit.h"

$PackageWebCoreBegin

class IAsioTimer;
class IAsioContext : public ISoloUnit<IAsioContext>
{
public:
    using Task = std::function<void()>;

public:
    IAsioContext() = default;
    ~IAsioContext();

public:
    asio::io_context& getContext();

    void run(int threadCount);

public:
    // TODO: 将 std::ptrdiff_t 抽象为 handle 吧
    static void post(Task);
    static std::ptrdiff_t startTimer(std::chrono::milliseconds duration, Task);
    static void stopTimer(std::ptrdiff_t ptr);

private:
    asio::io_context m_context;
    QList<IAsioTimer*> m_timers;
};

$PackageWebCoreEnd

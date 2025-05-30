#include "ITimer.h"

#include "core/application/IAsioContext.h"

$PackageWebCoreBegin

ITimer::ITimer(std::chrono::milliseconds duration, ITimer::Task task)
    : m_duration(duration), m_task(std::move(task)), m_timer(IAsioContext::instance().getContext())
{
    startTimer();
}

ITimer::~ITimer()
{
    m_timer.cancel();
}

void ITimer::cancelTimer()
{
    m_timer.cancel();
    m_isContinue = false;
}

void ITimer::startTimer()
{
    m_timer.expires_after(m_duration);
    m_timer.async_wait([=](std::error_code err){
        if(err){
            return;
        }

        m_task();

        if(m_isContinue){
            startTimer();
        }
    });
}

$PackageWebCoreEnd

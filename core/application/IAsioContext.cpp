#include "IAsioContext.h"
#include "core/application/default/ITimer.h"
#include "core/config/IContextImport.h"

$PackageWebCoreBegin

IAsioContext::~IAsioContext()
{
    for(auto timer : m_timers){
        delete timer;
    }
}

asio::io_context &IAsioContext::getContext()
{
    return m_context;
}

void IAsioContext::run(int threadCount)
{
    std::vector<std::thread> threads;
    for(std::size_t i=0; i<threadCount; i++){
        threads.emplace_back(std::thread([&](){
            m_context.run();
        }));
    }
    m_context.run();
    for(std::size_t i=0; i<threadCount; i++){
        threads[i].join();
    }
}

void IAsioContext::post(IAsioContext::Task task)
{
    instance().m_context.post(task);
}

std::ptrdiff_t IAsioContext::startTimer(std::chrono::milliseconds duration, IAsioContext::Task task)
{
    auto timer = new ITimer(duration, task);
    instance().m_timers.append(timer);
    return reinterpret_cast<std::ptrdiff_t>(timer);
}

void IAsioContext::stopTimer(ptrdiff_t ptr)
{
    for(auto timer : instance().m_timers){
        if(ptr == reinterpret_cast<std::ptrdiff_t>(timer)){
            instance().m_timers.removeOne(timer);
            timer->cancelTimer();
            delete timer;
            return;
        }
    }
}

$PackageWebCoreEnd

#pragma once

#if __has_include(<asio.hpp>)

#include "core/application/IApplicationInterface.h"

$PackageWebCoreBegin

class IAsioApplication : public IApplicationInterface<IAsioApplication>
{
public:
    IAsioApplication();

public:
    virtual QString applicationName() const final;
    virtual QString applicationPath() const final;
    virtual QString workingDirectory() const final;
    virtual QStringList arguments() const final;

public:
    virtual std::int64_t time() final;
    virtual IHandle startTimer(std::chrono::milliseconds duration, TaskType task) final;
    virtual void stopTimer(IHandle) final;
    virtual void post(TaskType) final;

public:
    virtual int exec() final;

protected:
    virtual QString applicationType() const final;
    virtual IApplicationWare* invoke(int, char**) final;

private:
    virtual void $task() final;

private:
    int m_threadCount{};
    std::atomic_int64_t m_time{};
};

$PackageWebCoreEnd

#endif

// #pragma once

// #if __has_include(<asio.hpp>)

// #include "IApplicationInterface.h"
// #include "asio/io_context.hpp"

// $PackageWebCoreBegin

// class IAsioApplication : public IApplicationInterface<IAsioApplication>
// {
// public:
//     IAsioApplication(int argc, char** argv);

// public:
//     void setThreadCount(int threadCount);
//     virtual int run() final;

// private:
//     int m_threadCount{};
// };

// using IApplication = IAsioApplication;

// $PackageWebCoreEnd

// #endif

#pragma once

#include "core/application/IApplicationInterface.h"

$PackageWebCoreBegin

class IAsioApplication : public IApplicationInterface<IAsioApplication>
{
public:
    IAsioApplication();

public:
    virtual IApplicationTimerWare& time() const final;
    virtual int exec() final;

protected:
    virtual QString applicationType() const final;
    virtual void invoke(int, const char**) final;
};

$PackageWebCoreEnd


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

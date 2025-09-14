#pragma once

#if __has_include(<asio.hpp>)

#include "IApplicationInterface.h"
#include "asio/io_context.hpp"

$PackageWebCoreBegin

class IAsioApplication : public IApplicationInterface<IAsioApplication>
{
public:
    IAsioApplication(int argc, char** argv);

public:
    void setThreadCount(int threadCount);
    virtual int run() final;

private:
    int m_threadCount{};
};

using IApplication = IAsioApplication;

$PackageWebCoreEnd

#endif

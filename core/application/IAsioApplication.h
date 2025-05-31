#pragma once

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
    std::unique_ptr<QCoreApplication> m_qCoreApplication;
};

using IApplication = IAsioApplication;

$PackageWebCoreEnd

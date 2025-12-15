#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/default/IEndupTaskInterface.h"

$PackageWebCoreBegin

class IApplicationShutdown : public IEndupTaskInterface<IApplicationShutdown>
{
public:
    IApplicationShutdown();
    ~IApplicationShutdown();

private:
    virtual void $task() final;

private:
    asio::signal_set m_signal;
};

$PackageWebCoreEnd

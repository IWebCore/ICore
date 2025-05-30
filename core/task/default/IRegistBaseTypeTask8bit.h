#pragma once

#include "core/util/IPackageUtil.h"
#include "core/task/unit/ITaskInstantUnit.h"

$PackageWebCoreBegin

class IRegistBaseTypeTask8bit : public ITaskInstantUnit<IRegistBaseTypeTask8bit, true>
{
public:
    IRegistBaseTypeTask8bit() = default;

public:
    virtual void $task() final;
};

$PackageWebCoreEnd

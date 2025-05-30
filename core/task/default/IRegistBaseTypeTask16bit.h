#pragma once

#include "core/util/IPackageUtil.h"
#include "core/task/unit/ITaskInstantUnit.h"

$PackageWebCoreBegin

class IRegistBaseTypeTask16bit : public ITaskInstantUnit<IRegistBaseTypeTask16bit, true>
{
public:
    IRegistBaseTypeTask16bit() = default;

public:
    virtual void $task() final;
};

$PackageWebCoreEnd

#pragma once

#include "core/util/IPackageUtil.h"
#include "core/task/unit/ITaskInstantUnit.h"

$PackageWebCoreBegin

class IRegistBaseTypeTask32bit : public ITaskInstantUnit<IRegistBaseTypeTask32bit, true>
{
public:
    IRegistBaseTypeTask32bit() = default;

public:
    virtual void $task() final;
};

$PackageWebCoreEnd

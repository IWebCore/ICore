#pragma once

#include "core/util/IPackageUtil.h"
#include "core/task/unit/ITaskInstantUnit.h"

$PackageWebCoreBegin

class IRegistBaseTypeTask64bit : public ITaskInstantUnit<IRegistBaseTypeTask64bit, true>
{
public:
    IRegistBaseTypeTask64bit() = default;

public:
    virtual void $task() final;
};

$PackageWebCoreEnd

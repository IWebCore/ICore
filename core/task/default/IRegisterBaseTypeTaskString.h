#pragma once

#include "core/util/IPackageUtil.h"
#include "core/task/unit/ITaskInstantUnit.h"

$PackageWebCoreBegin

class IRegistBaseTypeTaskString : public ITaskInstantUnit<IRegistBaseTypeTaskString, true>
{
public:
    IRegistBaseTypeTaskString() = default;

public:
    virtual void $task() final;
};

$PackageWebCoreEnd

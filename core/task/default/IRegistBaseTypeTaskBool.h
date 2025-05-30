﻿#pragma once

#include "core/util/IPackageUtil.h"
#include "core/task/unit/ITaskInstantUnit.h"

$PackageWebCoreBegin

class IRegistBaseTypeTaskBool : public ITaskInstantUnit<IRegistBaseTypeTaskBool>
{
public:
    IRegistBaseTypeTaskBool() = default;

public:
    virtual void $task() final;
};

$PackageWebCoreEnd

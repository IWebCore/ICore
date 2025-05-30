#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/test/ITestManage.h"
#include "core/test/ITestCatagory.h"
#include "core/task/unit/ITaskWareUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IUnitTestInterface :  public ITaskWareUnit<T, ITestCatagory, enabled>, public QObject, public ISoloUnit<T>
{
public:
    IUnitTestInterface() = default;

public:
    virtual double $order() const final;
    virtual void $task() final;
};

template<typename T, bool enabled>
double IUnitTestInterface<T, enabled>::$order() const
{
    return 0;
}

template<typename T, bool enabled>
void IUnitTestInterface<T, enabled>::$task()
{
    if constexpr (enabled){
        ITestManage::instance().addTest("unitTest", &T::instance());
    }
}

$PackageWebCoreEnd

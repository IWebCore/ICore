#include "IRegistBaseTypeTask32bit.h"
#include "core/bean/IBeanRegistBaseTypeUnit.h"

$PackageWebCoreBegin

void IRegistBaseTypeTask32bit::$task()
{
    IBeanRegistBaseTypeUnit<int>::registType();
    IBeanRegistBaseTypeUnit<unsigned int>::registType();
}

$PackageWebCoreEnd

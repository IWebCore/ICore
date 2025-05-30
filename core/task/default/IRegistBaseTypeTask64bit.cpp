#include "IRegistBaseTypeTask64bit.h"
#include "core/bean/IBeanRegistBaseTypeUnit.h"

$PackageWebCoreBegin

void IRegistBaseTypeTask64bit::$task()
{
    IBeanRegistBaseTypeUnit<long>::registType();
    IBeanRegistBaseTypeUnit<unsigned long>::registType();
    IBeanRegistBaseTypeUnit<long long>::registType();
    IBeanRegistBaseTypeUnit<unsigned long long>::registType();
}

$PackageWebCoreEnd

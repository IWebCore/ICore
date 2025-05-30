#include "IRegistBaseTypeTask16bit.h"
#include "core/bean/IBeanRegistBaseTypeUnit.h"

$PackageWebCoreBegin

void IRegistBaseTypeTask16bit::$task()
{
    IBeanRegistBaseTypeUnit<short>::registType();
    IBeanRegistBaseTypeUnit<unsigned short>::registType();
}

$PackageWebCoreEnd

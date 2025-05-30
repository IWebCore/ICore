#include "IRegistBaseTypeTask8bit.h"
#include "core/bean/IBeanRegistBaseTypeUnit.h"

$PackageWebCoreBegin

void IRegistBaseTypeTask8bit::$task()
{
    IBeanRegistBaseTypeUnit<uchar>::registType();
    IBeanRegistBaseTypeUnit<char>::registType();
}

$PackageWebCoreEnd

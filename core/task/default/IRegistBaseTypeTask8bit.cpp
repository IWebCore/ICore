#include "IRegistBaseTypeTask8bit.h"
#include "core/bean/IBeanRegistBaseTypeUnit.h"

$PackageWebCoreBegin

IRegistBaseTypeTask8bit::IRegistBaseTypeTask8bit()
{

}

void IRegistBaseTypeTask8bit::$task()
{
    IBeanRegistBaseTypeUnit<uchar>::registType();
    IBeanRegistBaseTypeUnit<signed char>::registType();
}

$PackageWebCoreEnd

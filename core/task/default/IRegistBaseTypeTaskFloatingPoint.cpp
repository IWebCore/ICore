#include "IRegistBaseTypeTaskFloatingPoint.h"
#include "core/bean/IBeanRegistBaseTypeUnit.h"

$PackageWebCoreBegin

IRegistBaseTypeTaskFloatingPoint::IRegistBaseTypeTaskFloatingPoint()
{

}

void IRegistBaseTypeTaskFloatingPoint::$task()
{
    IBeanRegistBaseTypeUnit<float>::registType();
    IBeanRegistBaseTypeUnit<double>::registType();
}

$PackageWebCoreEnd

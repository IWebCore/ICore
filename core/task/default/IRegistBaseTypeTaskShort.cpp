#include "IRegistBaseTypeTaskShort.h"
#include "core/bean/IBeanRegistBaseTypeUnit.h"

$PackageWebCoreBegin

IRegistBaseTypeTaskShort::IRegistBaseTypeTaskShort()
{

}

void IRegistBaseTypeTaskShort::$task()
{
    IBeanRegistBaseTypeUnit<short>::registType();
    IBeanRegistBaseTypeUnit<unsigned short>::registType();
}

$PackageWebCoreEnd

#include "IRegistBaseTypeTaskLongLong.h"
#include "core/bean/IBeanRegistBaseTypeUnit.h"

$PackageWebCoreBegin

IRegistBaseTypeTaskLongLong::IRegistBaseTypeTaskLongLong()
{

}

void IRegistBaseTypeTaskLongLong::$task()
{
    IBeanRegistBaseTypeUnit<long long>::registType();
    IBeanRegistBaseTypeUnit<unsigned long long>::registType();
}

$PackageWebCoreEnd

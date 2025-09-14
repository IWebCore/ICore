#include "IRegistBaseTypeTaskLong.h"
#include "core/bean/IBeanRegistBaseTypeUnit.h"

$PackageWebCoreBegin

IRegistBaseTypeTaskLong::IRegistBaseTypeTaskLong()
{

}

void IRegistBaseTypeTaskLong::$task()
{
    IBeanRegistBaseTypeUnit<long>::registType();
    IBeanRegistBaseTypeUnit<unsigned long>::registType();
}

$PackageWebCoreEnd

#include "IRegistBaseTypeTaskQString.h"
#include "core/bean/IBeanRegistBaseTypeUnit.h"

$PackageWebCoreBegin

IRegistBaseTypeTaskQString::IRegistBaseTypeTaskQString()
{

}

void IRegistBaseTypeTaskQString::$task()
{
    IBeanRegistBaseTypeUnit<QString>::registType();
}

$PackageWebCoreEnd

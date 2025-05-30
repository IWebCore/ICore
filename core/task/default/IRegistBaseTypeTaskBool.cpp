#include "IRegistBaseTypeTaskBool.h"
#include "core/bean/IBeanRegistBaseTypeUnit.h"

$PackageWebCoreBegin

void IRegistBaseTypeTaskBool::$task()
{
    IBeanRegistBaseTypeUnit<bool>::registType();
}

$PackageWebCoreEnd

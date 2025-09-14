#include "IRegistBaseTypeTaskBool.h"
#include "core/bean/IBeanRegistBaseTypeUnit.h"

$PackageWebCoreBegin

IRegistBaseTypeTaskBool::IRegistBaseTypeTaskBool()
{

}

void IRegistBaseTypeTaskBool::$task()
{
    IBeanRegistBaseTypeUnit<bool>::registType();
}

$PackageWebCoreEnd

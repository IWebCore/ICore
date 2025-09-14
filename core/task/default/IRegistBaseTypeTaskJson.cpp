#include "IRegistBaseTypeTaskJson.h"
#include "core/bean/IBeanRegistBaseTypeUnit.h"

$PackageWebCoreBegin

IRegistBaseTypeTaskJson::IRegistBaseTypeTaskJson()
{

}

void IRegistBaseTypeTaskJson::$task()
{
    IBeanRegistBaseTypeUnit<IJson>::registType();
}

$PackageWebCoreEnd

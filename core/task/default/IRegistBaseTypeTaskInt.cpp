#include "IRegistBaseTypeTaskInt.h"
#include "core/bean/IBeanRegistBaseTypeUnit.h"

$PackageWebCoreBegin

IRegistBaseTypeTaskInt::IRegistBaseTypeTaskInt()
{

}

void IRegistBaseTypeTaskInt::$task()
{
    IBeanRegistBaseTypeUnit<int>::registType();
    IBeanRegistBaseTypeUnit<unsigned int>::registType();
}

$PackageWebCoreEnd

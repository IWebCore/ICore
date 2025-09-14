#include "IRegistBaseTypeTask8bitChar.h"
#include "core/bean/IBeanRegistBaseTypeUnit.h"

$PackageWebCoreBegin

IRegistBaseTypeTask8bitChar::IRegistBaseTypeTask8bitChar()
{

}

void IRegistBaseTypeTask8bitChar::$task()
{
    IBeanRegistBaseTypeUnit<char>::registType();
}

$PackageWebCoreEnd

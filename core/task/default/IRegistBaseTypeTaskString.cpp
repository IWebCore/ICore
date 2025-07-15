#include "IRegisterBaseTypeTaskString.h"
#include "core/bean/IBeanRegistBaseTypeUnit.h"

$PackageWebCoreBegin

void IRegistBaseTypeTaskString::$task()
{
//    IBeanRegistBaseTypeUnit<IStringView>::registType();
    IBeanRegistBaseTypeUnit<IJson>::registType();
    IBeanRegistBaseTypeUnit<IString>::registType();
    IBeanRegistBaseTypeUnit<std::string>::registType();
    IBeanRegistBaseTypeUnit<QString>::registType();
}

$PackageWebCoreEnd

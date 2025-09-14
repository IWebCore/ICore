#include "IRegisterBaseTypeTaskString.h"
#include "core/bean/IBeanRegistBaseTypeUnit.h"

$PackageWebCoreBegin

IRegistBaseTypeTaskString::IRegistBaseTypeTaskString()
{

}

void IRegistBaseTypeTaskString::$task()
{
//    IBeanRegistBaseTypeUnit<IStringView>::registType();

    IBeanRegistBaseTypeUnit<IString>::registType();
    IBeanRegistBaseTypeUnit<std::string>::registType();
}

$PackageWebCoreEnd

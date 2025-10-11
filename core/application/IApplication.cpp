#include "IApplication.h"
#include "IApplicationManage.h"
#include "iApp.h"

$PackageWebCoreBegin

IApplication::IApplication(int argc, char **argv, const QString &type)
{
    if(iApp){
        qFatal("app already started");
    }
    if(auto fun = IApplicationManage::instance().getAppFunction(type); fun){
        iApp = fun(argc, argv);
    }else{
        qFatal("app function not found");
    }
}

IApplication::~IApplication()
{
}

int IApplication::exec()
{
    return iApp->exec();
}

$PackageWebCoreEnd

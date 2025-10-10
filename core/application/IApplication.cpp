#include "IApplication.h"
#include "IApplicationManage.h"
#include "IApplicationWare.h"

$PackageWebCoreBegin

extern IApplicationWare* iApp;

IApplication::IApplication(int argc, char *argv[], const QString &type)
    : IApplication(argc, const_cast<const char**>(argv), type)
{
}

IApplication::IApplication(int argc, const char **argv, const QString &type)
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

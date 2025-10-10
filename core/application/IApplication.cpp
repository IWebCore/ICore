#include "IApplication.h"
#include "IApplicationManage.h"
#include "IApplicationWare.h"

$PackageWebCoreBegin

IApplication::IApplication(int argc, char *argv[], const QString &type)
    : IApplication(argc, const_cast<const char**>(argv), type)
{
}

IApplication::IApplication(int argc, const char **argv, const QString &type)
{
    if(auto fun = IApplicationManage::instance().getAppFunction(type); fun){
        fun(argc, argv);
    }else{
        qFatal("app function not found");
    }
}

IApplication::~IApplication()
{
    delete iApp;
    iApp = nullptr;
}

int IApplication::exec()
{
    return iApp->exec();
}

$PackageWebCoreEnd

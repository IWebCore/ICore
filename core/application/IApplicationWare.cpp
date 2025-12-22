#include "IApplicationWare.h"
#include "core/task/ITaskManage.h"

$PackageWebCoreBegin

QString IApplicationWare::applicationName() const
{
    return qApp->applicationName();
}

QString IApplicationWare::applicationPath() const
{
    return qApp->applicationFilePath();
}

QString IApplicationWare::workingDirectory() const
{
    return QDir::currentPath();
}

QStringList IApplicationWare::arguments() const
{
    return qApp->arguments();
}

IApplicationWare *IApplicationWare::invoke(int argc, char ** argv)
{
    static QCoreApplication qCoreApp(argc, argv);
    return this;
}

$PackageWebCoreEnd

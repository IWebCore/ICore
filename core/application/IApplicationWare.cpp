#include "IApplicationWare.h"

QString IApplicationWare::applicationName() const
{
    return m_applicationName;
}

QString IApplicationWare::applicationPath() const
{
    return m_applicationPath;
}

QString IApplicationWare::workingDirectory() const
{
    return m_workingDirectory;
}

QStringList IApplicationWare::arguments() const
{
    return m_arguments;
}

#pragma once

#include "core/util/IHeaderUtil.h"
#include "IApplicationAnnomacro.h"

$PackageWebCoreBegin

class IApplicationWare;
extern IApplicationWare* iApp;

class IApplication
{
public:
    IApplication(int argc, char* argv[], const QString& type = "asio");
    IApplication(int argc, const char** argv, const QString& type = "asio");
    ~IApplication();

public:
    int exec();
};

$PackageWebCoreEnd

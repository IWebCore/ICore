#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISoloUnit.h"
#include "core/base/IHandle.h"

$PackageWebCoreBegin

class IApplicationWare;
extern IApplicationWare* iApp;

class IApplicationManage : public ISoloUnit<IApplicationManage>
{
public:
    using AppFun = std::function<void(int, const char**)>;

public:
    void registerAppFuns(const QString& name, AppFun);
    AppFun getAppFunction(const QString&);

private:
    QMap<QString, AppFun> m_appFuns;
};

$PackageWebCoreEnd

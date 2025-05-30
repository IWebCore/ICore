#include "ITestManage.h"

$PackageWebCoreBegin

void ITestManage::addTest(const QString &type, QObject *obj)
{
    instance().m_testCases[type].append(obj);
}

bool ITestManage::hasTests(const QString &type) const
{
    return instance().m_testCases.contains(type) && !instance().m_testCases[type].isEmpty();
}

void ITestManage::invokeTests(const QString &type)
{
    auto& objs = instance().m_testCases[type];
    for(auto obj : objs){
        QTest::qExec(obj);
    }
}

$PackageWebCoreEnd
